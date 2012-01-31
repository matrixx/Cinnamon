/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** No Commercial Usage
** This file contains pre-release code and may not be distributed.
** You may use this file in accordance with the terms and conditions
** contained in the Technology Preview License Agreement accompanying
** this package.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights.  These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
**
**
**
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtGui/QApplication>
#include <QtOpenGL>
#include "qmlapplicationviewer.h"
#include "collectionminer.h"
#include <QDeclarativeEngine>

int main(int argc, char *argv[])
{
#ifdef OPENGL_GRAPHICSSYSTEM
    QApplication::setGraphicsSystem("opengl");
    qDebug("using opengl graphicssystem");
#endif

    QApplication app(argc, argv);
    QmlApplicationViewer viewer;

#ifndef OPENGL_GRAPHICSSYSTEM
    QGLFormat format = QGLFormat::defaultFormat();
    format.setSampleBuffers(false);
    format.setSwapInterval(1);
    QGLWidget* glWidget = new QGLWidget(format);
    glWidget->setAutoFillBackground(false);
    viewer.setViewport(glWidget);
    qDebug("using opengl viewport");
#endif
    QCoreApplication::setApplicationName("cinnamon");
    CollectionMiner miner(&viewer);
    miner.setOnline(true);
    miner.setSuffix(QCoreApplication::applicationName());
    miner.setApplicationName(QCoreApplication::applicationName());
    miner.mine();
    viewer.setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    viewer.setAttribute(Qt::WA_OpaquePaintEvent);
    viewer.setAttribute(Qt::WA_NoSystemBackground);
    viewer.setMainQmlFile(QLatin1String("qml/cinnamon/main.qml"));
    viewer.showExpanded();

    return app.exec();
}
