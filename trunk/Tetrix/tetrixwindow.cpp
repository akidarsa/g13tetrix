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

 #include "tetrixboard.h"
 #include "tetrixwindow.h"

 TetrixWindow::TetrixWindow()
 {
     board = new TetrixBoard;

     nextPieceLabel = new QLabel;
     nextPieceLabel->setFrameStyle(QFrame::Box | QFrame::Raised);
     nextPieceLabel->setAlignment(Qt::AlignCenter);
     board->setNextPieceLabel(nextPieceLabel);

     scoreLcd = new QLCDNumber(5);
     scoreLcd->setSegmentStyle(QLCDNumber::Filled);
     levelLcd = new QLCDNumber(2);
     levelLcd->setSegmentStyle(QLCDNumber::Filled);
     linesLcd = new QLCDNumber(5);
     linesLcd->setSegmentStyle(QLCDNumber::Filled);
	 piecesLcd = new QLCDNumber(5);
	 piecesLcd->setSegmentStyle(QLCDNumber::Filled);
	 foursLcd = new QLCDNumber(5);
	 foursLcd->setSegmentStyle(QLCDNumber::Filled);
	 fivesLcd = new QLCDNumber(5);
	 fivesLcd->setSegmentStyle(QLCDNumber::Filled);
	 sixsLcd = new QLCDNumber(5);
	 sixsLcd->setSegmentStyle(QLCDNumber::Filled);
	 sevensLcd = new QLCDNumber(5);
	 sevensLcd->setSegmentStyle(QLCDNumber::Filled);
	 totLcd = new QLCDNumber(5);
	 totLcd->setSegmentStyle(QLCDNumber::Filled);



     startButton = new QPushButton(tr("&Start"));
     startButton->setFocusPolicy(Qt::NoFocus);
     quitButton = new QPushButton(tr("&Quit"));
     quitButton->setFocusPolicy(Qt::NoFocus);
     pauseButton = new QPushButton(tr("&Pause"));
     pauseButton->setFocusPolicy(Qt::NoFocus);
     keyButton = new QPushButton(tr("&Key Config"));
     keyButton->setFocusPolicy(Qt::NoFocus);
     demoButton = new QPushButton(tr("&Demo Mode"));
     demoButton->setFocusPolicy(Qt::NoFocus);


	 connect(keyButton, SIGNAL(clicked()), board, SLOT(keyConfig())); //I have to change this when i know what it's supposed to do
	 connect(demoButton, SIGNAL(clicked()), board, SLOT(demoMode())); //Change this when demo mode is done.

     connect(startButton, SIGNAL(clicked()), board, SLOT(start()));
     connect(quitButton , SIGNAL(clicked()), qApp, SLOT(quit()));
     connect(pauseButton, SIGNAL(clicked()), board, SLOT(pause()));
     connect(board, SIGNAL(scoreChanged(int)), scoreLcd, SLOT(display(int)));
     connect(board, SIGNAL(levelChanged(int)), levelLcd, SLOT(display(int)));
     connect(board, SIGNAL(linesRemovedChanged(int)), linesLcd, SLOT(display(int)));
	 connect(board, SIGNAL(piecesDropped(int)), piecesLcd, SLOT(display(int)));
	 connect(board, SIGNAL(foursDropped(int)), foursLcd, SLOT(display(int)));
	 connect(board, SIGNAL(fivesDropped(int)), fivesLcd, SLOT(display(int)));
	 connect(board, SIGNAL(sixsDropped(int)), sixsLcd, SLOT(display(int)));
	 connect(board, SIGNAL(sevensDropped(int)), sevensLcd, SLOT(display(int)));
	 connect(board, SIGNAL(totsDropped(int)), totLcd, SLOT(display(int)));

     QGridLayout *layout = new QGridLayout;
     layout->addWidget(createLabel(tr("NEXT")), 0, 0);
     layout->addWidget(nextPieceLabel, 1, 0);
	 layout->addWidget(createLabel(tr("Total Pieces Dropped")), 2, 0);
	 layout->addWidget(piecesLcd, 3, 0);
     //
	 layout->addWidget(createLabel(tr("Total Number of Square")), 5, 0);
     layout->addWidget(totLcd, 6, 0);
     layout->addWidget(createLabel(tr("LEVEL")), 8, 0);
     layout->addWidget(levelLcd, 9, 0);
     layout->addWidget(startButton, 11, 0);
	 layout->addWidget(keyButton, 12, 0);
	 layout->addWidget(demoButton,13,0);
     layout->addWidget(board, 0, 1, 14, 1);
     layout->addWidget(createLabel(tr("SCORE")), 0, 2);
     layout->addWidget(scoreLcd, 1, 2);
	 //Mod starts
	 layout->addWidget(createLabel(tr("Four")),2,2);
	 layout->addWidget(foursLcd, 3,2);
	 layout->addWidget(createLabel(tr("Five")), 4,2);
	 layout->addWidget(fivesLcd, 5,2);
	 layout->addWidget(createLabel(tr("Six")), 6,2);
	 layout->addWidget(sixsLcd, 7,2);
	 layout->addWidget(createLabel(tr("Seven")), 8,2);
	 layout->addWidget(sevensLcd, 9,2);
	 //Trial Mod Ends
     layout->addWidget(createLabel(tr("LINES REMOVED")), 10, 2);
     layout->addWidget(linesLcd, 11, 2);
     layout->addWidget(quitButton, 12, 2);
     layout->addWidget(pauseButton, 13, 2);
     setLayout(layout);

     setWindowTitle(tr("Tetrix"));
     resize(550, 380);
 }

 QLabel *TetrixWindow::createLabel(const QString &text)
 {
     QLabel *lbl = new QLabel(text);
     lbl->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
     return lbl;
 }
