#pragma once
#include <stdio.h>
#include <stdlib.h>

#include "tree.h"

typedef Node* Data;

struct listnode 
{
    Data value;
    struct listnode* next;
};
typedef struct listnode ListNode;


struct list
{
    ListNode* head;
    ListNode* tail;
};
typedef struct list List;


List* list_create()
{
    List* plist = (List*)malloc(sizeof(List));
    plist->head = NULL;
    plist->tail = NULL;
    return plist;
}

void list_add_last(List* plist, Data x)
{
    // Выделяем память на новый элемент
    ListNode* p_new_node = (ListNode*)malloc(sizeof(ListNode));
    p_new_node->value = x;
    p_new_node->next = NULL;

    if (plist->head == NULL)
    {
        plist->head = p_new_node;
        plist->tail = p_new_node;
    }
    else
    {
        plist->tail->next = p_new_node;
        plist->tail = p_new_node;
    }
    
}

Data list_remove_first(List* plist)
{
    if (plist->head == NULL)
    {
        printf("Error! Can't remove an element. List is empty!\n");
        exit(1);
    }
    // Запоминаем result, чтобы вернуть это значение и temp, чтобы освободить эту память в конце функции
    ListNode* temp = plist->head;
    Data result = temp->value;

    // head должен указывать на 2-й элемент
    plist->head = plist->head->next;
    if (plist->head == NULL)
        plist->tail == NULL;

    free(temp);
    return result;
}


Data list_get_first(List* plist)
{
    if (plist->head == NULL)
    {
        printf("Error! Can't get an element. List is empty!\n");
        exit(1);
    }
    return plist->head->value;
}

Data list_get_last(List* plist)
{
    if (plist->head == NULL)
    {
        printf("Error! Can't get an element. List is empty!\n");
        exit(1);
    }
    return plist->tail->value;
}

void list_print(List* plist)
{
    ListNode* ptr = plist->head;
    while (ptr != NULL)
    {
        printf("%d ", ptr->value);
        ptr = ptr->next;
    }
    printf("\n");
}

int list_is_empty(List* plist)
{
    return plist->head == NULL;
}

int list_size(List* plist)
{
    int size = 0;
    ListNode* ptr = plist->head;
    while (ptr != NULL)
    {
        size++;
        ptr = ptr->next;
    }
    return size;
}

void list_destroy(List* plist)
{
    ListNode* ptr = plist->head;
    ListNode* ptr_next;
    while (ptr != NULL)
    {
        ptr_next = ptr->next;
        free(ptr);
        ptr = ptr_next;
    }
    plist->head = NULL;
    plist->tail = NULL;
}



// Сделаем очередь на основе списка:
struct queue
{
    List* plist;
};
typedef struct queue Queue;

void queue_init(Queue* pq)
{
    pq->plist = list_create();
}
void enqueue(Queue* pq, Data x)
{
    list_add_last(pq->plist, x);
}
Data dequeue(Queue* pq)
{
    return list_remove_first(pq->plist);
}
int queue_is_empty(Queue* pq)
{
    return list_is_empty(pq->plist);
}
int queue_size(Queue* pq)
{
    return list_size(pq->plist);
}
void queue_print(Queue* pq)
{
    list_print(pq->plist);
}
void queue_destroy(Queue* pq)
{
    list_destroy(pq->plist);
}



/*
int main()
{
    Queue q;
    queue_init(&q);
    for (int i = 0; i < 10; ++i)
        enqueue(&q, i);

    printf("Deq: %d\n", dequeue(&q));
    printf("Deq: %d\n", dequeue(&q));
    printf("Deq: %d\n", dequeue(&q));


    queue_print(&q);
}
*/