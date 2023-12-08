//
// Created by Touka on 2023/12/7.
//

#ifndef MONTHVIEWTEST_H
#define MONTHVIEWTEST_H

#include <QtTest/QTest>
#include <QApplication>

class monthviewTest: public QObject
{
    Q_OBJECT
public:
    monthviewTest()=default;
    private slots:
        void testCorrectCreation();
};

#endif //MONTHVIEWTEST_H
