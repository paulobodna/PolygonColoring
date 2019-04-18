/*
 * =====================================================================================
 *
 *       Filename:  node.h
 *
 *    Description:  Node header
 *
 *        Version:  1.0
 *        Created:  18/04/2019 13:16:17
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Paulo Bodnarchuki, paulo.henrique.cruz@usp.br
 *         Nº USP:  9790944
 *
 * =====================================================================================
 */
#ifndef NODE_H
#define NODE_H


#include "line.h"

typedef struct NODE {
//    int id;
    int ymax;
    float xmin;
    float coeficiente;
    NODE *next;
} NODE;

int max(int a, int b);

int min(int a, int b);

void initializeNode(NODE *node, LINE line);

void printNode(NODE *node);

#endif
