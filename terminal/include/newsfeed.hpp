#ifndef NEWSFEED_HPP_
#define NEWSFEED_HPP_

#include <QDockWidget>
#include <QVBoxLayout>
#include <QWidget>
#include <QScrollArea>

class NewsFeed : public QDockWidget
{
private:
    QWidget* main_widget;
    QVBoxLayout* main_layout;
    QScrollArea* scroll_area;

public:
    NewsFeed();
    ~NewsFeed() = default;

    QDockWidget* operator()();

};

#endif /* NEWSFEED_HPP_ */