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
	completer = Completer()(":Resources/listing.txt");
	search->setCompleter(completer);
	
	search->setPlaceholderText(" Search for a ticker (For example: AAPL)");
	search->setFixedHeight(35);

	search->setStyleSheet("background-color: #243441;"
							"color: white;"
							"border-radius: 5px;"
							"font-size: 14px;"
							"font-weight: bold");
							
	QObject::connect(completer, SIGNAL(activated(const QString&)),
					this, SLOT(TakeFromLineEdit()),
					Qt::QueuedConnection);

	main_layout->addWidget(search);
}

void StockList::GetStockList()
{
	// table_widget = new QWidget;
	table = new QTableWidget(0, 6);

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
	stock->setStyleSheet("font-weight: bold;"
						 "font-size: 15px;"
						 "color: white;");

	QCheckBox* check_box = new QCheckBox;
	check_box->setStyleSheet("QCheckBox::indicator:checked"
							 "{"
								"image: url(:/Resources/icons/checkbox_checked.png);"
							 "}"
							"QCheckBox::indicator:unchecked" 
							 "{"
								"image: url(:/Resources/icons/checkbox_unchecked.png);"
							 "}"
							 "QCheckBox::indicator"
							 "{"
							 	"width: 15px;"
							 	"height: 15px;"
							 "}"
	);

	checkbox_layout->addWidget(check_box);
	checkbox_layout->addWidget(icon);
	checkbox_layout->addWidget(stock);

	return checkbox_widget;
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
		table->setCellWidget(cellPointer, 0, StockCheckBox(line));

		QHeaderView* header = table->verticalHeader();
		header->setDefaultSectionSize(40);
		header->sectionResizeMode(QHeaderView::Fixed);

		taken[line] = cellPointer;
		cellPointer += 1;
	}
}