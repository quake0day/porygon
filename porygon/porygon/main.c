//
//  main.c
//  porygon
//
//  Created by quake0day on 11/12/12.
//  Copyright (c) 2012 Si Chen. All rights reserved.
//

#include <stdio.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include "main.h"
#define LENGTH 102400
/* global variables */
int FRAMES = 5; // set the number of avaliable frames. Default is 5
char *POLICY_R = NULL;
int POLICY = 0; // set the replacement policy 0:FIFO 1:LRU 2:LRU-STACK 3:LRU-CLOCK 4:LRU-REF8
int INPUT_SOURCE = 0; // set the input source 0:STDIN 1:FILE
int HELP = 0; // print usage? 0:disable 1:enable
int SEQ_SIZE = 0;
int PAGE_REPLACEMENT=0;
int PAGE_REPLACEMENT_OPT=0;

int main(int argc, char **argv)
{
    // trace user choice
    int choice;
    char *input_file = "";
    FILE *fp;
    char seq[LENGTH]= "";
    char *input_seq = seq;
    int c;
    int i;

    // read and parse user's choice
    while((choice = getopt(argc,argv,"hf:r:i:")) != -1)
    {
        switch(choice){
            case 'f':
                FRAMES = atoi(optarg);
                break;
            case 'h':
                HELP = 1;
                break;
            case 'i':
                input_file = optarg;
                fp=fopen(input_file,"r");
                if(fp != 0){ //file exist
                    i = 0;
                    while((c = fgetc(fp)) != EOF){ //read it word by word
                        //printf("%c",c);
                        seq[i] = c;
                        i++;
                        SEQ_SIZE++;
                    }
                    INPUT_SOURCE = 1;
                }else{
                    fprintf(stderr,"No such file or file unable to read!\n");
                    return 1;
                }
                
                #ifdef DEBUG
                printf("input sequence:%s",input_seq);
                #endif
                break;
            case 'r':
                //printf(" enter 0 for FCFS and 1 for SJF");
                POLICY_R = optarg;
                char *str1="FIFO";
                char *str2="LFU";
                char *str3="LRU-STACK";
                char *str4="LRU-CLOCK";
                if(strcmp(POLICY_R,str1)==0)
                {
                    POLICY=0;
                }
                else if(strcmp(POLICY_R,str2)==0){
                    POLICY=1;
                }
                else if(strcmp(POLICY_R,str3)==0){
                    POLICY=2;
                }
                else if(strcmp(POLICY_R,str4)==0){
                    POLICY=3;
                }
                else{
                    fprintf(stderr,"Unknown option\n");
                    fprintf(stderr,"Using FIFO replacement policy.\n");
                }
                break;
                
            case '?':
                if(optopt == 'r' || optopt == 'i' || optopt == 'f')
                    fprintf(stderr,"Option -%c requires an argument.",optopt);
                else
                    fprintf(stderr,"Unknown option");
                return 1;
            default:
                abort();
                
        }
    }
    
#ifdef DEBUG
    printf("Frames:%d\n",FRAMES);
    printf("Policy:%s\n",POLICY_R);
    printf("Policy Num:%d\n",POLICY);
    printf("input-file:%s\n",input_file);
#endif
    
    // If program run in the help mode
    // print usage summary
    // and exit....
    if(HELP == 1){
        printf("virtualmem [−h] [-f available-frames] [−r replacement-policy] [−i input_file] \n");
        printf("Avaliable replacement policy: \n FIFO\n LFU\n LRU-STACK\n LRU-CLOCK\n LRU-REF8\n");
        return 0;
    }
    
    
    if(INPUT_SOURCE == 0){
        printf("Please input the page reference sequence, end with ENTER:");
        fgets(seq,sizeof(seq),stdin);
    }
    
#ifdef DEBUG
    printf("input sequence:%s",input_seq);
#endif
    
    if(POLICY == 0){
        queue* q = (queue*) malloc(sizeof(queue));
        do_fifo(q, input_seq, FRAMES);
    }
    
    
    return 0;
}
int do_fifo(queue* queue,char* input_seq, int frames){
    fifo_init_queue(queue);
   
    for(int i=0; i<SEQ_SIZE; i++){
        int ref_num = atoi(input_seq);
        if(ref_num >= 0){
            int exist = fifo_seek_queue(queue,ref_num);
            if(exist == 1){ // not exists
                if(FRAMES-- <= 0){
                    fifo_remove_node(queue);
                }
                node* new_node = (node*) malloc(sizeof(node));
                new_node->ref_num = atoi(input_seq);
                fifo_add_node(new_node, queue);
                PAGE_REPLACEMENT ++;
            }
        }
        input_seq++;
    }
    printf("PAGE REPLACEMENT TIME:%d",PAGE_REPLACEMENT);
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
