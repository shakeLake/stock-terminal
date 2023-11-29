#include "include/newsfeed.hpp"

NewsFeed::NewsFeed()
{
    // setFeatures(QDockWidget::NoDockWidgetFeatures);

    // hides title bar
    setTitleBarWidget(new QWidget);

    main_widget = new QWidget;
    setWidget(main_widget);

    main_widget->setStyleSheet("background-color: green");

    main_layout = new QVBoxLayout(main_widget);
}

QDockWidget* NewsFeed::operator()()
{
    return this;
}