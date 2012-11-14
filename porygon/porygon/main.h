//
//  main.h
//  porygon
//
//  Created by quake0day on 11/13/12.
//  Copyright (c) 2012 Si Chen. All rights reserved.
//

#ifndef porygon_main_h
#define porygon_main_h

typedef struct queue
{
    struct node *head;
    struct node *tail;
    int node_num;
}queue;

typedef struct node
{
    int ref_num;
    struct node *next;
    struct node *prev;
    
}node;

#endif
