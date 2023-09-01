
#include <QApplication>
#include "cmainwindow.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    awv::CMainWindow w;
    w.show();

    return a.exec();
}



