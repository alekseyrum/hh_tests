// MedianCalculator
// - - - - - - - - - - -
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <array>
#include <cmath>

using namespace std;

class ProcessingNeuroData {
public:
    std::vector<std::string> 
    process(const std::vector<std::string> & lines) const;
};

/*
typedef float rec_t[5]; 

void calcMinProbability(const rec_t& a, const rec_t& b, rec_t& res) {
    for (int i = 0; i < 5; i++) {
        // std::fmin безопаснее для работы с массивами и числами с плавающей точкой
        res[i] = std::fmin(a[i], b[i]); 
    }
}

int main() {
    rec_t minRes = {0.0};
    // Создаем вектор и добавляем в него два массива для проверки
    std::vector<rec_t> vecData(2); 
    
    // Передаем сами элементы массива, к которым можно обратиться по индексу
    calcMinProbability(vecData[0], vecData[1], minRes);
    
    return 0;
}
*/


// typedef float rec_t[5] ; 
typedef array<float, 5> rec_t; 

void calcMinProbability(const rec_t & a, const rec_t & b, rec_t & res ){
    for (int i=0; i<5;i++){
        // res[i] = std::min(a[i], b[i]);
        res[i] = a[i] < b[i] ? a[i] : b[i];
    }
}

std::vector<std::string> ProcessingNeuroData::process(const std::vector<std::string> & lines) const
{
    rec_t fRec = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f}; 
    // vector<rec_t> vecData;
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
        // vecData.push_back({});
        itLine++;
    }
    // Calculations:
    rec_t minRes = {0.0};
    rec_t maxRes = {0.0}; 
    rec_t comRes = {0.0};

    // calcMinProbability( *(vecData.begin()), *(vecData.begin()+1), minRes); 
    calcMinProbability( vecData[0], vecData[1], minRes); 
    // calcMinProbability( vecData.begin(), vecData.begin()+1, minRes); 
    cout << "minProb:" << minRes[0] << "," << minRes[1] << "," << minRes[2] << "," << minRes[3] << "," << minRes[4] << endl;

    return {"end"};
}
   

int main()
{
    vector<string> vInputData = {
    "0.30 0.60 0.70 0.80 0.40",
    "0.20 0.70 0.50 0.60 0.60"};

    ProcessingNeuroData pnd;

    vector<string> vResult = pnd.process(vInputData);
    for ( auto ss : vResult) {
        cout << ss << endl;
    }
}
