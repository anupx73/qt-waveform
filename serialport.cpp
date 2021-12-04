#include "serialport.h"
#include <QThread>

// demo pleth data for a single wave
// to understand you can plot these points in ms excel and see the wave
QList<float> SerialPort::demoData({-17,-18,-21,-23,-24,-22,-19,-15,-10,-5,-1,3,6,10,13,17,20,23,
                                    26,29,31,33,35,37,39,41,42,43,44,46,47,49,51,51,50,49,49,50,
                                    51,51,46,34,14,-12,-39,-62,-77,-85,-86,-82,-77,-72,-68,-62,
                                    -56,-48,-40,-33,-27,-22,-18,-16});

SerialPort::SerialPort(QObject *parent) : QObject(parent)
{

}

// running from a thread - thread started from main.cpp
void SerialPort::readSerialPort()
{
    // closeApp is not handled in this demo app
    // so this will crash the app on exiting
    while (!closeApp)
    {
        for (int i=0; i<demoData.length(); i++)
        {
            emit dataAvailable(demoData[i]);
        }
        QThread::sleep(1);
    }
}
