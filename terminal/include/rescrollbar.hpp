#ifndef RESCROLLBAR_HPP_
#define RESCROLLBAR_HPP_

#include <QScrollBar>
#include <QChart>

#include <iostream>

class MyScrollBar : public QScrollBar
{
private:
    QChart* chart;

private:
    void wheelEvent(QWheelEvent*);

public:
    MyScrollBar(QChart*);
    ~MyScrollBar() = default;

};

#endif /* RESCROLLBAR_HPP_ */