
#include <QApplication>
#include "amainwindow.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    awv::AMainWindow w;
    w.show();

    return a.exec();
}



