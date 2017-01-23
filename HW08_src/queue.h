#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* Queue structure which holds all necessary data */
typedef struct {
     void** m_arr;    // Pole ukazatelu - do nej budeme ukladat (a odebirat) prvky.
     int m_size;      // Velikost fronty (= pocet vyuzitych mist v poli m_arr).
     int m_capacity;  // Kapacity fronty (= velikost pole m_arr; vic prvku se tam nevejde).
     int m_oldest;    // Index nejstarsiho prvku v m_arr (nejstarsi => prvni na rade pri popnuti)
     int m_newest;    // Index prvniho volneho mista v m_arr (o index pred timto je (zatim) nejnovejsi prvek).
} queue_t;

/* creates a new queue with a given size */
queue_t* create_queue(int capacity);

/* deletes the queue and all allocated memory */
void delete_queue(queue_t *queue);

/*
 * inserts a reference to the element into the queue
 * returns: true on success; false otherwise
 */
bool push_to_queue(queue_t *queue, void *data);

/*
 * gets the first element from the queue and removes it from the queue
 * returns: the first element on success; NULL otherwise
 */
void* pop_from_queue(queue_t *queue);

/*
 * gets idx-th element from the queue
 * returns the element that will be popped after idx calls of the pop_from_queue()
 * returns: the idx-th element on success; NULL otherwise
 */
void* get_from_queue(queue_t *queue, int idx);

/* gets number of stored elements */
int get_queue_size(queue_t *queue);

#endif /* __QUEUE_H__ */
