#include "estop_gui.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    estop_gui w;
    w.show();

    return a.exec();
}
