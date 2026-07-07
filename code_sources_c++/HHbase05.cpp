
#include <iostream>
#include <sstream>
#include <vector>
#include <numeric>      // for std::accumulate
#include <cmath>        // for std::round
#include <map>
#include <algorithm>
using namespace std;

std::vector<std::string>
find_popular_cities (   const std::string & cities_line, 
                        const std::string& hotels_line ) 
{
    std::string sWorkStr = cities_line;
    std::transform(sWorkStr.begin(), sWorkStr.end(), sWorkStr.begin(), 
        [](unsigned char c) { return std::tolower(c); } );

    std::stringstream sDwnl(sWorkStr);
    std::string sVal;

    map<string, int> mapCities;
    map<string, int>::iterator itCity;
    while ( std::getline(sDwnl,sVal, ',' ) ) {
        itCity = mapCities.find(sVal);
        if ( itCity == mapCities.end() ) {
            mapCities.insert( {sVal , 1 } );
        } else {
            itCity->second++;
        }
    }

    std::vector<std::pair<std::string, int>> vec(mapCities.begin(), mapCities.end());
    std::sort(vec.begin(), vec.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
    });

    int iMaxCount = vec[0].second;
    int iCurPos = 0;
    std::vector<std::string> retRes;
    while ( iCurPos < vec.size() && vec[iCurPos].second == iMaxCount ) {
        std::string sCityName = "" ;
        sCityName += std::toupper( vec[iCurPos].first[0] ) ; 
        sCityName += vec[iCurPos].first.substr(1,vec[iCurPos].first.length()-1);
        retRes.push_back( sCityName + " " + std::to_string(vec[iCurPos].second) );
        iCurPos++;
    }
    return retRes;
}


int main() {

    /*
    std::string line1 = "Paris,London,London,Paris,Paris,London";
    std::string line2 = "HotelA,HotelB,HotelC,HotelD,HotelE,HotelF";

    std::string line1 = "Lyon";
    std::string line2 = "HotelDieu";
    
    std::string line1 = "Paris,Paris,Paris,Lyon,Lyon,Lyon,Lyon,Marseille,Marseille,Toulouse,Toulouse,Toulouse";
    std::string line2 = "Ritz1,Ritz2,Ritz3,Dieu1,Dieu3,PetitNice1,PetitNice2,PetitNice3,GrandBalcon1,GrandBalcon2,GrandBalcon3";

    std::string line1 = "Lille,Lille,Lille,Lille,Lille,Lille,Lille,Lille,Lille,Lille,Lille,Lille";
    std::string line2 = "LHermitage1,LHermitage2,LHermitage3,LHermitage4,LHermitage5,LHermitage6,LHermitage7,LHermitage8,LHermitage9,LHermitage10,LHermitage11,LHermitage12";
    */

    std::string line1 = "Strasbourg,Strasbourg,Strasbourg,Strasbourg,Montpellier,Montpellier,Montpellier,Montpellier,Rouen,Rouen,Rouen,Rouen";
    std::string line2 = "Rohan1,Rohan2,Rohan3,Rohan4,Domus1,Domus2,Domus3,Domus4,Mercure1,Mercure2,Mercure3,Mercure4";

    std::vector<std::string> vResult;
    vResult = find_popular_cities(line1 , line2);

    for (std::string val : vResult) {
        std::cout << val << std::endl;
    }
}

