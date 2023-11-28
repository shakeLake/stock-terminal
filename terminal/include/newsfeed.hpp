#ifndef NEWSFEED_HPP_
#define NEWSFEED_HPP_

#include <QDockWidget>
#include <QVBoxLayout>
#include <QWidget>

class NewsFeed : public QDockWidget
{
public:
    NewsFeed();
    ~NewsFeed() = default;

    QDockWidget* operator()();

};

#endif /* NEWSFEED_HPP_ */