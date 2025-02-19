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


