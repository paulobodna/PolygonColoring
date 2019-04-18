/*
 * =====================================================================================
 *
 *       Filename:  node.cpp
 *
 *    Description:  Node implementation
 *
 *        Version:  1.0
 *        Created:  18/04/2019 13:17:09
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Paulo Bodnarchuki, paulo.henrique.cruz@usp.br
 *         Nº USP:  9790944
 *
 * =====================================================================================
 */

#include <stdio.h>
#include "node.h"

int max(int a, int b) {
    return b>a ? b:a;
}

int min(int a, int b) {
    return b>a ? a:b;
}

void initializeNode(NODE *node, LINE line) {

    node->ymax = max(line.yA, line.yB);

    if(line.yB - line.yA != 0) {
        node->coeficiente = (float) (line.xB-line.xA)/(line.yB-line.yA);
    } else node->coeficiente = 0;


    if(node->coeficiente > 0) node->xmin = line.xA;
    else node->xmin = line.xB;

    node->next = NULL;
}

void printNode(NODE *node) {
    
    printf("\n----------------\n");
//    printf("Id: %d\n", node->id);
    printf("ymax: %d\n", node->ymax);
    printf("xmin: %f\n", node->xmin);
    printf("coeficiente: %f\n", node->coeficiente);
//    if(node->next != NULL) printf("Next id: %d\n", node->next->id);
//    else printf("Next id: NULL\n");
    printf("\n----------------\n");
}
