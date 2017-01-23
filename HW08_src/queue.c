#include "queue.h"

/*
 *   Tento soubor implementuje jednoduchou kruhovou frontu.
 *   Implementace je provedena pomoci pole (druha varianta
 *   by bylo implementovat kruhovou frontu pomoci spoj. seznamu,
 *   ale to bylo v zadani ukolu zakazano).
*/

queue_t* create_queue(int capacity) {
     queue_t* q = malloc(sizeof(queue_t));
     if(capacity <= 0)   // vtipalek...
          capacity = 1;
     q->m_arr = malloc(sizeof(void*) * capacity);
     q->m_size = 0;
     q->m_capacity = capacity;
     q->m_oldest = q->m_newest = 0;
     return q;
}

void delete_queue(queue_t *queue) {
     if(queue == NULL)
          return;
     free(queue->m_arr);
     free(queue);
}

bool push_to_queue(queue_t *queue, void *data) {
     if(queue->m_size == queue->m_capacity) {
          // Fronta je zaplnena - zvetsime ji na dvojnasobek.
          void** new_array = realloc(queue->m_arr, sizeof(void*) * queue->m_capacity * 2);
          if(new_array == NULL)
               return false;  // Realokace selhala.
          queue->m_arr = new_array;
          queue->m_capacity *= 2;
     }
     queue->m_newest %= queue->m_capacity;   // Osetreni index-out-of-bounds...
     // Pridame data do fronty.
     queue->m_arr[queue->m_newest++] = data;
     queue->m_size += 1;
     return true;
}

void* pop_from_queue(queue_t *queue) {
     if(queue->m_size == 0)
          return NULL;
     void* ret = queue->m_arr[queue->m_oldest++];  // Ukazatel, ktery budeme vracet.
     queue->m_oldest %= queue->m_capacity;   // Obrana proti index-out-of-bounds.
     queue->m_size -= 1;
     return ret;
}

void* get_from_queue(queue_t *queue, int idx) {
     if(0 <= idx && idx < queue->m_size) {
          // Index je validni - vratit ukazatel na dane pozici.
          return queue->m_arr[(queue->m_oldest + idx) % queue->m_capacity];
     } else {
          // Index je nevalidni (tzv. "out of bounds") - vratit NULL.
          return NULL;
     }
}

int get_queue_size(queue_t *queue) {
     return queue->m_size;
}
