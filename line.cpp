/*
 * =====================================================================================
 *
 *       Filename:  line.cpp
 *
 *    Description:  Line structure implementation
 *
 *        Version:  1.0
 *        Created:  18/04/2019 13:08:57
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Paulo Bodnarchuki, paulo.henrique.cruz@usp.br
 *         Nº USP:  9790944
 *
 * =====================================================================================
 */

#include <stdlib.h>
#include "line.h"

void createLines(LINE ***lines, int lines_qtd) {
    
    (*lines) = (LINE **) malloc(lines_qtd * sizeof(LINE *));
    for(int i = 0; i < lines_qtd; i++) {
        (*lines)[i] = (LINE *) malloc(sizeof(LINE));
    }

}

void destroyLines(LINE ***lines, int lines_qtd) {
    
    for(int i = 0; i < lines_qtd; i++) {
        free((*lines)[i]);
    }
    free(*lines);

    *lines = NULL;
}

LINE orderLine(LINE *line) {
    LINE ordered;

    if(line->xB < line->xA) {
        ordered.xA = line->xB;
        ordered.yA = line->yB;
        ordered.xB = line->xA;
        ordered.yB = line->yA;
    } else {
        ordered = *line;
    }

    return ordered;
}

void lineMaker(LINE *line, int xmin, int ymin, int xmax, int ymax) {
    line->xA = xmin;
    line->xB = xmax;
    line->yA = ymin;
    line->yB = ymax;
}
