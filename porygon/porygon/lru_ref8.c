//
//  lru_ref8.c
//  porygon
//
//  Created by quake0day on 11/18/12.
//  Copyright (c) 2012 quake0day. All rights reserved.
//

#include <stdio.h>
#include "main.h"
int do_lru_ref8(Queue* queue,char* input_seq, int frames){
    Queue* queue_p = queue;
    for(int i=0; i<SEQ_SIZE; i++){
        if(*input_seq != ' '){
            int ref_num = atoi(input_seq);
            if(ref_num >= 0){
                int exist = QueueTraverse(queue_p,ref_num, judge_if_exists);
                if(exist == 0){ // not exists
                    if(FRAMES-- <= 0){ // queue already full
                        int target_data = ref8_find_vic(queue);
                        ref8_remove_vic(queue, target_data);
                        Push(queue,ref_num);
                        PAGE_REPLACEMENT ++;
                    }
                    else{ // not full
                        Push(queue,ref_num);
                    }
                }
            }
            right_shift_all(queue);
        }
        input_seq++;
    }
    return 0;
}


int ref8_remove_vic(Queue* pqueue, int target_data){
    //QNode* tnode = pqueue->front;
    
    int i = pqueue->size;
    int k = 0;
    while(i--){
        Pop(pqueue, &k);
        if(k != target_data){
            Push(pqueue,k);
        }
        //tnode = tnode->next;
    }
    return 0;
}

int ref8_find_vic(Queue* pqueue){
    QNode* qnode = pqueue->front;
    int i = pqueue->size;
    int min = qnode->reference;
    int target_data = -1;
    while(i--)
    {
        if(qnode->reference < min){
            min = qnode->reference;
            target_data = qnode->data;
        }
        qnode = qnode->next;
    }
    return target_data;
}
int right_shift_all(Queue* pqueue){
    QNode* qnode = pqueue->front;
    int i = pqueue->size;
    while(i--)
    {
        if(qnode->shift == 0){
            qnode->reference = right_shift_miss(qnode->reference);
        }
        else if(qnode->shift == 1){
            qnode->reference = right_shift_hit(qnode->reference);
            qnode->shift = 0;
        }
        qnode = qnode->next;
    }
    return 0;
}

int right_shift_hit(int k)
{
    k = k >> 1;
    k = k+ 0x80;
    
    return k;
}

int right_shift_miss(int k)
{
    k = k >> 1;
    return k;
}
