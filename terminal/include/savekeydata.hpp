#ifndef SAVEKEYDATA_HPP_
#define SAVEKEYDATA_HPP_

#include <fstream>
#include <list>
#include <iostream>

class SaveKeyData
{
private:
    std::ofstream cout;
    std::ifstream cin;

    std::list<std::string> tickerList;

public:
    SaveKeyData();
    ~SaveKeyData();

    void MarkTickerAsLocalAccessible(std::string);
    std::list<std::string>& GetTickersList();

};

#endif /* SAVEKEYDATA_HPP_ */