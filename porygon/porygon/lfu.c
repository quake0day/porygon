//
//  lfu.c
//  porygon
//
//  Created by quake0day on 11/17/12.
//  Copyright (c) 2012 quake0day. All rights reserved.
//

#include <stdio.h>
#include "main.h"

int do_lfu(char* input_seq, int FRAMES)
{
    //printf("%c",seq[4]);
    // record the frame length since FRAMES will change afterward
    // need change do_fifo to make sure FRAMES remains the same
    int ini_length = FRAMES;
    
    // this is the queue
    int array[LENGTH]={0};
    int old_array[LENGTH]={-1};
    // if input length is bigger than array length it will cause buffer overflow
    if(LENGTH <= ini_length){
        fprintf(stderr, "Fatal ERROR! Please try to use a less length for input seq");
        abort();
    }
    // let a pointer point to this queue's beginning
    int *k = array;
    int *old = old_array;
    old++; // let -1 be the first element
    // SEQ_SIZE is twice larger than the actual input length (count the space)
    for(int i =0; i < SEQ_SIZE; i++){
        // try to get the sequence num
        if(*input_seq != ' '){
            int ref_num = atoi(input_seq);
            // if you can get (means not space)
            if(ref_num >=0){
                // first, try to see if this number is already in the queue
                int pos = lfu_seek_array(array, ref_num, ini_length);
                if(pos == -1){ //not exist
                    if(FRAMES-- <= 0){ // array already full
                        // we need find a victim to replace it
                        long vic_num = lfu_find_vic(array, old, ini_length);
                        lfu_replace_vic(array, vic_num,ref_num,ini_length);
                        PAGE_REPLACEMENT ++;
                    }
                    else{ // array not full
                        *k = ref_num; // set array to this input sequence number
                        k++; // done, move to the next cell in array
                    }
                }
                *old = ref_num; // save the input seq as history
                old++;
            }
        }
        input_seq++; // move to the next input
    }
    
    return 0;
}
int lfu_replace_vic(int* m, long vic_num, int ref_num, int array_length){
    for(int i = 0; i < array_length; i++){
        if(*m == vic_num){
            while(i< array_length){
                *m = *(m+1);
                m++;
                i++;
            }
            *--m = ref_num;
            return 0;
        }
        m++;
    }
    return -1;
}
/* try to find a victim to replace it out */
/* k: the array we need to search and maintain
 seq: the input sequence we need to search
 length: frame size which indicate how many space we can use in k
 */
long lfu_find_vic(int* k, int* old, int length){
    int* m = k;
    long vic= 999999999999999;
    int j=0;
    long dead_num=0;
    for(int i = 0; i < length; i++){
        int time = 0;
        time = lfu_peer_history(m, old);
        if(time < vic){
            vic = time;
            j = i;
            dead_num = *m;
        }
        m++;
    }
    
    return dead_num;
}

int lfu_peer_history(int* k, int* old){
    int time=0;
    int *old_array = old;
    while(*old_array != -1)
    {
        if (*k == *old_array){
            time++;
            old_array--;
        }
        else{
            old_array--;
        }
    }
    return time;
}
int lfu_seek_array(int* k, int ref_num, int length)
{
    for(int j = 0; j < length; j++){
        if(*k == ref_num)
            return j;
        k++;
    }
    return -1;
}