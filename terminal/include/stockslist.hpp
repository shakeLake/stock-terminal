#ifndef STOCKLIST_HPP_
#define STOCKLIST_HPP_

#include <iostream>

#include <QApplication>
#include <QScreen>

#include <QDockWidget>
#include <QWidget>
#include <QLineEdit>
#include <QTableWidget>
#include <QCheckBox>
#include <QLabel>
#include <QStringList>
#include <QPushButton>

#include <QVBoxLayout>
#include <QHeaderView>

#include <QFile>

#include <unordered_map>
#include <map>

#include "review.hpp"
#include "newsfeed.hpp"
#include "completer.hpp"
#include "savekeydata.hpp"
#include "../../api/include/client.hpp"

using GET = Client;

class StockList : public QDockWidget
{
	Q_OBJECT
private:
	QWidget* main_widget;
	QVBoxLayout* main_layout;

	// Main
	Review* reviewMenu;
	NewsFeed* newsFeed;

	// search
	QLineEdit* search;
	QCompleter* completer;
	std::unordered_map<std::string, int> taken;
	std::unordered_map<int, std::string> tableCellToTicker;
	int cellPointer = 0;

	// list
	SaveKeyData localAccess;
	QWidget* table_widget;
	QTableWidget* table;
	QStringList ctable_name;

	// save widgets to change their color
	std::map<std::pair<int , int>, QWidget*> cell_data;
	std::pair<int, int> prev_widget = std::make_pair(-1, -1);

private:
	void GetSearchBar();
	void GetStockList();
	QWidget* StockCheckBox(std::string);
	void ShowPastTickers();

private slots:
	void TakeFromLineEdit();
	void ActivateCheckWidget(int, int);

public:
	StockList();
	~StockList() = default;

	QDockWidget* operator()(Review*, NewsFeed*);

};

#endif /* STOCKLIST_HPP_ */