
#include <charconv>
#include <iostream>
#include <vector>
#include <set>
using namespace std;

int process(const std::vector<std::string> & lines) 
{
    std::string_view sInputLine = lines[0];
    int delim1 = sInputLine.find(' ');
    int delim2 = sInputLine.find(' ', delim1+1);
    int iServer1, iServer2, iServer3 = 0;

    std::from_chars_result fcr;
    fcr = std::from_chars(sInputLine.data(), sInputLine.data() + delim1, iServer1);
    fcr = std::from_chars(sInputLine.data()+delim1+1, sInputLine.data() + delim2, iServer2);
    fcr = std::from_chars(sInputLine.data()+delim2+1, sInputLine.data() + sInputLine.size()-delim2, iServer3);

    int iTotalGamers = iServer1 + iServer2 + iServer3;
    set<int> setGamers;
    int iRejected = 0;

    std::vector<std::string>::const_iterator itLine = ++lines.begin();
    while (itLine != lines.end() ) {
        std::string_view curStr = *itLine;
        delim1 = curStr.find(':');
        int clid;
        // fcr = std::from_chars(curStr.data(), curStr.data() + delim1, clid);
        clid = std::stoi( string( curStr.substr(0, delim1)));
        // cout << "clid=" << clid << endl;
        std::string_view strType = curStr.substr(delim1+1, curStr.size()- delim1);

        if ( setGamers.count(clid) > 0 ) {
            if (strType == "disconnect") {
                setGamers.erase(clid);
            }
        } else {
            if (strType == "connect") {
                if ( setGamers.size() < iTotalGamers ) {
                    setGamers.insert(clid);
                } else {
                    iRejected++;
                }
            }
        }
        itLine++;
    }
    return iRejected;
}

int main()
{
    /*
   vector<string> vInputData = { 
    "2 2 2",
    "100001:connect",
    "100002:connect",
    "100003:connect",
    "100004:connect",
    "100005:connect",
    "100006:connect",
    "100007:connect" };

   vector<string> vInputData = { 
    "1 2 1",
    "100001:connect",
    "100002:connect",
    "100001:connect",
    "100003:connect",
    "100001:disconnect",
    "100004:connect",
    "100005:disconnect" };

   vector<string> vInputData = { 
    "1 1 1",
    "700000:connect",
    "700001:connect",
    "700002:connect",
    "700003:connect",
    "700004:connect",
    "700005:connect",
    "700006:connect",
    "700007:connect" };

vector<string> vInputData = {
    "5 5 5",
    "800000:disconnect",
    "800001:disconnect",
    "800002:disconnect",
    "800000:connect",
    "800001:connect",
    "800002:connect",
    "800003:connect",
    "800004:connect"};

    vector<string> vInputData = {
    "2 2 2",
    "900000:connect",
    "900001:connect",
    "900002:connect",
    "900003:connect",
    "900000:disconnect",
    "900004:connect",
    "900001:disconnect",
    "900005:connect",
    "900002:disconnect",
    "900006:connect",
    "900003:disconnect",
    "900007:connect" };

    vector<string> vInputData = {
    "3 3 3",
    "300000:connect",
    "300001:connect",
    "300002:connect",
    "300003:connect",
    "300004:connect",
    "300005:connect",
    "300006:connect",
    "300007:connect",
    "300008:connect",
    "300009:connect",
    "300010:connect",
    "300011:connect" };

    vector<string> vInputData = {
    "20 20 20",
    "40000:connect",
    "40001:connect",
    "40002:connect",
    "40003:connect",
    "40004:connect",
    "40005:connect",
    "40006:connect",
    "40007:connect",
    "40008:connect",
    "40009:connect",
    "40010:connect",
    "40011:connect",
    "40012:connect",
    "40013:connect"};
*/

    vector<string> vInputData = {
    "1 1 2",
    "600000:connect",
    "600001:connect",
    "600002:connect",
    "600003:connect",
    "600004:connect",
    "600005:connect",
    "600000:disconnect",
    "600006:connect",
    "600001:disconnect",
    "600007:connect",
    "600002:disconnect",
    "600008:connect",
    "600003:disconnect",
    "600009:connect"};


    int iResult = process(vInputData);
    cout << iResult << endl;
}
