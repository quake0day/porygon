//
//  main.c
//  porygon
//
//  Created by quake0day on 11/12/12.
//  Copyright (c) 2012 Si Chen. All rights reserved.
//


#include "main.h"
/* global variables */
int FRAMES = 5; // set the number of avaliable frames. Default is 5
char *POLICY_R = "FIFO";
int POLICY = 0; // set the replacement policy 0:FIFO 1:LFU 2:LRU-STACK 3:LRU-CLOCK 4:LRU-REF8
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
                        if(c != '\n'){  // if not add this, certain BUG may happen.
                        //printf("%c",c);
                        seq[i] = c;
                        i++;
                        SEQ_SIZE++;
                        }
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
                char *str5="LRU-REF8";
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
                else if(strcmp(POLICY_R,str5)==0){
                    POLICY=4;
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
        char* count = input_seq;
        while(*count != '\n'){
            SEQ_SIZE++;
            count++;
        }
#ifdef DEBUG
        printf("%d\n",SEQ_SIZE);
#endif
    }
    
#ifdef DEBUG
    printf("input sequence:%s\n",input_seq);
#endif
    struct timeval tv;
    struct timeval tv1;
    struct timeval tv2;
    
    if(POLICY == 0){ //FIFO
        int FRAME_1 = FRAMES;
        queue* q = (queue*) malloc(sizeof(queue));
        gettimeofday(&tv, NULL);
        do_fifo(q, input_seq, FRAMES);
        gettimeofday(&tv1, NULL);
        do_optimal(input_seq, FRAME_1);
        gettimeofday(&tv2, NULL);
        //printf("\n%d",PAGE_REPLACEMENT);
        printf("# of page replacements with FIFO        :%d \n",PAGE_REPLACEMENT);
        printf("# of page replacements with OPTIMAL     :%d \n",PAGE_REPLACEMENT_OPT);
    }
    else if(POLICY == 1){ //LFU
        int FRAME_1 = FRAMES;
        gettimeofday(&tv, NULL);
        do_lfu(input_seq, FRAMES);
        gettimeofday(&tv1, NULL);
        do_optimal(input_seq, FRAME_1);
        gettimeofday(&tv2, NULL);
        printf("# of page replacements with LFU         :%d \n",PAGE_REPLACEMENT);
        printf("# of page replacements with OPTIMAL     :%d \n",PAGE_REPLACEMENT_OPT);
    }
    else if(POLICY == 2){ //LRU-STACK
        int FRAME_1 = FRAMES;
        Queue *pq = InitQueue();
        gettimeofday(&tv, NULL);
        do_lru_stack(pq, input_seq, FRAMES);
        gettimeofday(&tv1, NULL);
        do_optimal(input_seq, FRAME_1);
        gettimeofday(&tv2, NULL);
        printf("# of page replacements with LRU-STACK   :%d \n",PAGE_REPLACEMENT);
        printf("# of page replacements with OPTIMAL     :%d \n",PAGE_REPLACEMENT_OPT);
    }
    else if(POLICY == 3){ // LRU-CLOCK
        int FRAME_1 = FRAMES;
        Queue *pq = InitQueue();
        gettimeofday(&tv, NULL);
        do_lru_clock(pq, input_seq, FRAMES);
        gettimeofday(&tv1, NULL);
        do_optimal(input_seq, FRAME_1);
        gettimeofday(&tv2, NULL);
        printf("# of page replacements with LRU-CLOCK   :%d \n",PAGE_REPLACEMENT);
        printf("# of page replacements with OPTIMAL  	:%d \n",PAGE_REPLACEMENT_OPT);
    }
    else if (POLICY == 4){ // LRU-REF8 
        int FRAME_1 = FRAMES;
        Queue *pq = InitQueue();
        gettimeofday(&tv, NULL);
        do_lru_ref8(pq, input_seq, FRAMES);
        gettimeofday(&tv1, NULL);
        do_optimal(input_seq, FRAME_1);
        gettimeofday(&tv2, NULL);
        printf("# of page replacements with LRU-REF8    :%d \n",PAGE_REPLACEMENT);
        printf("# of page replacements with OPTIMAL     :%d \n",PAGE_REPLACEMENT_OPT);
    }
    float penalty = ((PAGE_REPLACEMENT-PAGE_REPLACEMENT_OPT)*1.0 / (PAGE_REPLACEMENT_OPT))*100;
    printf("%% page replacement penalty using %s \t:%4.1f%%\n\n",POLICY_R,penalty);

    int k1 = (uint)tv1.tv_usec - (uint)tv.tv_usec;
    int k2 = (uint)tv2.tv_usec - (uint)tv1.tv_usec;
    float faster = ((k2-k1)*1.0 / (k2))*100;
    printf("Total time to run %s algorithm        : %d msec\n",POLICY_R,k1);
    printf("Total time to run Optimal algorithm     : %d msec\n",k2);
    printf("%s is %4.1f%% faster than Optimal algorithm. \n",POLICY_R,faster);
    
    return 0;
}



