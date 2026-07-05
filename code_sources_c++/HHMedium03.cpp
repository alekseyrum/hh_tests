
#include <iostream>
#include <vector>
#include <unordered_map>
#include <regex>

using namespace std;

class ServerLogAnalyzer {
public:
    explicit ServerLogAnalyzer(const std::vector<std::string>& lines );
    std::vector<std::string> process() const;
private:
    struct Stat { int r{0}, w{0} ; };
    std::unordered_map<std::string, Stat> stat_; 
};

std::vector<std::string> ServerLogAnalyzer::process() const
{
    std::vector<std::string> vecResult;

    std::vector<std::pair<std::string, Stat>> vec(stat_.begin(), stat_.end());
    std::sort(vec.begin(), vec.end(), [](const auto& a, const auto& b) {
        return a.first < b.first;
    });

    for (const auto & dd : vec ) {
        int iWriteLimit = (dd.second.w + dd.second.r) *0.75;
        if ( dd.second.w >= iWriteLimit) {
            vecResult.push_back( "Alert! " + dd.first + " has suspicious activity" );
        } else {
            vecResult.push_back( "{service=\"" + dd.first + "\",\"read\":" + std::to_string(dd.second.r) + ",\"write\":" + std::to_string(dd.second.w) + "}" );
        }
    }
    if ( vecResult.size() == 0 ) {
        vecResult.push_back( "none" );
    }
    return vecResult;
}

ServerLogAnalyzer::ServerLogAnalyzer(const std::vector<std::string>& lines )
{
    std::unordered_map<std::string, Stat>::iterator itElem;
    std::regex pattern("^<service=\"(\\d{5})\" data=\"(\\w{9})\" action=\"(\\w{4,5})\">"); 
    std::smatch matches;

    std::vector<std::string>::const_iterator itLine = lines.begin();
    while ( itLine != lines.end() )
    {
        if (std::regex_search( *itLine , matches, pattern)) {
            // itElem = mStates.find( matches.str(1) );
            itElem = stat_.find( matches.str(1) );
            if ( itElem == stat_.end() ) {
                Stat os;
                os.r = 0;
                os.w = 0;
                auto pIns = stat_.insert( { matches.str(1) , os } );
                itElem = pIns.first;
            } 
            if ( matches.str(3) == "read") {
                itElem->second.r++;
            } else if (matches.str(3) == "write") {
                itElem->second.w++;
            }
        }
        itLine++;
    }
}

int main () 
{

    /*
    vector<string> vInputData = {
        "<service=\"10001\" data=\"ABCDEFGHI\" action=\"read\">",
        "<service=\"10001\" data=\"JKLMNOPQR\" action=\"read\">",
        "<service=\"10001\" data=\"STUVWXYZa\" action=\"write\">",
        "<service=\"10002\" data=\"bcdefghij\" action=\"read\">"
         };
        */

    vector<string> vInputData = {     
    "<service=\"20001\" data=\"AAAAAAAAA\" action=\"write\">",
    "<service=\"20001\" data=\"BBBBBBBBB\" action=\"write\">",
    "<service=\"20001\" data=\"CCCCCCCCC\" action=\"write\">",
    "<service=\"20001\" data=\"DDDDDDDDD\" action=\"read\">",
    "<service=\"20002\" data=\"EEEEEEEEE\" action=\"read\">",
    "<service=\"20002\" data=\"FFFFFFFFF\" action=\"read\">",
    "<service=\"20002\" data=\"GGGGGGGGG\" action=\"write\">"};
    
/*
    vector<string> vInputData = {     
        "<service=\"20002\" data=\"EEEEEEEEE\" acteon=\"read\">",
        "<service=\"20002\" data=\"FFFFFF\" action=\"re\">",
        "<service=\"200\" data=\"GGGGGGGGG\" action=\"write\">" };
        

vector<string> vInputData = { 
"<service=\"29005\" data=\"ABCDEFGHI\" action=\"read\">",
"<service=\"30006\" data=\"JKLMNOPQR\" action=\"write\">",
"<service=\"29005\" data=\"STUVWXYZA\" action=\"read\">",
"<service=\"30006\" data=\"BCDEFGHIJ\" action=\"write\">",
"<service=\"29005\" data=\"KLMNOPQRS\" action=\"read\">",
"<service=\"30006\" data=\"TUVWXYZAB\" action=\"write\">",
"<service=\"29005\" data=\"CDEFGHIJK\" action=\"read\">",
"<service=\"30006\" data=\"LMNOPQRST\" action=\"write\">" };
*/

    // vector<string> vResult = report(vInputData);
    ServerLogAnalyzer ss(vInputData);
    vector<string> vResult = ss.process();
    
    for ( auto ss : vResult) {
        cout << ss << endl;
    }
}
