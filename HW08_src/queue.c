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
          // Zde musíme zabránit bugům typu "5 6 7 1 2 3 4 - - - - - - -"
          // TODO: Dodělat!
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
     // Implementace VOLITELNE CASTI - pokud je nyni obsazeno mene nez 1/3 mist
     // ve fronte, zmensime jeji kapacitu na 1/3.
     if(queue->m_size < queue->m_capacity / 3) {
          // 1) Alokujeme novy prostor o tretinove kapacite pro m_arr:
          void** new_arr = malloc(sizeof(void*) * (queue->m_capacity / 3));
          // 2) Do noveho prostoru prekopirujeme prvky m_arr.
          // POZOR - asi jedina vec poradne k zamysleni.
          // Pri kopirovani prvku je rovnou zarovname, aby fronta zacinala
          // na indexu 0, tj. nejstarsi prvek byl na indexu 0, druhy nejstarsi
          // na 1, atd...
          if(new_arr != NULL) {
               for(int i = 0; i < queue->m_size; ++i) {
                    new_arr[i] = queue->m_arr[(queue->m_oldest + i) % queue->m_capacity];
               }
               // Mame zkopirovano, uvolnime stare pole a je hotovo.
               free(queue->m_arr);
               queue->m_arr = new_arr;
               queue->m_capacity /= 3;
               queue->m_oldest = 0;
               queue->m_newest = queue->m_size;
          }
     }
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
