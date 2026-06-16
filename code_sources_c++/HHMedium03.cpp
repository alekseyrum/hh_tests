
#include <iostream>
#include <vector>
#include <map>
#include <regex>

using namespace std;

struct OpStatus {
    int read;
    int write;
};

std::vector<std::string> report(const std::vector<std::string> & lines) 
{
    std::vector<std::string> vecResult;
    std::map<string, OpStatus> mStates;
    std::map<string, OpStatus>::iterator itElem;

    std::regex pattern("^<service=\"(\\d{5})\" data=\"(\\w{9})\" action=\"(\\w{4,5})\">"); 
    std::smatch matches;

    std::vector<std::string>::const_iterator itLine = lines.begin();
    while ( itLine != lines.end() )
    {
        if (std::regex_search( *itLine , matches, pattern)) {
            itElem = mStates.find( matches.str(1) );
            if ( itElem == mStates.end() ) {
                OpStatus os;
                os.read = 0;
                os.write = 0;
                auto pIns = mStates.insert( { matches.str(1) , os } );
                itElem = pIns.first;
            } 
            if ( matches.str(3) == "read") {
                itElem->second.read++;
            } else if (matches.str(3) == "write") {
                itElem->second.write++;
            }
        }
        itLine++;
    }
    // write-out to result:
    for (const auto & dd : mStates) {
        int iWriteLimit = (dd.second.write + dd.second.read) *0.75;
        if ( dd.second.write >= iWriteLimit) {
            vecResult.push_back( "Alert! " + dd.first + " has suspicious activity" );
        } else {
            vecResult.push_back( "{service=\"" + dd.first + "\",\"read\":" + std::to_string(dd.second.read) + ",\"write\":" + std::to_string(dd.second.write) + "}" );
        }
    }
    if ( vecResult.size() == 0 ) {
        vecResult.push_back( "none" );
    }
    return vecResult;
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
        
    vector<string> vInputData = {     
    "<service=\"20001\" data=\"AAAAAAAAA\" action=\"write\">",
    "<service=\"20001\" data=\"BBBBBBBBB\" action=\"write\">",
    "<service=\"20001\" data=\"CCCCCCCCC\" action=\"write\">",
    "<service=\"20001\" data=\"DDDDDDDDD\" action=\"read\">",
    "<service=\"20002\" data=\"EEEEEEEEE\" action=\"read\">",
    "<service=\"20002\" data=\"FFFFFFFFF\" action=\"read\">",
    "<service=\"20002\" data=\"GGGGGGGGG\" action=\"write\">"};
    

    vector<string> vInputData = {     
        "<service=\"20002\" data=\"EEEEEEEEE\" acteon=\"read\">",
        "<service=\"20002\" data=\"FFFFFF\" action=\"re\">",
        "<service=\"200\" data=\"GGGGGGGGG\" action=\"write\">" };
        */

vector<string> vInputData = { 
"<service=\"29005\" data=\"ABCDEFGHI\" action=\"read\">",
"<service=\"30006\" data=\"JKLMNOPQR\" action=\"write\">",
"<service=\"29005\" data=\"STUVWXYZA\" action=\"read\">",
"<service=\"30006\" data=\"BCDEFGHIJ\" action=\"write\">",
"<service=\"29005\" data=\"KLMNOPQRS\" action=\"read\">",
"<service=\"30006\" data=\"TUVWXYZAB\" action=\"write\">",
"<service=\"29005\" data=\"CDEFGHIJK\" action=\"read\">",
"<service=\"30006\" data=\"LMNOPQRST\" action=\"write\">" };


    vector<string> vResult = report(vInputData);
    for ( auto ss : vResult) {
        cout << ss << endl;
    }
}
