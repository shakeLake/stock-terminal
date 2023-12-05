#include "include/mainwindow.hpp"

UserInterface::UserInterface(int height, int width)
{
	setWindowTitle("Terminal");
	resize(width, height);

	setStyleSheet("background-color: #17232D");

	addToolBar(GetToolBar());
	addDockWidget(Qt::LeftDockWidgetArea, GetNewsFeed());
	addDockWidget(Qt::RightDockWidgetArea, GetReviewMenu());
	addDockWidget(Qt::RightDockWidgetArea, GetStockList());
}