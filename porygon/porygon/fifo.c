//
//  fifo.c
//  porygon
//
//  Created by quake0day on 11/14/12.
//  Copyright (c) 2012 quake0day. All rights reserved.
//

#include <stdio.h>
#include "main.h"

int do_fifo(queue* queue,char* input_seq, int frames){
    fifo_init_queue(queue);
    
    for(int i=0; i<SEQ_SIZE; i++){
        int ref_num = atoi(input_seq);
        if(ref_num >= 0){
            int exist = fifo_seek_queue(queue,ref_num);
            if(exist == 1){ // not exists
                if(FRAMES-- <= 0){
                    fifo_remove_node(queue);
                    node* new_node = (node*) malloc(sizeof(node));
                    new_node->ref_num = atoi(input_seq);
                    fifo_add_node(new_node, queue);
                    PAGE_REPLACEMENT ++;
                }
                else{
                node* new_node = (node*) malloc(sizeof(node));
                new_node->ref_num = atoi(input_seq);
                fifo_add_node(new_node, queue);
                }
            }
        }
        input_seq++;
    }
    return 0;
}

int fifo_seek_queue(queue *queue, int new_ref_num){
    node* current_node;
    int i = 0;
    if(queue-> head == NULL)
        return 1;
    current_node = queue->head;
    do {
        if(current_node->ref_num == new_ref_num){
            return 0;
        }
        current_node = current_node->next;
        i++;
    }while(i < queue->node_num);
    return 1;
}

int fifo_init_queue(queue* queue){
    if(queue == NULL)
        return 1;
    queue->head = NULL;
    queue->tail = NULL;
    queue->node_num = 0;
    return 0;
}

int fifo_add_node(node* node,queue* queue)
{
    node->next = NULL;
    node->prev = NULL;
    if(queue->node_num == 0){
        queue->head = node;
        queue->tail = node;
    }
    else{
        node->next = queue->head;
        queue->head->prev = node;
        queue->head = node;
    }
    queue->node_num++;
    return 0;
}

int fifo_remove_node(queue* queue)
{
    if(queue == NULL)
        return 1;
    switch (queue->node_num) {
        case 0:
            return 1;
        case 1:
            queue->head=NULL;
            queue->tail=NULL;
            break;
        default:
            queue->tail->prev->next = NULL;
            queue->tail = queue->tail->prev;
    }
    queue->node_num--;
    return 0;
    
}