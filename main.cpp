#include "widget.h"
#include <QApplication>
#include <QObject>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget* w = new Widget();
    w->show();
    return a.exec();
}