#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QObject>

class SerialPort : public QObject
{
    Q_OBJECT
public:
    explicit SerialPort(QObject *parent = nullptr);

private:
    static QList<float> demoData;
    bool closeApp = false;

public slots:
    void readSerialPort();

signals:
    void dataAvailable(float yPoint);
};

#endif // SERIALPORT_H
