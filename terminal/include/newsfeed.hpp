#ifndef NEWSFEED_HPP_
#define NEWSFEED_HPP_

#include <QWidget>
#include <QLabel>
#include <QPushButton>

#include <QDockWidget>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QScrollArea>

class NewsFeed : public QDockWidget
{
private:
    QWidget* main_widget;
    QVBoxLayout* main_layout;

    // scroll area
    QWidget* scroll_widget;
    QVBoxLayout* scroll_layout;
    QScrollArea* scroll_area;

private:
    void NewNewsBlock(std::string&, std::string&, std::string&);
    void GetScrollArea();

public:
    NewsFeed();
    ~NewsFeed() = default;

    QDockWidget* operator()();

};

#endif /* NEWSFEED_HPP_ */