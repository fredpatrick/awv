
#include <QApplication>
#include "bmainwindow.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    awv::BMainWindow w;
    w.show();

    return a.exec();
}



