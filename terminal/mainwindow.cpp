#include "include/mainwindow.hpp"

UserInterface::UserInterface()
{
    setWindowTitle("Terminal");
    resize(900, 600);

    addToolBar(GetToolBar());
    addDockWidget(Qt::LeftDockWidgetArea, GetNewsFeed());
    addDockWidget(Qt::RightDockWidgetArea, GetReviewMenu());
    addDockWidget(Qt::RightDockWidgetArea, GetStockList());
}