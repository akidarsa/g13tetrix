/* 
 * File:   piecegenerator.cpp
 * Author: ee462b21
 * 
 * Created on October 17, 2009, 5:38 PM
 */

#include "piecegenerator.h"
#include <math.h>
#include <QFile>
#include <QTextStream>


void PieceGenerator::openInput(QFile *pieceFile) {
    /*if( argc != 3 ) {
            printf("Error: Insufficient Command line arguments");
     }
     if( strcmp(argv[1],"-f") != 0) {
            printf("Error: Incorrect input file format");
    }
    printf ("File to be opened is : %s \n", argv[2]);
    */
    if ( (*pieceFile).open(QIODevice::ReadOnly) ) {
        printf("File Opened...");
    } else {
        printf("Failed to open piece file...");
    }

}

void PieceGenerator::getNextPiece(QTextStream line, int pieceLoc[][2],
        int *pieceSize) {
  //  QFile pieceFile( (argv[2]) );

    if ( !(line).atEnd() ) {
       pieceStr = (line).readLine();
    }

    *pieceSize = (int)sqrt(pieceStr.size());
    piecePos = 0;

    for(int i = 0; i < *pieceSize; i++) {
        for(int j = 0; j < *pieceSize; j++) {
           if ( pieceStr[(i * (*pieceSize)) + j].digitValue() == 1 ) {
               pieceLoc[piecePos][0]=j;
               pieceLoc[piecePos][1]=i;
               piecePos++;
           }
        }
    }
}