#include <vector>
#include <iostream>
#include <string_view>
// #include <span>
#include <charconv>
#include <map>
#include <algorithm>
using namespace std;

struct ClientData {
    int clientid;
    int sum;
    int orders;
};

std::vector<std::string> process(const std::vector<std::string> & lines) 
// Solution::ProcessingClientData::process(const std::vector<std::string> & lines) const
{
    std::string_view str0 = lines[0];

    int delimPos = str0.find(' ');
    int monthSearch = 0;
    std::from_chars_result fcr = std::from_chars(str0.data(), str0.data() + delimPos, monthSearch);
    int Nclients = 0;
    fcr = std::from_chars(str0.data() + delimPos+1, str0.data() + str0.size(), Nclients);
    std::vector<std::string>::const_iterator itCurLine = lines.begin() + 1; //  [1]

    map<int, ClientData> mapClients;
    ClientData newOrder;
    while (itCurLine != lines.end() ) {
        std::string_view viewLine = *itCurLine;
        delimPos = viewLine.find(':');
        int iClid = 0;
        fcr = std::from_chars(viewLine.data(), viewLine.data() + delimPos, iClid);
        int delim2Pos = viewLine.find(':', delimPos+1);
        int iOrdid = 0;
        fcr = std::from_chars(viewLine.data()+delimPos+1, viewLine.data() + delim2Pos-1, iOrdid);
        int delim3Pos = viewLine.find(':', delim2Pos+1);

        std::string_view const_span( viewLine.data()+delim2Pos+1, delim3Pos - delim2Pos -1 );
        if ( const_span == "accepted") { 
            itCurLine++; 
            continue; 
        }
        int delim4Pos = viewLine.find(':', delim3Pos+1);
        int iCost = 0;
        fcr = std::from_chars(viewLine.data()+delim3Pos+1, viewLine.data() + (delim4Pos), iCost);

        int delimMonthStart = viewLine.find('-', delim3Pos+1);
        int delimMonthEnd = viewLine.find('-', delimMonthStart+1);
        int iMonth = std::stoi( string(viewLine.substr( delimMonthStart+1,  delimMonthEnd - delimMonthStart-1 ))) ;
        if (monthSearch != iMonth) {
            itCurLine++; 
            continue;
        }
        auto itClient = mapClients.find(iClid); 

        if (itClient == mapClients.end()) {
            newOrder.clientid = iClid;
            newOrder.sum = iCost;
            newOrder.orders = 1;
            mapClients.emplace(iClid , newOrder);
        } else {
            itClient->second.sum += iCost;
            itClient->second.orders++;
        }
        itCurLine++;
    }
    std::vector<std::pair<int,ClientData>> vecSort(mapClients.begin(), mapClients.end());

    std::sort(vecSort.begin(), vecSort.end(), [](const auto& a, const auto& b) {
        if ( a.second.sum != b.second.sum ) return a.second.sum > b.second.sum ;
        if ( a.second.orders != b.second.orders ) return a.second.orders > b.second.orders ;
        return a.second.clientid < b.second.clientid; 
    });
    
    vector<string> vResult;
    if (Nclients > vecSort.size()) {
        vResult.push_back("none");
        return vResult;
    }
   
    auto itRec = vecSort.begin();
    for (int iCurRec = 0; iCurRec < Nclients; iCurRec++) {
        vResult.push_back( std::to_string(itRec->first) + ";" + std::to_string(itRec->second.sum) + ";" + std::to_string(itRec->second.orders) );
        itRec++;
    }
    return vResult;
}

int main() 
{
    system("chcp 65001 > nul");
    /*
    vector<string> vInputData = { 
        "5 2",
        "10001:20001:accepted:15000:01-05-2024", "10002:20002:rejected:25000:15-05-2024",
        "10001:20003:rejected:35000:20-05-2024", "10003:20004:rejected:10000:10-05-2024",
        "10002:20005:rejected:15000:25-05-2024"
    };

    vector<string> vInputData = { 
        "6 3",
        "10001:20001:rejected:10000:01-06-2024",
        "10002:20002:accepted:20000:15-06-2024",
        "10003:20003:rejected:10000:20-06-2024"
    };

    vector<string> vInputData = { 
    "7 5",
    "10041:20041:accepted:45000:01-07-2024",
    "10042:20042:accepted:50000:05-07-2024",
    "10043:20043:accepted:55000:10-07-2024",
    "10044:20044:accepted:60000:15-07-2024",
    "10045:20045:accepted:65000:20-07-2024",
    "10046:20046:accepted:70000:25-07-2024",
    "10047:20047:accepted:75000:30-07-2024",
    "10048:20048:accepted:80000:31-07-2024" };

    vector<string> vInputData = { 
    "8 2",
    "10049:20049:rejected:85000:01-08-2024",
    "10050:20050:rejected:90000:05-08-2024",
    "10051:20051:rejected:95000:10-08-2024",
    "10050:20052:rejected:100000:15-08-2024",
    "10050:20053:rejected:105000:20-08-2024",
    "10050:20054:rejected:110000:25-08-2024",
    "10050:20055:rejected:115000:30-08-2024",
    "10056:20056:rejected:120000:31-08-2024" };

    vector<string> vInputData = { 
    "5 10",
    "10057:20057:rejected:125000:01-05-2024",
    "10058:20058:rejected:130000:05-05-2024",
    "10059:20059:accepted:135000:10-05-2024",
    "10060:20060:rejected:140000:15-05-2024",
    "10061:20061:accepted:145000:20-03-2024",
    "10062:20062:rejected:150000:25-05-2024",
    "10063:20063:accepted:155000:30-05-2024",
    "10064:20064:accepted:160000:31-03-2024",
    "10065:20065:accepted:165000:01-05-2024",
    "10066:20066:accepted:170000:05-03-2024",
    "10067:20067:accepted:175000:10-05-2024",
    "10068:20068:accepted:180000:15-05-2024"};
    */

    vector<string> vInputData = { 
    "8 2",
    "10095:20095:rejected:315000:01-08-2024",
    "10096:20096:rejected:320000:05-02-2024",
    "10097:20097:rejected:325000:10-08-2024",
    "10097:20098:accepted:330000:15-08-2024",
    "10095:20099:rejected:65000:20-08-2024",
    "10095:20100:rejected:340000:25-02-2024",
    "10095:20101:accepted:345000:30-08-2024",
    "10095:20102:rejected:350000:31-08-2024",
    "10095:20103:rejected:355000:01-02-2024",
    "10096:20104:rejected:360000:05-08-2024",
    "10096:20105:accepted:365000:10-08-2024",
    "10096:20106:rejected:370000:15-08-2024",
    "10107:20107:rejected:375000:20-08-2024",
    "10108:20108:accepted:380000:25-08-2024"};

    vector<string> vResult = process(vInputData);
    for ( auto ss : vResult) {
        cout << ss << endl;
    }
}



