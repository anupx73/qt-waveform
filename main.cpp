#include "widget.h"
#include <QApplication>
#include <QThread>
#include <QStyle>
#include <QDesktopWidget>
#include "serialport.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QThread thread;
    SerialPort sp;
    sp.moveToThread(&thread);
    QObject::connect(&thread, SIGNAL(started()), &sp, SLOT(readSerialPort()));
    thread.start();

    Widget w;
    w.setGeometry(0, 0, 600, 120);
    w.setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, w.size(),
                                      qApp->desktop()->availableGeometry()));
    w.setStyleSheet("background-color: #000000");
    QObject::connect(&sp, SIGNAL(dataAvailable(float)), &w, SLOT(processData(float)));
    w.show();

    return app.exec();
}
