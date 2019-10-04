#include "servewidget.h"
#include <QApplication>
#include"clientwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ServeWidget w;
    w.show();
    ClientWidget w2;
    w2.move(0,0);

    w2.show();

    return a.exec();
}
