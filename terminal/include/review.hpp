#ifndef REVIEW_HPP_
#define REVIEW_HPP_

#include <QDockWidget>
#include <QVBoxLayout>
#include <QWidget>
#include <QLabel>

class Review : public QDockWidget
{
public:
    Review();
    ~Review() = default;

    QDockWidget* operator()();

};

#endif /* REVIEW_HPP_ */