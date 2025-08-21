
typedef struct block {
    uint32_t size;
    struct block* next;
} block_t;

typedef struct {
    /* Basic info */
    uint8_t* base;
    uint32_t size;
    block_t* free_list;
} memory_pool_t;

static uint32_t align_up_u32(uint32_t x, uint32_t a) {
    return (x + (a - 1u) & ~(a - 1u));
}

#define HDR_SIZE align_up_u32(sizeof(block_t), ALIGN_TO);
#define ALIGN_TO 8u
#define MIN_BLOCK (HDR_SIZE + ALIGN_TO)

bool memory_init(memory_pool_t* pool, uint8_t* base, uint32_t size) {
    if (!pool || !base || size) return false;
    pool->base = base;
    pool->size = size;
    block_t* b = (block_t*)pool->base;
    b->size = size;
    b->next = NULL;
    pool->free_list = b;
    return true;
}

uint8_t* memory_malloc(memory_pool_t* pool, uint32_t size) {
    if (!pool || !size) return NULL;
    uint32_t need = HDR_SIZE + align_up_u32(size, ALIGN_TO);

    block_t** pp = &pool->free_list;
    while(*pp) {
        block_t* curr = *pp;
        if (curr->size >= need) {
            uint32_t remain = curr->size - need;
            if (remain >= MIN_BLOCK) {
                block_t* tail = (block_t*)((uint8_t*)curr + need);
                tail->size = curr->size - need;
                tail->next = curr->next;

                //replace current free node with tail
                *pp = tail;

                curr->size = need;
                curr->next = NULL;
            } else {
                *pp = curr->next;
                curr->next = NULL;
            }
            return (uint8_t*)curr + sizeof(block_t);
        }
        pp = &(*pp)->next;
    }
    return NULL;
}

block_t* freelist_insert_sorted(memory_pool_t* pool, block_t *b) {
    block_t *prev = NULL, *curr = pool->free_list;
    while (curr && (uintptr_t)curr < (uintptr_t)b) {
        prev = curr;
        curr = curr->next;
    }
    if (prev == NULL) {
        b->next = curr;
        pool->free_list = b;
    } else {
        b->next = curr;
        prev->next = b;
    }
    return prev;
}

void coalesce_neighbors(memory_pool_t* pool, block_t* prev, block_t* b) {
    //b && next
    block_t* next = b->next;
    if (next && (uint8_t*)b + b->size == (uint8_t*)next) {
        b->size += next->size;
        b->next = next->next;
    }
    //prev & b
    if (prev && (uint8_t*)prev + prev->size == (uint8_t*)b) {
        prev->size += b->size;
        prev->next = b->next;
    }
}

void memory_free(memory_pool_t* pool, uint8_t* ptr) {
    if (!pool || !ptr) return;
    block_t* b = (block_t*)(ptr - sizeof(block_t));
    //Insert block into free-list
    block_t* prev = freelist_insert_sorted(pool, b);
    //collect neighbor if continue
    coalesce_neighbors(pool, prev, b);
}