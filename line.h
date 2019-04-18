/*
 * =====================================================================================
 *
 *       Filename:  line.h
 *
 *    Description:  Line header
 *
 *        Version:  1.0
 *        Created:  18/04/2019 13:04:42
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Paulo Bodnarchuki, paulo.henrique.cruz@usp.br
 *         Nº USP:  9790944
 *
 * =====================================================================================
 */

#ifndef LINE_H
#define LINE_H


typedef struct LINE {
    int xA, yA;
    int xB, yB;
} LINE;

void createLines(LINE ***lines, int lines_qtd);

void destroyLines(LINE ***lines, int lines_qtd);

LINE orderLine(LINE *line);

void lineMaker(LINE *line, int xmin, int ymin, int xmax, int ymax);

#endif
