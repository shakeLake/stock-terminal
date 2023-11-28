#ifndef MAINWINDOW_HPP_
#define MAINWINDOW_HPP_

#include <QMainWindow>
#include "toolbar.hpp"
#include "stockslist.hpp"
#include "review.hpp"

class UserInterface : public QMainWindow
{
private:
    ToolBar GetToolBar;
    StockList GetStockList;
    Review GetReviewMenu;

public:
    UserInterface();
    ~UserInterface() = default;

};

#endif /* MAINWINDOW_HPP_ */