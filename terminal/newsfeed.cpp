#include "include/newsfeed.hpp"

NewsFeed::NewsFeed()
{
	setFeatures(QDockWidget::NoDockWidgetFeatures);

	setWindowTitle("news sentiments");				
	setStyleSheet("QDockWidget {color: #B9CCDB; font-weight: bold; font-size: 12px}");

	main_widget = new QWidget;
	setWidget(main_widget);

	main_widget->setStyleSheet("background-color: #1E2C38");
	main_layout = new QVBoxLayout(main_widget);

	infoData = new QLabel("No Data");
	infoData->setStyleSheet("font-size: 48px; color: #152029");
	infoData->setAlignment(Qt::AlignCenter);

	main_layout->addWidget(infoData);
}

void NewsFeed::NewsFeedStart(std::string ticker)
{
	infoData->setVisible(false);

	allQVBoxLayoutWidgets = new std::vector<QWidget*>();
	allQFormLayoutWidgets = new std::vector<QWidget*>();

	GetScrollArea();

	JsonParser p;
    std::vector<NewsItem> news = std::move(p.ReadNews("NEWS_SENTIMENT_" + ticker + ".json"));

	for (int i = 0; i < news.size(); ++i)
		NewNewsBlock(news[i].title, news[i].summary, news[i].url);
}

void NewsFeed::NewsFeedReset()
{
	main_layout->removeWidget(scroll_area);

	QLayoutItem* item;

	for (QWidget* var : *allQVBoxLayoutWidgets)
	{
		while (( item = var->layout()->takeAt( 0 ) ) != nullptr)
		{
			delete item->widget();
			delete item;
		}

		delete var;
	}

	for (QWidget* var : *allQFormLayoutWidgets)
	{
		item = var->layout()->takeAt(0);

		delete item->widget();
		delete item;

		delete var;
	}

	while (( item = scroll_layout->takeAt( 0 ) ) != nullptr)
	{
		delete item->widget();
		delete item;
	}

	delete scroll_widget;

	delete allQVBoxLayoutWidgets;
	delete allQFormLayoutWidgets;
}

QDockWidget* NewsFeed::operator()()
{
	return this;
}

void NewsFeed::GetScrollArea()
{
	scroll_widget = new QWidget;
	scroll_layout = new QVBoxLayout(scroll_widget);

	scroll_layout->setSpacing(20);

	scroll_area = new QScrollArea;
	scroll_area->setAlignment(Qt::AlignTop);
	scroll_area->setFrameShape(QFrame::NoFrame);
	scroll_area->setWidgetResizable( true );
	scroll_area->setWidget(scroll_widget);
	
	main_layout->addWidget(scroll_area);
}

void NewsFeed::NewNewsBlock(std::string& title, std::string& description, std::string& href)
{
	QWidget* block_widget = new QWidget;
	QFormLayout* block_layout = new QFormLayout(block_widget);

	QWidget* td_widget = new QWidget;
	QVBoxLayout* title_description = new QVBoxLayout(td_widget);

	QString qtitle = "<a href=";
	qtitle += '\"' + href + '\"';
	qtitle += " style=\"color: white; text-decoration:none; font-size: 20px; font-weight: bold\"";
	qtitle += '>' + QString::fromStdString(title) + "</a>";

	QLabel* titl = new QLabel();
	titl->setText(qtitle);
	titl->setWordWrap(true);
	titl->setTextFormat(Qt::RichText);
	titl->setTextInteractionFlags(Qt::TextBrowserInteraction);
	titl->setOpenExternalLinks(true);

	QLabel* descrp = new QLabel(QString::fromStdString(description));
	descrp->setWordWrap(true);
	descrp->setStyleSheet("font-size: 14px;"
						  "color: white");

	title_description->addWidget(titl);
	title_description->addWidget(descrp);

	QPushButton* icon = new QPushButton;
	icon->setIcon(QIcon(QString::fromStdString(":/Resources/logo/site.png")));
	icon->setStyleSheet("border: none");
	icon->setIconSize(QSize(60, 80));

	block_layout->addRow(icon, td_widget);

	block_widget->setStyleSheet("background-color: #17232D;"
								"border-radius: 20px");

	scroll_layout->addWidget(block_widget);

	allQVBoxLayoutWidgets->push_back(td_widget);
	allQFormLayoutWidgets->push_back(block_widget);
}