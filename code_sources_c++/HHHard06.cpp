// MedianCalculator
// - - - - - - - - - - -
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <array>
#include <cmath>
#include <iomanip>

using namespace std;

class ProcessingNeuroData {
public:
    std::vector<std::string> 
    process(const std::vector<std::string> & lines) const;
};

// typedef float rec_t[5] ; 
typedef array<float, 5> rec_t; 

void calcMinProbability(const rec_t & a, const rec_t & b, rec_t & res ){
    for (int i=0; i<5;i++){
        res[i] = a[i] < b[i] ? a[i] : b[i];
    }
}

void calcMaxProbability(const rec_t & a, const rec_t & b, rec_t & res ){
    for (int i=0; i<5;i++){
        res[i] = a[i] > b[i] ? a[i] : b[i];
    }
}

void calcComProbability(const rec_t & a, const rec_t & b, rec_t & res ){
    for (int i=0; i<5;i++){
        res[i] = (a[i] + b[i]) - (a[i] * b[i]);
    }
}

std::vector<std::string> ProcessingNeuroData::process(const std::vector<std::string> & lines) const
{
    rec_t fRec = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f}; 
    std::vector<rec_t> vecData; 

    std::vector<std::string>::const_iterator itLine = lines.begin();
    while (itLine != lines.end()) {
        std::stringstream stInput(*itLine);
        std::string sVal;
        for (int iCur = 0; iCur < 5; iCur++) {
            std::getline(stInput,sVal, ' ' );
            fRec[iCur] = std::stof(sVal);
        }
        vecData.push_back(fRec);
        itLine++;
    }
    // - - - [ Calculations: ] - - - - - - - - - - - - - - - - -
    rec_t minRes = vecData[0]; // {0.0};
    rec_t maxRes = vecData[0]; // {0.0}; 
    rec_t comRes = vecData[0]; // {0.0};

    // const rec_t & fRecA = vecData[0];
    const rec_t & fRecB = vecData[1];
    for (int iCurRec = 1; iCurRec < vecData.size(); iCurRec++ ) {
        calcMinProbability( minRes, vecData[iCurRec], minRes); 
        calcMaxProbability( maxRes, vecData[iCurRec], maxRes); 
        calcComProbability( comRes, vecData[iCurRec], comRes);
    }
    vector<string> vResult;
    std::stringstream stream;
    stream << std::fixed << std::setprecision(2) << minRes[0] << " " << minRes[1] << " " << minRes[2] << " " << minRes[3] << " " << minRes[4];
    std::string str = stream.str();
    vResult.push_back( stream.str() );

    stream.str(""); 
    stream << maxRes[0] << " " << maxRes[1] << " " << maxRes[2] << " " << maxRes[3] << " " << maxRes[4];
    vResult.push_back( stream.str() );

    stream.str("");
    stream << comRes[0] << " " << comRes[1] << " " << comRes[2] << " " << comRes[3] << " " << comRes[4];
    vResult.push_back( stream.str() );

    return vResult;
}
   

int main()
{
    /*
    vector<string> vInputData = {
    "0.30 0.60 0.70 0.80 0.40",
    "0.20 0.70 0.50 0.60 0.60"};

    vector<string> vInputData = {
        "0.10 0.10 0.10 0.10 0.10",
        "0.20 0.20 0.20 0.20 0.20",
        "0.42 0.42 0.42 0.42 0.42"};

    vector<string> vInputData = {
    "0.70 0.71 0.72 0.73 0.74",
    "0.75 0.76 0.77 0.78 0.79",
    "0.80 0.81 0.82 0.83 0.84",
    "0.85 0.86 0.87 0.88 0.89",
    "0.70 0.71 0.72 0.73 0.74",
    "0.75 0.76 0.77 0.78 0.79",
    "0.80 0.81 0.82 0.83 0.84",
    "0.85 0.86 0.87 0.88 0.89"};

    vector<string> vInputData = {
        "0.20 0.21 0.22 0.23 0.24",
        "0.25 0.26 0.27 0.28 0.29",
        "0.30 0.31 0.32 0.33 0.34",
        "0.35 0.36 0.37 0.38 0.39",
        "0.40 0.41 0.42 0.43 0.44",
        "0.45 0.46 0.47 0.48 0.49",
        "0.50 0.51 0.52 0.53 0.54",
        "0.55 0.56 0.57 0.58 0.59"};

        */

    vector<string> vInputData = {
    "0.01 0.02 0.03 0.04 0.05",
    "0.06 0.07 0.08 0.09 0.10",
    "0.11 0.12 0.13 0.14 0.15",
    "0.16 0.17 0.18 0.19 0.20",
    "0.21 0.22 0.23 0.24 0.25",
    "0.26 0.27 0.28 0.29 0.30",
    "0.31 0.32 0.33 0.34 0.35",
    "0.36 0.37 0.38 0.39 0.40",
    "0.41 0.42 0.43 0.44 0.45",
    "0.46 0.47 0.48 0.49 0.50",
    "0.51 0.52 0.53 0.54 0.55",
    "0.56 0.57 0.58 0.59 0.60"};


    ProcessingNeuroData pnd;

    vector<string> vResult = pnd.process(vInputData);
    for ( auto ss : vResult) {
        cout << ss << endl;
    }
    // string sStop; cin >>  sStop;
}
