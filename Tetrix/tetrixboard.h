/****************************************************************************
 **
 ** Copyright (C) 2004-2008 Trolltech ASA. All rights reserved.
 **
 ** This file is part of the documentation of the Qt Toolkit.
 **
 ** This file may be used under the terms of the GNU General Public
 ** License versions 2.0 or 3.0 as published by the Free Software
 ** Foundation and appearing in the files LICENSE.GPL2 and LICENSE.GPL3
 ** included in the packaging of this file.  Alternatively you may (at
 ** your option) use any later version of the GNU General Public
 ** License if such license has been publicly approved by Trolltech ASA
 ** (or its successors, if any) and the KDE Free Qt Foundation. In
 ** addition, as a special exception, Trolltech gives you certain
 ** additional rights. These rights are described in the Trolltech GPL
 ** Exception version 1.2, which can be found at
 ** http://www.trolltech.com/products/qt/gplexception/ and in the file
 ** GPL_EXCEPTION.txt in this package.
 **
 ** Please review the following information to ensure GNU General
 ** Public Licensing requirements will be met:
 ** http://trolltech.com/products/qt/licenses/licensing/opensource/. If
 ** you are unsure which license is appropriate for your use, please
 ** review the following information:
 ** http://trolltech.com/products/qt/licenses/licensing/licensingoverview
 ** or contact the sales department at sales@trolltech.com.
 **
 ** In addition, as a special exception, Trolltech, as the sole
 ** copyright holder for Qt Designer, grants users of the Qt/Eclipse
 ** Integration plug-in the right for the Qt/Eclipse Integration to
 ** link to functionality provided by Qt Designer and its related
 ** libraries.
 **
 ** This file is provided "AS IS" with NO WARRANTY OF ANY KIND,
 ** INCLUDING THE WARRANTIES OF DESIGN, MERCHANTABILITY AND FITNESS FOR
 ** A PARTICULAR PURPOSE. Trolltech reserves all rights not expressly
 ** granted herein.
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **
 ****************************************************************************/

#ifndef TETRIXBOARD_H
#define TETRIXBOARD_H

#include <QBasicTimer>
#include <QFrame>
#include <QPointer>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iterator>

#include "tetrixpiece.h"

using namespace std;

class QLabel;
class QPushButton;

class TetrixBoard : public QFrame {
    Q_OBJECT

public:
    TetrixBoard(char argv[], QWidget *parent = 0);

    void setNextPieceLabel(QLabel *label);
    QSize sizeHint() const;
    QSize minimumSizeHint() const;

public slots:
    void start();
    void pause();
    void keyConfig();
    void demoMode();

signals:
    void scoreChanged(int score);
    void levelChanged(int level);
    void linesRemovedChanged(int numLines);
    void piecesDropped(int numPiecesDropped);
    void totsDropped(int totNumDropped);
    void foursDropped(int fourBlockDropped);
    void fivesDropped(int fiveBlockDropped);
    void sixsDropped(int sixBlockDropped);
    void sevensDropped(int sevenBlockDropped);

protected:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void timerEvent(QTimerEvent *event);

private:

    enum {
        BoardWidth = 20, BoardHeight = 30
    };

    QLabel *createLabel(const QString &text);

    TetrixShape &shapeAt(int x, int y) {
        return board[(y * BoardWidth) + x];
    }

    int timeoutTime() {
        return 1000 / (1 + level);
    }

    int squareWidth() {
        return contentsRect().width() / BoardWidth;
    }

    int squareHeight() {
        return contentsRect().height() / BoardHeight;
    }
    void clearBoard();
    void dropDown();
    void oneLineDown();
    void pieceDropped(int dropHeight);
    void removeFullLines();
    void newPiece();
    void showNextPiece();
    bool tryMove(const TetrixPiece &newPiece, int newX, int newY);
    void drawSquare(QPainter &painter, int x, int y, TetrixShape shape);

    QBasicTimer timer;
    QPointer<QLabel> nextPieceLabel;
    bool isDemo;
    bool isStarted;
    bool isPaused;
    bool isWaitingAfterLine;
    TetrixPiece curPiece;
    TetrixPiece nextPiece;
    int curX;
    int curY;
    int numLinesRemoved;
    int numPiecesDropped;
    int totNumDropped;
    int fourBlockDropped;
    int fiveBlockDropped;
    int sixBlockDropped;
    int sevenBlockDropped;
    int score;
    int level;
    TetrixShape board[BoardWidth * BoardHeight];


    int leftVar;
    int rightVar;
    int rotRightVar;
    int dropVar;
    int mdropVar;
    int key;
    int temK;
    int pieceSize;
    char *fileName;
    string pieceStr;
    vector<string>::iterator pieceIter;
    vector<string> pieceVector;
    ifstream filestr;
    QPushButton *leftButton;
    QPushButton *rightButton;
    QPushButton *rotateButton;
    QPushButton *softDownButton;
    QPushButton *hardDownButton;
};

#endif
