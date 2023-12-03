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

    GetScrollArea();

    std::string titl = "Apple Is Far Less Important to Berkshire Hathaway Than You Think";
    std::string desc = "What is Warren Buffett-led Berkshire Hathaway really worth?";
    std::string url = "http://example.com/";
    NewNewsBlock(titl, desc, url);
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
	scroll_layout->addStretch(10);

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
    qtitle += " style=\"color: white; font-size: 20px; font-weight: bold\"";
    qtitle += '>' + QString::fromStdString(title) + "</a>";

    QLabel* titl = new QLabel();
    titl->setText(qtitle);
    titl->setTextFormat(Qt::RichText);
    titl->setTextInteractionFlags(Qt::TextBrowserInteraction);
    titl->setOpenExternalLinks(true);

    // titl->setStyleSheet("font-size: 20px;"
    //                     "font-weight: bold;"
    //                     "color: white;");

    QLabel* descrp = new QLabel(QString::fromStdString(description));
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
    block_widget->setFixedHeight(100);

    scroll_layout->addWidget(block_widget);
}