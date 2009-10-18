/* 
 * File:   piecegenerator.h
 * Author: ee462b21
 *
 * Created on October 17, 2009, 5:38 PM
 */

#ifndef _PIECEGENERATOR_H
#define	_PIECEGENERATOR_H
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class PieceGenerator
{
public:
    PieceGenerator();
    void openInput();
    void closeInput();
    void init(char *string);
    void getNextPiece(int pieceLoc[][2], int *pieceSize);

private:
    //char pieceStr[100];
    string pieceStr;
    fstream filestr;
    //QTextStream stream;
    int piecePos;
    //QString s;
};

#endif	/* _PIECEGENERATOR_H */

