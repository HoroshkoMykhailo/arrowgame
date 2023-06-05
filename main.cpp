#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Arrowgame w;
    w.show();

    return a.exec();
}
