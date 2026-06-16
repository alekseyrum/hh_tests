#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

std::vector<std::string> report(const std::vector<std::string> & lines) 
{
    std::vector<std::string> vecResult;

    for (auto cc : lines) {
        std::string_view sv(cc);

        int delim1 = sv.find("->");
        int delim2 = sv.find("->", delim1+2);
        int delim3 = sv.find("->", delim2+2);
        if (delim3 == std::string_view::npos) {
            cout << "fields too few" << endl;
            return vecResult;
        }
        std::string svGameid(sv.substr(0,delim1) );
        std::string svName(sv.substr(delim1+2, delim2-delim1-2) ) ; 
        std::string svRate(sv.substr(delim2+2, delim3-delim2-2) );
        std::string svLoad(sv.substr(delim3+2, sv.size()-delim3) );
       
        int iGameID = 0 ; 
        if ( svGameid.empty() ) { 
            svGameid = "unknown" ;
        } else {
            iGameID = std::stoi(svGameid);
        }
        
        int iRate = std::stoi(svRate);
        int iDownLoad = std::stoi(svLoad);
        std::string sMsg = "low";

        if (iGameID < 1000 || iGameID > 9999 || svName.length() < 5 || svName.length() > 40 
            || ! std::all_of(svName.begin(), svName.end(), [](unsigned char c) { return std::isalpha(c); })
            || iRate < 0 || iRate > 100
            || iDownLoad < 0 || iDownLoad > 10000000
            ) { 
            if ( svName.empty() ) { svName = "unknown"; }
            vecResult.push_back(svGameid + ":" + svName + ":incorrect data");
        } else {
            if (iRate >= 90 || iDownLoad > 100000) { sMsg = "top"; }
            else if ( (iRate > 60 && iRate <= 89) || (iDownLoad > 50000 && iDownLoad < 99999 ) ) 
            { sMsg = "middle"; }
            vecResult.push_back(svGameid + ":" + svName + ":" + sMsg);
        }         
    }  
    return vecResult; 
}

int main () {
    /*
    vector<string> vInputData = {
        "1001->StardewValley->95->50000",
        "1002->Terrarie->85->75000",
        "1003->HollowKnight->72->300000",
        "1004->Celeste->20->15000",
        "1007->SuperNova->75->25000"};
        

    vector<string> vInputData = {
    "1001->Stardew Valley->95->500000",
    "1002->->85->75000",
    "1003->HollowKnight->92->300000",
    "->->80->45000"};
*/

    vector<string> vInputData = {
        "1001->Amani->95->500000",
        "1002->Baraka->85->75000",
        "1003->  Chidi->92->300000",
        "1004->Dakarai->80->45000",
        "1005->Ekon->65->50000",
        "1006->Femi->90->200000",
        "1007->lfe->75->60000",
        "1008->Jabari->80->80000",
        "1009->Kato->70->70000",
        "1010->Lebo->60->40000",
        "1011->Mandla->155->30000",
        "1012->Nia->50->20000"};
        

    vector<string> vResult = report(vInputData);
    for ( auto ss : vResult) {
        cout << ss << endl;
    }
}


