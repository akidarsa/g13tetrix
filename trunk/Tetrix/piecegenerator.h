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

class PieceGenerator {
public:
    PieceGenerator();
    void openInput(QFile *pieceFile);
    void getNextPiece(QTextStream line, int pieceLoc[][2], int *pieceSize);

private:
    QString pieceStr;
    QTextStream line;
    int piecePos;
};

#endif	/* _PIECEGENERATOR_H */

