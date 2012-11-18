//
//  optimal.c
//  porygon
//
//  Created by quake0day on 11/17/12.
//  Copyright (c) 2012 quake0day. All rights reserved.
//

#include <stdio.h>
#include "main.h"


int do_optimal(char* input_seq, int FRAMES)
{
    //printf("%c",seq[4]);
    // record the frame length since FRAMES will change afterward
    // need change do_fifo to make sure FRAMES remains the same
    int ini_length = FRAMES;
    
    // this is the queue
    int array[LENGTH]={0};
    // if input length is bigger than array length it will cause buffer overflow
    if(LENGTH <= ini_length){
        fprintf(stderr, "Fatal ERROR! Please try to use a less length for input seq");
        abort();
    }
    // let a pointer point to this queue's beginning
    int *k = array;
    // SEQ_SIZE is twice larger than the actual input length (count the space)
    for(int i =0; i < SEQ_SIZE; i++){
        // try to get the sequence num
        if(*input_seq != ' '){
            int ref_num = atoi(input_seq);
            // if you can get (means not space)
            if(ref_num >=0){
                // first, try to see if this number is already in the queue
                int pos = optimal_seek_array(array, ref_num, ini_length);
                if(pos == -1){ //not exist
                    if(FRAMES-- <= 0){ // array already full
                        // we need find a victim to replace it
                        int vic_pos = optimal_find_vic(array, input_seq, ini_length);
                        optimal_replace_vic(array, vic_pos,ref_num);
                        PAGE_REPLACEMENT_OPT ++;
                    }
                    else{ // array not full
                        *k = ref_num; // set array to this input sequence number
                        k++; // done, move to the next cell in array
                    }
                }
            }
        }
        input_seq++; // move to the next input
        
    }
    
    return 0;
}
int optimal_replace_vic(int* m, int vic_pos, int ref_num){
    for(int i = 0; i < vic_pos; i++){
        m++;
    }
    *m = ref_num;
    return 0;
}
/* try to find a victim to replace it out */
/* k: the array we need to search and maintain
 seq: the input sequence we need to search
 length: frame size which indicate how many space we can use in k
 */
int optimal_find_vic(int* k, char* seq, int length){
    int* m = k;
    long vic=0;
    int j=0;
    for(int i = 0; i < length; i++){
        long pos = 0;
        pos = optimal_peer_future(m, seq);
        if(pos > vic){
            vic = pos;
            j = i;
        }
        m++;
    }
    return j;
}
long optimal_peer_future(int* k, char* seq){
    long pos = 0;
    while(*seq != '\n')
    {
        if(*seq != ' '){
            if (*k == atoi(seq)){
                return pos;
            }
            else{
                seq++;
                pos++;
            }
        }
        else{
            seq++;
        }
    }
    return ++pos;
}
int optimal_seek_array(int* k, int ref_num, int length)
{
    for(int j = 0; j < length; j++){
        if(*k == ref_num)
            return j;
        k++;
    }
    return -1;
}

/*
 
 int do_optimal(queue *queue, char* input_seq, int frames)
 {
 PAGE_REPLACEMENT_OPT = 0;
 fifo_init_queue(queue);
 for(int i=0; i<SEQ_SIZE; i++){
 int ref_num = atoi(input_seq);
 if(ref_num >= 0){
 int exist = fifo_seek_queue(queue,ref_num);
 if(exist == 1){ // not exists
 if(FRAMES-- <= 0){
 optimal_remove_node(queue,input_seq);
 node* new_node = (node*) malloc(sizeof(node));
 new_node->ref_num = atoi(input_seq);
 fifo_add_node(new_node, queue);
 PAGE_REPLACEMENT_OPT ++;
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
 printf("PAGE REPLACEMENT TIME:%d \n",PAGE_REPLACEMENT_OPT);
 return 0;
 }
 
 int optimal_remove_node(queue* queue,char* input_seq)
 {
 node* k = (node*) malloc(sizeof(node));
 int maxpos = 0;
 int j=0;
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
 k =  queue->tail;
 for(int i=0; i < queue->node_num; i++){
 int pos = optimal_return_position(k->ref_num, input_seq);
 if(pos > maxpos){
 maxpos = pos;
 j = i;
 }
 k = k->prev;
 }
 queue_delete_cetrain_position(queue, j);
 
 //queue_change_certain_position(queue, j, atoi(input_seq-1));
 
 // queue->tail->prev->next = NULL;
 // queue->tail = queue->tail->prev;
 }
 queue->node_num--;
 return 0;
 }
 int queue_delete_cetrain_position(queue* queue, int pos){
 node* l = (node*) malloc(sizeof(node));
 node* k = (node*) malloc(sizeof(node));
 if(pos == 0){ // if tail OK
 queue->tail->prev->next = NULL;
 queue->tail = queue->tail->prev;
 }else if(pos != queue->node_num -1){ // if middle
 l = queue->tail;
 for(int i=0; i < pos; i++){
 l = l->prev;
 }
 l->prev->next=l->next;
 l->next->prev = k->prev;
 free(l);
 free(k);
 }
 return 0;
 }
 
 int optimal_return_position(int ref_num,char* input)
 {
 int pos=0;
 char* seq = input;
 while(atoi(seq) != '\n'){
 if(ref_num == atoi(seq))
 return pos;
 seq++;
 pos++;
 }
 return 0;
 }
 */