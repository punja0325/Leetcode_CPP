typedef struct Node{
    int key;
    int value;
    struct Node* next;
    struct Node* prev;
    struct Node* hash_next; // 用於哈希表碰撞鏈

} Node_t;

typedef struct {
    // 定義你的結構
    int capacity; // maximum size
    int size;       // current size
    Node_t** hash_table;
    int hash_size;;
    Node_t* head;
    Node_t* tail;
} LRUCache;

int hashFun(int key, int hash_size) {
    return ((uint32_t)key * 31) % hash_size;
}



LRUCache* lRUCacheCreate(int capacity);
int lRUCacheGet(LRUCache* obj, int key);
void lRUCachePut(LRUCache* obj, int key, int value);
void lRUCacheFree(LRUCache* obj);


LRUCache* lRUCacheCreate(int capacity) {
    if (capacity <= 0) return NULL;
    LRUCache* cache = malloc(sizeof(LRUCache));
    if (!cache) return NULL;
    cache->capacity = capacity;
    cache->size = 0;
    cache->hash_size = capacity * 2;
    if (cache->hash_size > 100000) cache->hash_size = 100000;
    cache->hash_table = calloc(cache->hash_size, sizeof(Node_t*));
    if (!cache->hash_table) {
        free(cache);
        return NULL;
    }
    cache->head = NULL;
    cache->tail = NULL;
    return cache;
}

void removeNode(LRUCache* obj, Node_t* node) {
    if (node->prev) {
        node->prev->next = node->next;
    } else {
        obj->head = node->next;
    }
    if (node->next) {
        node->next->prev = node->prev;
    } else {
        obj->tail = node->prev;
    }
    if (!obj->head) obj->tail = NULL;
}

void insertHead(LRUCache* obj, Node_t* node) {
    node->prev = NULL;
    node->next = obj->head;
    if (obj->head) obj->head->prev = node;
    obj->head = node;
    if (!obj->tail) obj->tail = node;
}


int lRUCacheGet(LRUCache* obj, int key) {
    int idx =  hashFun(key, obj->hash_size);
    Node_t* node = obj->hash_table[idx];
    while (node && node->key != key) {
        node = node->hash_next;
    }
    if (!node) return -1; // Not Found
    // Move to head
    removeNode(obj, node);
    insertHead(obj, node);
    return node->value;
}

void lRUCachePut(LRUCache* obj, int key, int value) {
    int idx =  hashFun(key, obj->hash_size);
    Node_t* node = obj->hash_table[idx];
    while (node && node->key != key) {
        node = node->hash_next;
    }
    if (node) { //key exist
        node->value = value;
        removeNode(obj, node);
        insertHead(obj, node);
        return;
    }
    // Create new node
    Node_t* new_node = malloc(sizeof(Node_t));
    if (!new_node) return;

    new_node->key = key;
    new_node->value = value;
    new_node->next = NULL;
    new_node->prev = NULL;
    new_node->hash_next = NULL;

    //Insert into hash table
    new_node->hash_next = obj->hash_table[idx];
    obj->hash_table[idx] = new_node;

    // Insert into head;
    insertHead(obj, new_node);
    obj->size++;
    if (obj->size > obj->capacity) {
        Node_t* tail = obj->tail;
        removeNode(obj, tail);

        // Remove from hash table
        int tidx = hashFun(tail->key, obj->hash_size);
        Node_t** indirect = &obj->hash_table[tidx];
        while (*indirect && *indirect != tail) {
             indirect = &(*indirect)->hash_next;
        }
        if (*indirect) {
            *indirect = tail->hash_next;
        }
        free(tail);
        obj->size--;
    }
}

void lRUCacheFree(LRUCache* obj) {
    Node_t* curr = obj->head;
    while (curr) {
        Node_t* tmp = curr;
        curr = curr->next;
        free(tmp);
    }
    free(obj->hash_table);
    free(obj);
}




