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

PieceGenerator::PieceGenerator() {
    //QString fileName = QString(QLatin1String(string));
    //inputFile = new QFile(&fileName);
//printf("You created a PG\n"); 
}

void PieceGenerator::init(char *string) {
printf("you are in init\n");

//QString s;
s = string;
//printf("%s\n", s);
     //QFile inputFile((const QString) &s);
	//QFile inputFile(string);
	QFile inputFile(s);
}


void PieceGenerator::openInput() {
    if ( inputFile.open(QIODevice::ReadOnly) ) {
        printf("File Opened...");
    } else {
        printf("Failed to open piece file...");
    }
    QTextStream stream(&inputFile);

}

void PieceGenerator::closeInput() {
    inputFile.close();
}

void PieceGenerator::getNextPiece(int pieceLoc[][2],int *pieceSize) {
    if ( !stream.atEnd() ) {
       pieceStr = stream.readLine();
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
