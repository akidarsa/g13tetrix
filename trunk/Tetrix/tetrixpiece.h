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

 #ifndef TETRIXPIECE_H
 #define TETRIXPIECE_H

 #include <QFile>
 #include <QTextStream>
 #include "piecegenerator.h"

 enum TetrixShape { NoShape };

 class TetrixPiece
 {
 public:

     void setRandomShape();
     void setShape(TetrixShape shape);
     
     TetrixShape shape() const { return pieceShape; }
     int sizeOf() {return pieceSize;}
     int x(int index) const { return coords[index][0]; }
     int y(int index) const { return coords[index][1]; }
     int minX() const;
     int maxX() const;
     int minY() const;
     int maxY() const;
     TetrixPiece rotatedLeft() const;
     TetrixPiece rotatedRight() const;

 private:
     void setX(int index, int x) { coords[index][0] = x; }
     void setY(int index, int y) { coords[index][1] = y; }

     TetrixShape pieceShape;
     int pieceSize;
     int pieceLoc[7][2];
     int coords[][2];

 };

 #endif