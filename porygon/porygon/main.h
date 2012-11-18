//
//  main.h
//  porygon
//
//  Created by quake0day on 11/13/12.
//  Copyright (c) 2012 Si Chen. All rights reserved.
//

#ifndef porygon_main_h
#define porygon_main_h

#include <stdio.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include<sys/types.h>
#include<sys/time.h>

#define LENGTH 1024
/* global variables */
extern int FRAMES; // set the number of avaliable frames. Default is 5
extern char *POLICY_R;
extern int POLICY; // set the replacement policy 0:FIFO 1:LRU 2:LRU-STACK 3:LRU-CLOCK 4:LRU-REF8
extern int INPUT_SOURCE; // set the input source 0:STDIN 1:FILE
extern int HELP; // print usage? 0:disable 1:enable
extern int SEQ_SIZE;
extern int PAGE_REPLACEMENT;
extern int PAGE_REPLACEMENT_OPT;

typedef unsigned int uint;
typedef struct queue
{
    struct node *head;
    struct node *tail;
    int node_num;
}queue;

typedef struct node
{
    int ref_num;
    struct node *next;
    struct node *prev;
    
}node;

typedef int Item;
typedef struct QNode
{
    Item data;
    Item HP;
    Item reference;
    Item shift;
    struct QNode* next;
}QNode;

typedef struct
{
    struct QNode* front;
    struct QNode* rear;
    int size;
}Queue;

// initial empty queue
Queue *InitQueue();

/*
typedef char DataType;
typedef struct stacknode{
    DataType data;
    struct stacknode *next;
}StackNode;
typedef struct{
    StackNode *top;
    StackNode *bottom;
}LinkStack;
*/
int do_lru_ref8(Queue* queue,char* input_seq, int frames);
int right_shift_miss(int k);
int right_shift_hit(int k);
int right_shift_all(Queue* pqueue);
int ref8_find_vic(Queue* pqueue);
int ref8_remove_vic(Queue* pqueue, int target_data);
int do_lru_clock(Queue* queue,char* input_seq, int frames);
int Pop_or_HP_decrease(Queue *pqueue, int *k, int pos);
int do_lru_stack(Queue* queue,char* input_seq, int frames);
int judge_if_exists(int data, int ref_num);
int QueueTraverse(Queue *pqueue,int ref_num, int(*visit)());
QNode Push(Queue *pqueue, int item);
void Pop(Queue *pqueue, int *k);
int do_lfu(char* input_seq, int FRAMES);
int lfu_replace_vic(int* m, long vic_num, int ref_num, int array_length);
int lfu_seek_array(int* k, int ref_num, int length);
int lfu_peer_history(int* k, int* old);
long lfu_find_vic(int* k, int* old, int length);
int do_optimal(char* input_seq, int FRAMES);
long optimal_peer_future(int* k, char* seq);
int optimal_find_vic(int* k, char* seq, int length);
int optimal_seek_array(int* k, int ref_num, int length);
int optimal_replace_vic(int* m, int vic_pos, int ref_num);
int do_fifo(queue* queue,char* input_seq, int frames);
int fifo_seek_queue(queue *queue, int new_ref_num);
int fifo_init_queue(queue* queue);
int fifo_add_node(node* node,queue* queue);
int fifo_remove_node(queue* queue);
#endif
