
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <charconv>
#include <map>
using namespace std;

std::vector<std::string> generate_report(const std::vector<std::string> & lines) 
{
    std::vector<std::string> vecResult;
    std::map<string, int> mapWorkers;

    for (const std::string &word : lines) {
        std::string_view sv(word);
        int delim1 = sv.find(';');
        int delim2 = sv.find(';', delim1+1);
        int delim3 = sv.find(';', delim2+1);
        if (delim3 == std::string_view::npos) {
            continue;
        }
        std::string_view svName = sv.substr(0,delim1);
        std::string_view svYear = sv.substr(delim1+1, delim2-delim1-1);
        std::string_view svCountry = sv.substr(delim2+1, delim3-delim2-1);
        std::string_view svProject = sv.substr(delim3+1, sv.size()-delim3);
        // cout << "name:" << svName << " year:" << svYear << " contry:" << svCountry << " proj:" << svProject << endl;
        if ( svName.size() > 40 || svCountry.size() > 40 || svCountry.size() < 2) { 
            cout << "wrong field length:" << svName << " or " << svCountry << endl;
            continue; 
        }
        if ( ! std::all_of(svName.begin(), svName.end(), [](unsigned char c) { return std::isalpha(c); } ) )  {
            cout << "wrong name:" << svName << endl;
            continue; 
        }
        int iYearVal = 0;
        std::from_chars_result fcr = std::from_chars(svYear.data(), svYear.data() + svYear.size() , iYearVal );
        if ( iYearVal < 1960 || iYearVal > 2007) {
            cout << "wrong year:" << iYearVal << endl;
            continue;
        }

        if ( ! std::all_of(svCountry.begin(), svCountry.end(), [](unsigned char c) { return std::isalpha(c); } ) )  {
            cout << "wrong country:" << svCountry << endl;
            continue; 
        }
        // - - - [field ProjectID] - - -
        if ( svProject.size() != 5 || ! std::all_of(svProject.begin(), svProject.begin()+2, [](unsigned char c) { return (c >= 'A' && c <= 'Z');} ) ) {
            cout << "wrong project format:" << svProject << endl;
            continue;
        }    
        if ( ! std::all_of(svProject.begin()+3, svProject.begin()+5, [](unsigned char c) { return std::isdigit(c); } ) ) {
            cout << "wrong project format:" << svProject << endl;
            continue;
        }   
        // here all ok:
        std::map<string,int>::iterator itWorkers = mapWorkers.find( std::string(svCountry) );
        if ( itWorkers == mapWorkers.end() ) {
            mapWorkers.insert( { std::string(svCountry), 1 } );
        } else {
            itWorkers->second++;
        }
    }

    if ( mapWorkers.size() == 0 ) {
        return {"none:0"};
    }

    std::vector<std::pair<std::string, int>> vec4Sort(mapWorkers.begin(), mapWorkers.end());
    std::sort(vec4Sort.begin(), vec4Sort.end(), [](const auto& a, const auto& b) {
        if (a.second != b.second) return a.second > b.second;
        return a.first < b.first;
    });
    for (auto cc : vec4Sort) {
        vecResult.push_back( cc.first + ":" + std::to_string(cc.second) );
    }
    return vecResult;
}

int main () {

    /*
    vector<string> vInputData = { 
    "Smith;1985;USA;AB123",
    "Johnson;1990;Canada;CD456",
    "Williams;1978;USA;EF789",
    "Brown;1995;UK;GH012",
    "Davis;1982;Canada;IJ345" };
    
    vector<string> vInputData = { 
    "Smith;1950;USA;AB123",
    "Johnson;1990;C;CD456",
    "Williams1978;none;EF789",
    "Brown;1995;UK;GH0123",
    "Davis;1982;Canada;IJ34"};
    */

    vector<string> vInputData = {
    "VanLandeghem;1987;SanMarino;MN678",
    "DeConinck;1973;Monaco;OP901",
    "VanDePutte;1990;VaticanCity;QR234",
    "Verstappen;2003;Iceland;ST567",
    "VanDerAa;1971;Malta;UV890",
    "DeBock;1984;Cyprus;WX123",
    "VanOvermeire;1996;Andorra;YZ456",
    "Verhaeghe;1969;Liechtenstein;AB789",
    "VanSteen;1981;SanMarino;CD012",
    "DePaepe;1975;Monaco;EF345",
    "VanHulle;1998;VaticanCity;GH678",
    "Verdonck;2002;Iceland;IJ901"};


    vector<string> vResult = generate_report(vInputData);
    for ( auto ss : vResult) {
        cout << ss << endl;
    }
}

