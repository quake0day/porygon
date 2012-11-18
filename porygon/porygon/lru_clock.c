//
//  lru_clock.c
//  porygon
//
//  Created by quake0day on 11/17/12.
//  Copyright (c) 2012 quake0day. All rights reserved.
//

#include <stdio.h>
#include "main.h"



int do_lru_clock(Queue* queue,char* input_seq, int frames){
    Queue* queue_p = queue;
    for(int i=0; i<SEQ_SIZE; i++){
        if(*input_seq != ' '){
            int ref_num = atoi(input_seq);
            if(ref_num >= 0){
                int exist = QueueTraverse(queue_p,ref_num, judge_if_exists);
                if(exist == 0){ // not exists
                    if(FRAMES-- <= 0){ // queue already full
                        int k=0;
                        int status = 1;
                        int pos = 0;
                        while(status){
                            if(pos > queue->size){
                                pos = 0;
                            }
                            status = Pop_or_HP_decrease(queue, &k, pos);
                            pos ++;
                        }
                        //Pop(queue,&k);
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
                        else if( k == ref_num){
                            Push(queue,ref_num);
                            queue->rear->HP = 1;
                        }
                        size--;
                    }
                }
            }
        }
        input_seq++;
    }
    return 0;
}


