#include "include/stockslist.hpp"

StockList::StockList()
{
	setFeatures(QDockWidget::NoDockWidgetFeatures);

	setWindowTitle("List");                
	setStyleSheet("QDockWidget {color: #B9CCDB; font-weight: bold; font-size: 12px}");

	main_widget = new QWidget;
	setWidget(main_widget);

	main_widget->setStyleSheet("background-color: #1E2C38");

	main_layout = new QVBoxLayout(main_widget);

	GetSearchBar();
	main_layout->addSpacing(10);

	GetStockList();

	table->setCellWidget(0, 0, StockCheckBox("AAPL"));
	table->setCellWidget(0, 1, new QLabel("912.2323"));
	table->setCellWidget(0, 2, new QLabel("182.2323"));
	table->setCellWidget(0, 3, new QLabel("032.2323"));
	table->setCellWidget(0, 4, new QLabel("83.2323"));
	table->setCellWidget(0, 5, new QLabel("233.2323"));

	main_layout->addSpacing(10);
	GetProceedMenu();
}

QDockWidget* StockList::operator()()
{
	return this;
}

void StockList::GetSearchBar()
{
	search = new QLineEdit;
	search->setCompleter(Completer()(":Resources/listing.txt"));
	
	search->setPlaceholderText(" Search for a ticker (For example: AAPL)");
	search->setFixedHeight(35);

	search->setStyleSheet("background-color: #243441;"
							"color: white;"
							"border-radius: 5px;"
							"font-size: 14px;"
							"font-weight: bold");

	main_layout->addWidget(search);
}

void StockList::GetStockList()
{
	// table_widget = new QWidget;
	table = new QTableWidget(5, 6);

	// 
	table->verticalHeader()->setVisible(false);
	table->setShowGrid(false);
	table->setEditTriggers(QAbstractItemView::NoEditTriggers);
	table->setSelectionBehavior(QAbstractItemView::SelectRows);
	table->setSelectionMode(QAbstractItemView::SingleSelection);
	table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

	table->setFrameStyle(QFrame::NoFrame);

	table->setStyleSheet("QHeaderView::section" 
						"{" 
							"background-color: transparent;" 
							"color: #B9CCDB;"
							"font-weight: bold;"
						"}"
	);

	ctable_name << "Ticker" << "Open" << "High" << "Low" << "Close" << "Volume"; 
	table->setHorizontalHeaderLabels(ctable_name);

	main_layout->addWidget(table);
}

QWidget* StockList::StockCheckBox(std::string stock_name)
{
	QWidget* check_box_widget = new QWidget;
	QCheckBox* check_box = new QCheckBox(QString::fromStdString(stock_name), check_box_widget);

	return check_box_widget;
}

void StockList::GetProceedMenu()
{
	proceed_widget = new QWidget;
	proceed_layout = new QHBoxLayout(proceed_widget);  

	proceed = new QPushButton("Request");
	proceed->setFixedWidth(150);
	proceed->setFixedHeight(23);
	proceed->setStyleSheet("background-color: #3374E9;"
							"color: white;"
							"border-radius: 5px;");

	QLabel* dummy = new QLabel;

	proceed_layout->addWidget(dummy, Qt::AlignRight);
	proceed_layout->addWidget(proceed, Qt::AlignRight);

	main_layout->addWidget(proceed_widget);
}