#include "gitfu.h"
#include <QtGui/QApplication>

#include <stdio.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GitFu w;
    w.show();
    return a.exec();
}
