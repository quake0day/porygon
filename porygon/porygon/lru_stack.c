//
//  lru_stack.c
//  porygon
//
//  Created by quake0day on 11/17/12.
//  Copyright (c) 2012 quake0day. All rights reserved.
//

#include <stdio.h>
#include "main.h"

int do_lru_stack(Queue* queue,char* input_seq, int frames){
    for(int i=0; i<SEQ_SIZE; i++){
        if(*input_seq != ' '){
            int ref_num = atoi(input_seq);
            if(ref_num >= 0){
                int exist = QueueTraverse(queue,ref_num, judge_if_exists);
                //int exist = fifo_seek_queue(queue,ref_num);
                if(exist == 0){ // not exists
                    if(FRAMES-- <= 0){ // queue already full
                        int k=0;
                        Pop(queue,&k);
                        Push(queue,ref_num);
                        PAGE_REPLACEMENT ++;
                    }
                    else{ // not full
                        Push(queue,ref_num);
                    }
                }
                else if(exist > 0){ // exists
                    int k=0;
                    int size = queue->size;
                    while(size!= 0){
                        Pop(queue,&k);
                        if(k != ref_num)
                            Push(queue,k);
                        size--;
                    }
                    Push(queue,ref_num);
                }
            }
        }
        input_seq++;
    }
    return 0;
}


Queue *InitQueue()
{
    Queue *pqueue = (Queue *)malloc(sizeof(Queue));
    if(pqueue != NULL)
    {
        pqueue->front = NULL;
        pqueue->rear = NULL;
        pqueue->size = 0;
    }
    return pqueue;
}
int IsEmpty(Queue *pqueue)
{
    if(pqueue->front== NULL && pqueue->rear==NULL && pqueue->size==0)
        return 1;
    else
        return 0;
}
QNode Push(Queue *pqueue, int item)
{
    QNode *qnode = (QNode *)malloc(sizeof(QNode));
    if(qnode != NULL)
    {
        qnode->data=item;
        qnode->next=NULL;
        
        if(IsEmpty(pqueue)){
            pqueue->front=qnode;
        }
        else{
            pqueue->rear->next = qnode;
        }
        pqueue->rear = qnode;
        pqueue->size++;
    }
    return *qnode;
}
void Pop(Queue *pqueue, int *k)
{
    QNode *qnode = pqueue->front;
    if(IsEmpty(pqueue) != 1 && qnode != NULL)
    {
        if(k != NULL)
            *k = qnode->data;
        pqueue->size--;
        pqueue->front = qnode->next;
        free(qnode);
        if(pqueue->size==0)
            pqueue->rear = NULL;
    }
}

int QueueTraverse(Queue *pqueue,int ref_num, int(*visit)())
{
    QNode* qnode = pqueue->front;
    int i = pqueue->size;
    int exist=0;
    while(i--)
    {
        exist += visit(qnode->data,ref_num);
        qnode = qnode->next;
    }
    return exist;
}
int judge_if_exists(int data, int ref_num)
{
    if(data == ref_num)
        return 1;
    return 0;
}
/*
 void InitialStack(LinkStack *s){
 s->top=NULL;
 s->bottom=NULL;
 }
 
 int IsEmpty(LinkStack *s){
 return s->top == NULL;
 }
 
 void Push(LinkStack *s, DataType x)
 {
 StackNode *p = (StackNode *) malloc(sizeof(StackNode));
 p->data = x;
 p->next = s->top;
 s->top = p;
 }
 */