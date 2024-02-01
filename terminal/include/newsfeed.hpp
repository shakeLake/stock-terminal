#ifndef NEWSFEED_HPP_
#define NEWSFEED_HPP_

#include <QWidget>
#include <QLabel>
#include <QPushButton>

#include <QDockWidget>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QScrollArea>

#include <string>

#include "../../jsonparser/parser.hpp"

class NewsFeed : public QDockWidget
{
private:
	QLabel* infoData;

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

	void NewsFeedStart(std::string /*ticker*/);

	QDockWidget* operator()();

};

#endif /* NEWSFEED_HPP_ */