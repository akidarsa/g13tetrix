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

 #include <QtGui>
 #include <QMessageBox>
 #include "tetrixboard.h"
 #include "tetrixkey.h"
 #include <fstream>
 #include <vector>
 #include <iostream>
 #include <string>
 #include <iterator>


 TetrixBoard::TetrixBoard(char argv[], QWidget *parent)
     : QFrame(parent)
 {
     setFrameStyle(QFrame::Panel | QFrame::Sunken);
     setFocusPolicy(Qt::StrongFocus);
     isStarted = false;
     isPaused = false;
     isDemo = false;
     clearBoard();
     filestr.open(argv, ios::in);

     if (filestr.is_open()) {
        printf("File Opened...\n");
     } else {
        printf("Failed to open piece file... \n");
     }

     while (filestr) {
            getline(filestr, pieceStr);
            pieceVector.push_back(pieceStr);
    }

    pieceIter = pieceVector.begin();

    leftVar = Qt::Key_Left;
    rightVar = Qt::Key_Right;
    rotRightVar = Qt::Key_Up;
    dropVar = Qt::Key_D;
    mdropVar= Qt::Key_Space;


    pieceSize = (*pieceIter).length();
    nextPiece.setShape(*(pieceIter++));
 }

 void TetrixBoard::setNextPieceLabel(QLabel *label)
 {
     nextPieceLabel = label;
 }

 QSize TetrixBoard::sizeHint() const
 {
     return QSize(BoardWidth * 15 + frameWidth() * 2,
                  BoardHeight * 15 + frameWidth() * 2);
 }

 QSize TetrixBoard::minimumSizeHint() const
 {
     return QSize(BoardWidth * 5 + frameWidth() * 3,
                  BoardHeight * 5 + frameWidth() * 2);
 }

 void TetrixBoard::start()
 {
     if (isPaused)
         return;

     isStarted = true;
     isWaitingAfterLine = false;
     isDemo = false;
     numLinesRemoved = 0;
     numPiecesDropped = 0;
     totNumDropped = 0;
     score = 0;
     level = 1;
     printf("Start initialized... \n");

	 /**
	 fourBlockDropped = 0;
	 fiveBlockDropped = 0;
	 sixBlockDropped = 0;
	 sevenBlockDropped = 0;
	 **/


     emit linesRemovedChanged(numLinesRemoved);
     emit scoreChanged(score);
     emit levelChanged(level);
     emit piecesDropped(numPiecesDropped);
     emit totsDropped(totNumDropped);

     clearBoard();
     printf("Board cleared.... \n");

/**	emit foursDropped(fourBlockDropped);
	emit fivesDropped(fiveBlockDropped);
	emit sixsDropped(sixBlockDropped);
	emit sevensDropped(sevenBlockDropped);
**/
   
     newPiece();  
     timer.start(timeoutTime(), this);  
 }

 void TetrixBoard::pause()
 {
     if (!isStarted)
         return;

     isPaused = !isPaused;
     if (isPaused) {
         timer.stop();
     } else {
         timer.start(timeoutTime(), this);
     }
     update();
 }

 void TetrixBoard::paintEvent(QPaintEvent *event)
 {
     QFrame::paintEvent(event);

     QPainter painter(this);
     QRect rect = contentsRect();

     if (isPaused) {
         painter.drawText(rect, Qt::AlignCenter, tr("Pause"));
         return;
     }

/** implement isDemo **/
	if (isDemo)
	{
         painter.drawText(rect, Qt::AlignCenter, tr("~~Demo Mode~~"));
	}

     int boardTop = rect.bottom() - BoardHeight*squareHeight();

     for (int i = 0; i < BoardHeight; ++i) {
         for (int j = 0; j < BoardWidth; ++j) {
             TetrixShape shape = shapeAt(j, BoardHeight - i - 1);
             if (shape != NoShape)
			 {
                 drawSquare(painter, rect.left() + j * squareWidth(),
                            boardTop + i * squareHeight(), shape);
			 }
         }
     }

     if (curPiece.shape() != NoShape) {
         for (int i = 0; i < curPiece.sizeOf(); ++i) {
             int x = curX + curPiece.x(i);
             int y = curY - curPiece.y(i);
             drawSquare(painter, rect.left() + x * squareWidth(),
                        boardTop + (BoardHeight - y - 1) * squareHeight(),
                        curPiece.shape());
         }
     }
 }

 void TetrixBoard::keyPressEvent(QKeyEvent *event)
 {
     if (!isStarted || isPaused || isDemo || curPiece.shape() == NoShape) {
         QFrame::keyPressEvent(event);
         return;
     }

	 if((event->key()) == leftVar)
	 {
         tryMove(curPiece, curX - 1, curY);
	 }
	 else if((event->key()) == rightVar)
	 {
         tryMove(curPiece, curX + 1, curY);
	 }
	 else if((event->key()) == rotRightVar)
	 {
         tryMove(curPiece.rotatedRight(), curX, curY);
	 }
	 else if((event->key()) == dropVar)
	 {
         oneLineDown();
	 }
	 else if((event->key()) == mdropVar)
	 {
         dropDown();
	 }
	 else
	 {
         QFrame::keyPressEvent(event);
	 }

 }

 void TetrixBoard::timerEvent(QTimerEvent *event)
 {
     if (event->timerId() == timer.timerId()) {
         if (isWaitingAfterLine) {
             isWaitingAfterLine = false;
             newPiece();
             timer.start(timeoutTime(), this);
         } else {
             oneLineDown();
         }
     } else {
         QFrame::timerEvent(event);
     }
 }

 void TetrixBoard::clearBoard()
 {
     for (int i = 0; i < BoardHeight * BoardWidth; ++i)
         board[i] = NoShape;
 }

 void TetrixBoard::dropDown()
 {
     int dropHeight = 0;
     int newY = curY;
     while (newY > 0) {
         if (!tryMove(curPiece, curX, newY - 1))
             break;
         --newY;
         ++dropHeight;
     }
     pieceDropped(dropHeight);
 }

 void TetrixBoard::oneLineDown()
 {
     if (!tryMove(curPiece, curX, curY - 1))
         pieceDropped(0);
 }

 void TetrixBoard::pieceDropped(int dropHeight)
 {
     for (int i = 0; i < curPiece.sizeOf(); ++i) {
         int x = curX + curPiece.x(i);
         int y = curY - curPiece.y(i);
         shapeAt(x, y) = curPiece.shape();
     }

     ++numPiecesDropped;
     if (numPiecesDropped % 25 == 0) {
         ++level;
         timer.start(timeoutTime(), this);
         emit levelChanged(level);
     }

     score += dropHeight + 7;
     emit scoreChanged(score);
     removeFullLines();

     if (!isWaitingAfterLine);
         newPiece();
 }

 void TetrixBoard::removeFullLines()
 {
     int numFullLines = 0;

     for (int i = BoardHeight - 1; i >= 0; --i) {
         bool lineIsFull = true;

         for (int j = 0; j < BoardWidth; ++j) {
             if (shapeAt(j, i) == NoShape) {
                 lineIsFull = false;
                 break;
             }
         }

         if (lineIsFull) {
             ++numFullLines;
             for (int k = i; k < BoardHeight - 1; ++k) {
                 for (int j = 0; j < BoardWidth; ++j)
                     shapeAt(j, k) = shapeAt(j, k + 1);
             }
             for (int j = 0; j < BoardWidth; ++j)
                 shapeAt(j, BoardHeight - 1) = NoShape;
         }
     }

     if (numFullLines > 0) {
         numLinesRemoved += numFullLines;
         score += 10 * numFullLines;
         emit linesRemovedChanged(numLinesRemoved);
         emit scoreChanged(score);

         timer.start(500, this);
         isWaitingAfterLine = true;
         curPiece.setShape(NoShape);
         update();
     }
 }

 void TetrixBoard::newPiece()
 {
     QMessageBox lossmessage;
     curPiece = nextPiece;
     pieceSize = (*pieceIter).length();
     nextPiece.setShape(*(pieceIter++));
     showNextPiece();
     curX = BoardWidth / 2 + 1;
     curY = BoardHeight - 1 + curPiece.minY();

     if (!tryMove(curPiece, curX, curY)) {
        curPiece.setShape(NoShape);
        timer.stop();
        isStarted = false;
            lossmessage.setText("You lost the game!");
            lossmessage.setStandardButtons(QMessageBox::Ok);
            lossmessage.setDefaultButton(QMessageBox::Ok);
            lossmessage.exec();
	numLinesRemoved = 0;
	numPiecesDropped = 0;
	totNumDropped = 0;
	score = 0;
	level = 0;
	isDemo = false;

	 /**
	 fourBlockDropped = 0;
	 fiveBlockDropped = 0;
	 sixBlockDropped = 0;
	 sevenBlockDropped = 0;
	 **/

	clearBoard();
	nextPieceLabel->clear();
     }

/** emit foursDropped(fourBlockDropped);
 *     emit fivesDropped(fiveBlockDropped);
 *         emit sixsDropped(sixBlockDropped);
 *             emit sevensDropped(sevenBlockDropped);
 *             **/

     emit linesRemovedChanged(numLinesRemoved);
     emit scoreChanged(score);
     emit levelChanged(level);
	 emit piecesDropped(numPiecesDropped);
	 emit totsDropped(totNumDropped);
 }

 void TetrixBoard::showNextPiece()
 {
     if (!nextPieceLabel)
         return;

     int dx = nextPiece.maxX() - nextPiece.minX() + 1;
     int dy = nextPiece.maxY() - nextPiece.minY() + 1;

     QPixmap pixmap(dx * squareWidth(), dy * squareHeight());
     QPainter painter(&pixmap);
     painter.fillRect(pixmap.rect(), nextPieceLabel->palette().background());

     for (int i = 0; i < pieceSize; i++) {
	 totNumDropped++;
	 emit totsDropped(totNumDropped);		
         int x = nextPiece.x(i) - nextPiece.minX();
         int y = nextPiece.y(i) - nextPiece.minY();
         drawSquare(painter, x * squareWidth(), y * squareHeight(),
                    nextPiece.shape());
     }
     nextPieceLabel->setPixmap(pixmap);
 }

 bool TetrixBoard::tryMove(const TetrixPiece &newPiece, int newX, int newY)
 {
     for (int i = 0; i < 4; ++i) {
         int x = newX + newPiece.x(i);
         int y = newY - newPiece.y(i);
         if (x < 0 || x >= BoardWidth || y < 0 || y >= BoardHeight)
             return false;
         if (shapeAt(x, y) != NoShape)
             return false;
     }

     curPiece = newPiece;
     curX = newX;
     curY = newY;
     update();
     return true;
 }

 void TetrixBoard::drawSquare(QPainter &painter, int x, int y, TetrixShape shape)
 {
     static const QRgb colorTable[8] = {
         0x000000, 0xCC6666, 0x66CC66, 0x6666CC,
         0xCCCC66, 0xCC66CC, 0x66CCCC, 0xDAAA00
     };

     QColor color = colorTable[int(shape)];
     painter.fillRect(x + 1, y + 1, squareWidth() - 1, squareHeight() - 1,
                      color);

     painter.setPen(color.light());
     painter.drawLine(x, y + squareHeight() - 1, x, y);
     painter.drawLine(x, y, x + squareWidth() - 1, y);

     painter.setPen(color.dark());
     painter.drawLine(x + 1, y + squareHeight() - 1,
                      x + squareWidth() - 1, y + squareHeight() - 1);
     painter.drawLine(x + squareWidth() - 1, y + squareHeight() - 1,
                      x + squareWidth() - 1, y + 1);
 }

void TetrixBoard::keyConfig()
{
	TetrixKey dialog;
	pause();
	dialog.exec();
	leftVar = dialog.getKey(TetrixKey::LEFT);
	rightVar = dialog.getKey(TetrixKey::RIGHT);
	rotRightVar = dialog.getKey(TetrixKey::ROTATE);
	dropVar = dialog.getKey(TetrixKey::SOFTDOWN);
	mdropVar = dialog.getKey(TetrixKey::MAGICDOWN);

	pause();
}

 QLabel *TetrixBoard::createLabel(const QString &text)
	 {
		      QLabel *lbl = new QLabel(text);
			  lbl->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
			  return lbl;
	 }

void TetrixBoard::demoMode()
{
	if(!isStarted)
	{
		start();
	}
	isDemo = !isDemo;
}
