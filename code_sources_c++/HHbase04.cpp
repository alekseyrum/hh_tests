
#include <iostream>
#include <sstream>
#include <vector>
#include <ranges>
#include <numeric>      // for std::accumulate
using namespace std;

int processing_input_lines (const std::string & game_ids_line , 
    const std::string & downloads_line ) 
{
    std::stringstream sDwnl(downloads_line);
    std::string sVal;

    vector<int> vLoads;
    while ( std::getline(sDwnl,sVal, ',' ) ) {
        vLoads.push_back( std::stoi(sVal) );
    }
    int sum = std::accumulate( vLoads.begin(), vLoads.end(), 0);
    float fAverage = (float)sum / vLoads.size();
    auto result_view = vLoads
                     | std::views::filter( [&fAverage](int n) { return n < fAverage; } );
    auto count = std::ranges::distance(result_view);
    int iLessCount = ((float)count/vLoads.size())*100;
    return iLessCount;
}


int main() {

    /*
    std::string line1 = "ABC,DEFX,GHISD,JKLABG";
    std::string line2 = "100,200,300,400";
 
    std::string line1 = "ADC,DEF";
    std::string line2 = "20000,20000";
 

    std::string line1 = "X1,X2,X3,X4,X5,X6,X7,X8,X9,X10";
    std::string line2 = "10,20,30,40,99960,99970,99980,99990,99995,99999";
  */
    std::string line1 = "W1,W2,W3,W4,W5,W6,W7,W8,W9,W10";
    std::string line2 = "10,10,10,10,10,10,10,10,10,99995";

    cout << processing_input_lines(line1 , line2) << endl; 
}

