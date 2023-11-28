#ifndef STOCKLIST_HPP_
#define STOCKLIST_HPP_

#include <QDockWidget>
#include <QVBoxLayout>
#include <QWidget>

class StockList : public QDockWidget
{
public:
    StockList();
    ~StockList() = default;

    QDockWidget* operator()();

};

#endif /* STOCKLIST_HPP_ */