#include "mainwindow.h"
#include <QApplication>
#include <QPushButton>
#include <form.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w,k(100,100);
    //w.show();
    k.show();
    form m();
    m.show();

    return a.exec();
}
