#include <QApplication>
#include "view/startwin.h"
#include "view/playvideowin.h"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    CStartWin w;
    w.show();
    return a.exec();
}
