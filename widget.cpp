#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <QThread>

// this is to adjust the height of waveform based on serialport data
const float scalingFactor = 2.5;

// this controls scattering of waveform
const float xOffset = 1.2;

// rect to be cleared before each painting
const int clearRectWidth = 15;

// controls the waveform line thickness
const int lineWidth = 3;

// the following needs to be adjusted based on serialport sample rate
const int uiSampleRate = 30;
const int timerSpeed = 40;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    connect(&_timer, SIGNAL(timeout()), this, SLOT(redraw()));
    _timer.start(timerSpeed);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);

    _clearRect.setRect(_x, 0, clearRectWidth, this->height());

    // draw 2 points in single paint iteration to reduce overhead
    // may be this optimizes the drawing a bit.
    for (int i=0; i<2; i++)
    {
        float y = 0;
        if (!_yDrawable.isEmpty())
            y = _yDrawable.dequeue() / scalingFactor;

        QPointF endPoint(_x, y);
        _x += xOffset;

        // when reached to the width of the control
        if(_x > this->width())
        {
            _x = 0;
            endPoint.setX(_x);
            _path = QPainterPath();
            _path.moveTo(_x, y);
        }
        _path.lineTo(endPoint);
    }

//    painter.fillRect(boundingRect, QColor(Qt::yellow));
    painter.setPen(QPen(Qt::magenta, lineWidth, Qt::SolidLine, Qt::RoundCap));
    painter.setTransform(QTransform(1,0,0,-1,0,50));
    painter.drawPath(_path);
    painter.end();

    QWidget::paintEvent(event);
}

void Widget::processData(float y)
{
    if (_yRaw.size() >= uiSampleRate)
    {
        while (_yRaw.size() != 0)
        {
            _yDrawable.enqueue(_yRaw.dequeue());
        }
    }

    _yRaw.enqueue(y);
}
