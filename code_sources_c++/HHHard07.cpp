
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <array>
#include <cmath>
#include <iomanip>

using namespace std;

std::vector<std::string> processingInputLines(const std::string& intervalLine,
                                                const std::vector<std::string>& inputLines)
{
    std::istringstream iss( intervalLine );
    std::tm tm1 = {};
    std::tm tm2 = {};

    iss >> std::get_time(&tm1, "%d:%m:%Y:%H:%M:%S" );
    iss.ignore(1);
    iss >> std::get_time(&tm2, "%d:%m:%Y:%H:%M:%S" );

    std::time_t time_1 = std::mktime(&tm1);
    std::time_t time_2 = std::mktime(&tm2);
 
    float fMin = 0.0;
    float fMax = 0.0;
    float fSum = 0.0;
    int iValCount = 0;

    std::vector<std::string>::const_iterator itLine = inputLines.begin();
    for ( auto curLine : inputLines) {
        iss.clear();  
        iss.str( curLine ); 

        iss >> std::get_time(&tm1, "%d:%m:%Y:%H:%M:%S" );
        std::time_t lineTime = std::mktime(&tm1);
        if (lineTime < time_1 || lineTime > time_2) continue;

        int delimPos = curLine.find(';');
        float fVal = std::stof( curLine.substr(delimPos+1, curLine.length() - delimPos - 1) );
     
        fSum += fVal;
        if ( iValCount == 0 ) {
            fMin = fMax = fVal;
            iValCount++;
            continue;
        }
        if ( fVal < fMin ) fMin = fVal;
        if ( fVal > fMax ) fMax = fVal;
        iValCount++;
    }
    float fAverage = 0.0 ; 
    if (iValCount == 0) { return {"none"}; }

    fAverage = fSum/iValCount;

    vector<string> vResult;
    std::stringstream stream;
    stream << std::fixed << std::setprecision(3) << fMax ;
    std::string str = stream.str();
    vResult.push_back( stream.str() );

    stream.str(""); 
    stream << fMin ; 
    vResult.push_back( stream.str() );

    stream.str(""); 
    stream << fAverage ; 
    vResult.push_back( stream.str() );

    return vResult;

}

int main()
{
    /*
    std::string strData = "01:01:2025:09:00:00;01:01:2025:11:00:00";
    vector<string> vInputData = {
        "01:01:2025:09:30:00;-12.5",
        "01:01:2025:10:00:00;15.5",
        "01:01:2025:10:30:00;-8.3" };
        
    std::string strData = "01:01:2025:12:00:00;01:01:2025:12:30:00";
    vector<string> vInputData = { "01:01:2023:12:15:00;42.3" } ;

    std::string strData = "01:01:2024:00:00:00;01:01:2024:00:00:00" ;
    vector<string> vInputData = {
        "01:01:2024:00:00:00;5.0",
        "01:01:2024:01:00:00;10.0",
        "01:01:2024:02:00:00;15.0",
        "01:01:2024:03:00:00;20.0",
        "01:01:2024:04:00:00;25.0",
        "01:01:2024:05:00:00;30.0",
        "01:01:2024:06:00:00;35.0",
        "01:01:2024:07:00:00;40.0"};
        

    std::string strData = "01:01:2024:01:00:00;01:01:2024:09:00:00";
    vector<string> vInputData = { 
        "01:01:2024:00:00:00;-5.0",
        "01:01:2024:01:00:00;0.0",
        "01:01:2024:02:00:00;5.0",
        "01:01:2024:03:00:00;10.0",
        "01:01:2024:04:00:00;15.0",
        "01:01:2024:05:00:00;20.0",
        "01:01:2024:06:00:00;25.0",
        "01:01:2024:07:00:00;30.0",
        "01:01:2024:08:00:00;35.0",
        "01:01:2024:09:00:00;40.0" };
        */

    std::string strData = "01:01:2024:04:00:00;01:01:2024:08:00:00";
    vector<string> vInputData = { 
        "01:01:2024:00:00:00;-6.56",
        "01:01:2024:01:00:00;-4.34",
        "01:01:2024:04:00:00;2.33",
        "01:01:2024:05:00:00;4.44",
        "01:01:2024:06:00:00;6.336",
        "01:01:2024:07:00:00;8.34",
        "01:01:2024:08:00:00;10.324",
        "01:01:2024:09:00:00;12.657",
        "01:01:2024:02:00:00;-2.44",
        "01:01:2024:03:00:00;0.33",
        "01:01:2024:10:00:00;14.53",
        "01:01:2024:11:00:00;16.235"};


    vector<string> vResult = processingInputLines(strData, vInputData);
    for ( auto ss : vResult) {
        cout << ss << endl;
    }
}
