#ifndef COMPLETER_HPP_
#define COMPLETER_HPP_

#include <QCompleter>
#include <QAbstractItemView>
#include <QScrollBar>
#include <QStringList>
#include <QFile>

#include <iostream>

class Completer
{
private:
	QStringList wordlist;

public:
	Completer() = default;
	~Completer() = default;

	QCompleter* operator()(std::string);

};

#endif /* COMPLETER_HPP_ */