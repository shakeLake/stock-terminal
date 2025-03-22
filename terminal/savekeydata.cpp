#include "include/savekeydata.hpp"

SaveKeyData::SaveKeyData()
{
    cin.open("localaccess");
    cout.open("localaccess", std::ofstream::app);
}

SaveKeyData::~SaveKeyData()
{
    cout.close();
    cin.close();
}

void SaveKeyData::MarkTickerAsLocalAccessible(std::string ticker)
{
    cout << '\n' << ticker; 
}

std::list<std::string>& SaveKeyData::GetTickersList()
{
    while (!cin.eof())
    {
        std::string ticker;
        cin >> ticker; 

        if (!ticker.empty())
            tickerList.push_back(ticker);
    }

    return tickerList;
}