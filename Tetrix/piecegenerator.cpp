/* 
 * File:   piecegenerator.cpp
 * Author: ee462b21
 * 
 * Created on October 17, 2009, 5:38 PM
 */

#include "piecegenerator.h"
#include <math.h>
#include <fstream.h>
#include <vector>
#include <iostream>
#include <string>

PieceGenerator::PieceGenerator() {
    //QString fileName = QString(QLatin1String(string));
    //inputFile = new QFile(&fileName);
//printf("You created a PG\n"); 
}

void PieceGenerator::init(char *string) {
    printf("you are in init\n");
    fstream filestr;
    filestr.open (string, fstream::in);
    if (filestr.is_open()) {
        printf("File Opened...");
    } else {
        printf("Failed to open piece file...");
    }
}


void PieceGenerator::openInput() {
	/**printf("you are in init\n");
    if ( inputFile.open(QIODevice::ReadOnly) ) {
        printf("File Opened...");
    } else {
        printf("Failed to open piece file...");
    }**/
    //QTextStream stream(&inputFile, );
}

void PieceGenerator::closeInput() {
    filestr.close();
}

void PieceGenerator::getNextPiece(int pieceLoc[][2],int *pieceSize) {
    if ( !filestr.eofbit ) {
       getline(filestr, pieceStr);
    }

    *pieceSize = (int)sqrt(pieceStr.length());
    piecePos = 0;

    for(int i = 0; i < *pieceSize; i++) {
        for(int j = 0; j < *pieceSize; j++) {
           if ( ((int)pieceStr[(i * (*pieceSize)) + j]) == 1 ) {
               pieceLoc[piecePos][0]=j;
               pieceLoc[piecePos][1]=i;
               piecePos++;
           }
        }
    }
}
