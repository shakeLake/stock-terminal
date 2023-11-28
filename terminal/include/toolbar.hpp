#ifndef TOOLBAR_HPP_
#define TOOLBAR_HPP_

#include <QToolBar>
#include <QLabel>

class ToolBar : public QToolBar
{
private:
    QLabel* test_label;

public:
    ToolBar();
    ~ToolBar() = default;

    QToolBar* operator()();

};

#endif /* TOOLBAR_HPP_ */