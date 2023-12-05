#ifndef MAINWINDOW_HPP_
#define MAINWINDOW_HPP_

#include <QMainWindow>

#include "toolbar.hpp"
#include "stockslist.hpp"
#include "review.hpp"
#include "newsfeed.hpp"

class UserInterface : public QMainWindow
{
private:
	ToolBar GetToolBar;
	StockList GetStockList;
	Review GetReviewMenu;
	NewsFeed GetNewsFeed;

public:
	UserInterface(int, int);
	~UserInterface() = default;

};

#endif /* MAINWINDOW_HPP_ */