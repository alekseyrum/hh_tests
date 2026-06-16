#include <iostream>
#include <vector>
#include <map>
#include <chrono>
#include <regex>

using namespace std;

struct AState {
    int price;
    std::chrono::seconds time;
};

std::vector<std::string> report(const std::vector<std::string> & lines) 
{
    std::vector<std::string> vecResult;
    std::map<std::string,AState> mPapers;
    std::map<std::string,AState>::iterator itPaper;
    std::vector<std::string>::const_iterator itLine = lines.begin();

    std::regex pattern("^(\\w{4})::(\\d+)::(\\w{2,4})::(\\d{2}:\\d{2}:\\d{2})$"); 
    std::smatch matches;

    while ( itLine != lines.end() )
    {
        if (! std::regex_search( *itLine , matches, pattern)) {
            cout << "regexp parsing not found mathces in line:" << endl;
            cout << *itLine << endl;
            itLine++;
            continue;
        }
        std::istringstream iss( matches.str(4) );
        std::chrono::seconds time_val; 
        iss >> std::chrono::parse("%H:%M:%S", time_val);
        if ( iss.fail()) {
            cout << "ERROR time parsing from string:" << matches.str(4) << endl;
            itLine++;
            continue;
        }
        int iNewPrice = std::stoi(matches.str(2));
        std::string sPaperName = matches.str(1);
        itPaper = mPapers.find( sPaperName );
        if ( itPaper == mPapers.end() ) {
            AState nS;
            nS.price = iNewPrice;
            nS.time = time_val;
            mPapers.insert( { sPaperName , nS } );
        } else {
            // PAPER already exists
            // cout << "paper exists wit time = " <<  itPaper->second.time << endl;
            if (itPaper->second.time >= time_val) {
                itLine++;
                continue;
            }
            itPaper->second.time = time_val;
            if ( matches.str(3) == "UP" ) {
                vecResult.push_back("{\"Symbol\":\"" + sPaperName + "\",\"Price\":" + std::to_string(iNewPrice) + ",\"Trend\":\"UP\"}" );
            } else {
                int iDeltaPrice = itPaper->second.price - iNewPrice;
                vecResult.push_back(sPaperName + " DOWN " + std::to_string(iDeltaPrice) );
            }
            itPaper->second.price = iNewPrice;
        }
        itLine++;
    }
    if (vecResult.size() == 0) vecResult.push_back("none");
    return vecResult;
}

int main () 
{
    // using namespace std::chrono;

/*
    vector<string> vInputData = { 
        "AAPL::100::UP::10:00:00",
        "AAPL::120::UP::10:05:00",
        "GOOG::200::DOWN::10:10:00",
        "AAPL::110::DOWN::10:15:00",
        "GOOG::210::UP::10:05:00",
        "MSFT::150::UP::10:20:00",
        "AAPL::115::UP::10:10:00"   };

    vector<string> vInputData = {
    "AAPL::150::UP::10:30:00",
    "GOOG::2800::DOWN::10:31:00" };

    vector<string> vInputData = {
        "IBMM::120::UP::13:00:00",
        "IBMM::125::UP::13:05:00",
        "IBMM::130::UP::13:10:00",
        "IBMM::135::UP::13:15:00",
        "IBMM::140::UP::13:20:00",
        "IBMM::145::UP::13:25:00",
        "IBMM::150::UP::13:30:00",
        "IBMM::155::UP::13:35:00" };

    vector<string> vInputData = {
    "INTC::60::DOWN::14:00:00",
    "INTC::58::DOWN::14:05:00",
    "INTC::56::DOWN::14:10:00",
    "INTC::54::DOWN::14:15:00",
    "INTC::52::DOWN::14:20:00",
    "INTC::50::DOWN::14:25:00",
    "INTC::48::DOWN::14:30:00",
    "INTC::46::DOWN::14:35:00" };
*/

    vector<string> vInputData = {
    "ORCL::80::UP::15:00:00",
    "ORCL::85::UP::15:05:00",
    "ORCL::90::UP::15:10:00",
    "CSCO::45::DOWN::15:15:00",
    "CSCO::43::DOWN::15:20:00",
    "CSCO::41::DOWN::15:25:00",
    "ORCL::95::UP::15:30:00",
    "CSCO::39::DOWN::15:35:00"};

    vector<string> vResult = report(vInputData);
    for ( auto ss : vResult) {
        cout << ss << endl;
    }
}
