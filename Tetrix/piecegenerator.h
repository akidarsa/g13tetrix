/* 
 * File:   piecegenerator.h
 * Author: ee462b21
 *
 * Created on October 17, 2009, 5:38 PM
 */

#ifndef _PIECEGENERATOR_H
#define	_PIECEGENERATOR_H

#include <QFile>
#include <QTextStream>

class PieceGenerator
{
public:
    PieceGenerator();
    void openInput();
    void closeInput();
    void init(char *string);
    void getNextPiece(int pieceLoc[][2], int *pieceSize);

private:
    QString pieceStr;
    QFile inputFile;
    QTextStream stream;
    int piecePos;
    QString s;
};

#endif	/* _PIECEGENERATOR_H */

