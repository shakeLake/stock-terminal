#ifndef STOCKLIST_HPP_
#define STOCKLIST_HPP_

#include <QDockWidget>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QWidget>

class StockList : public QDockWidget
{
private:
    QLineEdit* search;

    // test
    QLabel* test;

public:
    StockList();
    ~StockList() = default;

    QDockWidget* operator()();

};

#endif /* STOCKLIST_HPP_ */