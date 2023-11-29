#include "include/mainwindow.hpp"

UserInterface::UserInterface(int height, int width)
{
    setWindowTitle("Terminal");
    resize(width, height);

    addToolBar(GetToolBar());
    addDockWidget(Qt::LeftDockWidgetArea, GetNewsFeed());
    addDockWidget(Qt::RightDockWidgetArea, GetReviewMenu());
    addDockWidget(Qt::RightDockWidgetArea, GetStockList());
}