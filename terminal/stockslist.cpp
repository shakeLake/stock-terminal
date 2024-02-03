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

	ShowPastTickers();

	main_layout->addSpacing(10);
}

QDockWidget* StockList::operator()(Review* review, NewsFeed* news)
{
	reviewMenu = review;
	newsFeed = news;

	return this;
}

void StockList::ShowPastTickers()
{
	for (std::string& line : localAccess.GetTickersList())
	{
		table->insertRow( table->rowCount() );

		std::pair<int, int> bufp = std::make_pair(cellPointer, 0);
		cell_data[bufp] = StockCheckBox(line);
		table->setCellWidget(cellPointer, 0, cell_data[bufp]);

		QHeaderView* header = table->verticalHeader();
		header->setDefaultSectionSize(40);
		header->sectionResizeMode(QHeaderView::Fixed);

		taken[line] = cellPointer;
		tableCellToTicker[cellPointer] = line;
		cellPointer += 1;
	}
}

void StockList::GetSearchBar()
{
	search = new QLineEdit;
	completer = Completer()(":Resources/listing.txt");
	search->setCompleter(completer);
	
	search->setPlaceholderText(" Search for a ticker (For example: AAPL)");
	search->setFixedHeight(35);

	search->setStyleSheet(
		"background-color: #243441;"
		"color: white;"
		"border-radius: 5px;"
		"font-size: 14px;"
		"font-weight: bold"
	);
							
	QObject::connect(completer, SIGNAL(activated(const QString&)),
					 this, SLOT(TakeFromLineEdit()), Qt::QueuedConnection);

	main_layout->addWidget(search);
}

void StockList::GetStockList()
{
	// table_widget = new QWidget;
	table = new QTableWidget(0, 6);
	connect(table, SIGNAL(cellClicked(int, int)), this, SLOT(ActivateCheckWidget(int, int)));

	// 
	table->verticalHeader()->setVisible(false);
	table->setShowGrid(false);
	table->setEditTriggers(QAbstractItemView::NoEditTriggers);
	table->setSelectionBehavior(QAbstractItemView::SelectRows);
	table->setSelectionMode(QAbstractItemView::SingleSelection);
	table->setFocusPolicy(Qt::NoFocus);
	table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

	table->setFrameStyle(QFrame::NoFrame);

	table->setStyleSheet(
		"QHeaderView::section" 
		"{" 
			"background-color: transparent;" 
			"color: #B9CCDB;"
			"font-weight: bold;"
		"}"
		"QTableWidget::item"
		"{"
			"background-color: transparent"
		"}"
	);

	ctable_name << "Ticker" << "Open" << "High" << "Low" << "Close" << "Volume"; 
	table->setHorizontalHeaderLabels(ctable_name);

	main_layout->addWidget(table);
}

QWidget* StockList::StockCheckBox(std::string stock_name)
{
	QWidget* checkbox_widget = new QWidget;
	QHBoxLayout* checkbox_layout = new QHBoxLayout(checkbox_widget);

	QPushButton* icon = new QPushButton;
	QString path = ":/Resources/logolist/";
	path += stock_name + ".png";

	if (QFile::exists(path))
		icon->setIcon(QIcon(path));
	else
	{
		path = ":/Resources/logolist/";

		QString buf = QChar::fromLatin1(stock_name[0]);
		path += buf;
		path += "0.png";

		icon->setIcon(QIcon(path));
	}

	icon->setIconSize(QSize(20, 20));
	icon->setStyleSheet("border: none");

	QLabel* stock = new QLabel(QString::fromStdString(stock_name));
	stock->setStyleSheet(
		"font-weight: bold;"
		"font-size: 15px;"
		"color: white;"
	);

	checkbox_layout->addWidget(icon);
	checkbox_layout->addWidget(stock);

	return checkbox_widget;
}

void StockList::TakeFromLineEdit()
{
	QString buf = search->text();
	search->clear();

	if (buf.isEmpty())
		return;

	std::string line = buf.toStdString();
	
	if (taken.find(line) == taken.end())
	{
		table->insertRow( table->rowCount() );

		std::pair<int, int> bufp = std::make_pair(cellPointer, 0);
		cell_data[bufp] = StockCheckBox(line);
		table->setCellWidget(cellPointer, 0, cell_data[bufp]);

		QHeaderView* header = table->verticalHeader();
		header->setDefaultSectionSize(40);
		header->sectionResizeMode(QHeaderView::Fixed);

		taken[line] = cellPointer;
		tableCellToTicker[cellPointer] = line;
		cellPointer += 1;

		localAccess.MarkTickerAsLocalAccessible(line);

		// GET requestNEWS(line, "NEWS_SENTIMENT");
		// GET reqOHLC(line, "TIME_SERIES_DAILY");
	}
}

void StockList::ActivateCheckWidget(int row, int col)
{
	if (col == 0)
	{
		if (prev_widget.first != -1)
			cell_data[prev_widget]->setStyleSheet("background-color: transparent;");

		std::pair<int, int> bufp = std::make_pair(row, col);

		QWidget* widg = cell_data[bufp];
		widg->setStyleSheet("background-color: #273E4E");

		prev_widget = bufp;

		reviewMenu->ReviewStart(tableCellToTicker[row]);
		newsFeed->NewsFeedStart(tableCellToTicker[row]);
	}
}