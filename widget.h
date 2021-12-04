#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>
#include <QQueue>
#include <QPainterPath>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    Ui::Widget *ui;

    QTimer _timer;
    QPainterPath _path;
    QRect _clearRect;

    QQueue<float> _yRaw;
    QQueue<float> _yDrawable;
    float _x = 0;

public slots:
    void redraw() { update(_clearRect); }
    void processData(float y);
};
#endif // WIDGET_H
