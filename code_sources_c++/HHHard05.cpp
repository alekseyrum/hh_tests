// MedianCalculator
// - - - - - - - - - - -
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

std::vector<std::string> process(const std::vector<std::string> & lines) 
{
    int iN = std::stoi(lines[0]);
    // cout <<iN << endl;
    unsigned char * inMat = static_cast<unsigned char*>(malloc( sizeof(unsigned char) * iN * iN ));
    if ( inMat == nullptr ) return {};

    int iCurLine = 0;
    std::vector<std::string>::const_iterator itLine = ++lines.begin();
    while (iCurLine < iN && itLine != lines.end()) {
        std::stringstream stInput(*itLine);
        int iCurCol = 0;
        std::string sColorVal;

        while ( std::getline(stInput,sColorVal, ' ' )) {
            int iVal = std::stoi(sColorVal);
            inMat[ sizeof(unsigned char) *(iCurLine*iN) + iCurCol] = static_cast<unsigned char>(iVal);
            iCurCol++;
        }
        if (iCurCol != iN )  {
            cout << "ERROR: Column count " << iCurCol << " in Line " << iCurLine << endl;
            cout << "(must be equal " << iN  << endl;
            return {}; 
        }

        iCurLine++;
        itLine++;
    }

    /*
    cout << "matrix loaded." << endl;
    for (int idebugLine = 0; idebugLine < iN; idebugLine++) {
        for (int idebugCol = 0; idebugCol < iN; idebugCol++) {
            cout << std::to_string(inMat[ sizeof(unsigned char) *  (idebugLine*iN) + idebugCol]) << "-";
        }
        cout << endl;
    }
    */

    // - - - [processing matrix:] - - - - - -

    vector<string> vecResult;
    vecResult.push_back( std::to_string(iN/2) );

    vector<unsigned char>vMid = {0, 0, 0, 0};
    for (int iMidLine = 0; iMidLine < iN/2; iMidLine++)
    {
        string sCurResLine = "";
        for (int iMidCol = 0; iMidCol < iN/2; iMidCol++) {
            vMid[0] = inMat[sizeof(unsigned char) * (iN*iMidLine*2) + (iMidCol*2)];
            vMid[1] = inMat[sizeof(unsigned char) * (iN*iMidLine*2) + (iMidCol*2 + 1) ];
            vMid[2] = inMat[sizeof(unsigned char) * (iN*(iMidLine*2 + 1)) + (iMidCol*2) ];
            vMid[3] = inMat[sizeof(unsigned char) * (iN*(iMidLine*2 + 1)) + (iMidCol*2 + 1) ];
            // cout << "original pixels:" << std::to_string(vMid[0]) << "," << std::to_string(vMid[1]) << "," << std::to_string(vMid[2]) << "," << std::to_string(vMid[3]) << endl;

            std::sort(vMid.begin(), vMid.end(), [](const auto& a, const auto& b) { return a < b ; } );
            // cout << "sorted pixels:" << std::to_string(vMid[0]) << "," << std::to_string(vMid[1]) << "," << std::to_string(vMid[2]) << "," << std::to_string(vMid[3]) << endl;
            int iMidValue = (vMid[1] + vMid[2]) / 2;
            // cout << "average = " << iMidValue << endl;
            sCurResLine += (std::to_string(iMidValue) + " ");
        }
        vecResult.push_back(sCurResLine);
    }
    return vecResult;
}

int main()
{
    /*
    vector<string> vInputData = { 
    "2",
    "10 20",
    "30 40" };
    
    vector<string> vInputData = { 
    "4",
    "10 20 30 40",
    "50 60 70 80",
    "90 100 110 120",
    "130 140 150 160" };

    vector<string> vInputData = {
    "8",
    "10 10 20 20 30 30 40 40 ",
    "10 10 20 20 30 30 40 40 ",
    "50 50 60 60 70 70 80 80 ",
    "50 50 60 60 70 70 80 80 ",
    "90 90 100 100 110 110 120 120",
    "90 90 100 100 110 110 120 120",
    "130 130 140 140 150 150 160 160",
    "130 130 140 140 150 150 160 160" };

    vector<string> vInputData = {
    "8",
    "5 5 5 5 10 10 10 10",
    "5 5 5 5 10 10 10 10",
    "5 5 5 5 10 10 10 10",
    "5 5 5 5 10 10 10 10",
    "15 15 15 15 20 20 20 20",
    "15 15 15 15 20 20 20 20",
    "15 15 15 15 20 20 20 20",
    "15 15 15 15 20 20 20 20" };
    */

    vector<string> vInputData = {
    "8",
    "0 50 100 150 200 250 255 255",
    "0 50 100 150 200 250 255 255",
    "0 50 100 150 200 250 255 255",
    "0 50 100 150 200 250 255 255",
    "0 50 100 150 200 250 255 255",
    "0 50 100 150 200 250 255 255",
    "0 50 100 150 200 250 255 255",
    "0 50 100 150 200 250 255 255" };


    vector<string> vResult = process(vInputData);
    for ( auto ss : vResult) {
        cout << ss << endl;
    }
}

