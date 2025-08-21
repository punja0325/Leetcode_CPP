



#define HEAP_SIZE 1024

typedef struct block_header {
    uint32_t size;
    struct block_header *next;
} block_header_t;

static uint8_t heap[HEAP_SIZE];
static block_header_t *free_list = NULL;

void my_heap_init(void) {
    free_list = (block_header_t*)heap;
    free_list->size = HEAP_SIZE - sizeof(block_header_t);
    free_list->next = NULL;
}

void *my_malloc(uint32_t size) {
    block_header_t* prev = NULL;
    block_header_t* curr = free_list;

    size = (size + 3) & ~3;
    while (curr) {
        if (curr->size >= size) {
            if (curr->size >= size + sizeof(block_header_t) + 4) {
                block_header_t *new_block = (block_header_t *)((uint8_t *)curr + sizeof(block_header_t) + size);
                new_block->size = curr->size - sizeof(block_header_t) - size;
                new_block->next = curr->next;
                curr->size = size;
                if (prev) prev->next = new_block;
                else free_list = new_block;
            } else {
                if (prev) prev->next = curr->next;
                else free_list = curr->next;
            }
            return (uint8_t*)curr + sizeof(block_header_t);
        }
        prev = curr;
        curr = curr->next;
    }
    return NULL; //out of memory
}

void my_free(void *ptr) {
    if (!ptr) return;
    block_header_t *block = (block_header_t *)((uint8_t *)ptr - sizeof(block_header_t));

    // 插入到 free list 開頭
    block->next = free_list;
    free_list = block;

    // 合併相鄰區塊（可選）
    block_header_t *curr = free_list;
    while (curr && curr->next) {
        uint8_t *end_of_curr = (uint8_t *)curr + sizeof(block_header_t) + curr->size;
        if (end_of_curr == (uint8_t *)curr->next) {
            curr->size += sizeof(block_header_t) + curr->next->size;
            curr->next = curr->next->next;
        } else {
            curr = curr->next;
        }
    }
}