#include "include/newsfeed.hpp"

NewsFeed::NewsFeed()
{
    setFeatures(QDockWidget::NoDockWidgetFeatures);

    // hides title bar
    setTitleBarWidget(new QWidget);

    QWidget* container = new QWidget;
    setWidget(container);

    container->setStyleSheet("background-color: green");

    QVBoxLayout* layout = new QVBoxLayout(container);
}

QDockWidget* NewsFeed::operator()()
{
    return this;
}