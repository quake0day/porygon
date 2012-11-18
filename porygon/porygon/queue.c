//
//  queue.c
//  porygon
//
//  Created by quake0day on 11/17/12.
//  Copyright (c) 2012 quake0day. All rights reserved.
//

#include <stdio.h>
#include "main.h"

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
    int overlap = 0;
    QNode *qnode = (QNode *)malloc(sizeof(QNode));
    QNode *cnode = (QNode *)malloc(sizeof(QNode));
    if(qnode == pqueue->front){
        overlap = 1;
    }
    if(qnode != NULL)
    {
        if(overlap == 0){
        qnode->data=item;
        qnode->next=NULL;
        qnode->HP = 0;
        qnode->reference = 0;
        qnode->shift = 0;

        
        
        if(IsEmpty(pqueue)){
            pqueue->front=qnode;
        }
        else{
            pqueue->rear->next = qnode;
        }
        pqueue->rear = qnode;
        }
        else{
            cnode->data=item;
            cnode->next=NULL;
            cnode->HP = 0;
            
            
            if(IsEmpty(pqueue)){
                pqueue->front=cnode;
            }
            else{
                pqueue->rear->next = cnode;
            }
            pqueue->rear = cnode;
        }
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
int Pop_or_HP_decrease(Queue *pqueue, int *k, int pos)
{
    QNode *qnode = pqueue->front;
    QNode *tempnode = pqueue->front;
    int length = pqueue->size;
    int status = 0;
    int i = 0;
    while(i < pos){
        qnode = qnode->next;
        i++;
    }
    if(IsEmpty(pqueue) != 1 && qnode != NULL)
    {
        if(k != NULL)
            *k = qnode->data;
        if(qnode->HP == 0 && pos == 0){ // HP = 0
            pqueue->size--;
            pqueue->front = qnode->next;
            free(qnode);
            status = 0;
            
        }
        else if(qnode->HP >= 1){
            qnode->HP = 0;
            status = 1;
        }
        else if( pos > 0 && qnode->HP == 0){
            while(length --)
            {
                int data = tempnode->data;
                pqueue->size--;
                pqueue->front = tempnode->next;
                if(data != *k)
                {
                    Push(pqueue,data);
                }
                tempnode = tempnode->next;
                
            }
            free(tempnode);
            status = 0;


        }
        if(pqueue->size==0)
            pqueue->rear = NULL;
    }
    return status;

    
}

int QueueTraverse(Queue *pqueue,int ref_num, int(*visit)())
{
    QNode* qnode = pqueue->front;
    int i = pqueue->size;
    int k = 0;
    int exist=0;
    while(i--)
    {
        k = visit(qnode->data,ref_num);
        if(k == 1){
            qnode->shift = 1; // mark it
        }
        exist = exist + k;
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