#include "include/completer.hpp"

QCompleter* Completer::operator()(std::string path)
{
	QFile file(QString::fromStdString(path));

	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		std::cerr << "Can't open listing.txt" << '\n';
		return nullptr;
	}

	QTextStream in(&file);
	while (!in.atEnd()) 
	{
		QString line = in.readLine();
		wordlist.append(line);
	}

	file.close();

	QCompleter* comp = new QCompleter(wordlist);
	comp->setCaseSensitivity(Qt::CaseInsensitive);

	comp->popup()->setStyleSheet("background-color: #243441;"
								 "color: white;"
								 "border-radius: 5px;");

	comp->popup()->verticalScrollBar()->setStyleSheet("QScrollBar::add-line" 
														"{"
															"border: none;"
														"}"
														"QScrollBar::sub-line"
														"{"
															"border: none;"
														"}"
														"QScrollBar::handle:vertical"
														"{"
															"background: white;"
															"border-radius: 2px;"
														"}"
														"QScrollBar:vertical"
														"{"
															"width: 7px;"
														"}"
	);

	return comp;
}