#include "include/mainwindow.hpp"

UserInterface::UserInterface() : GetReviewMenu("fl1.json")
{
	setWindowTitle("Terminal");
	showFullScreen();
	showMaximized();

	setStyleSheet("background-color: #17232D");

	addToolBar(GetToolBar());
	addDockWidget(Qt::LeftDockWidgetArea, GetNewsFeed());
	addDockWidget(Qt::RightDockWidgetArea, GetReviewMenu());
	addDockWidget(Qt::RightDockWidgetArea, GetStockList());
}