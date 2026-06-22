#include <iostream>
#include <vector>
#include <sstream>
#include <numeric>
#include <iomanip>

using namespace std;

std::vector<std::string> PrintCorrectCandidates(
const std::string & scoreInput ,
const std::string & namesInput )
{
    std::string sWord;
    std::stringstream stInput(scoreInput);

    vector<int> vecScores;
    while ( std::getline(stInput,sWord, ',' )) {
        vecScores.push_back( std::stoi(sWord) );
    }
    int iTotal = std::accumulate( vecScores.begin(), vecScores.end(), 0);
    float fAverage = (float)iTotal / vecScores.size();
    stInput.clear();
    stInput.str(namesInput);
    vector<string>vecNames;
    while ( std::getline(stInput,sWord, ',' )) {
        vecNames.push_back( sWord );
    }
    vector<string>vecResult;
    for (size_t i = 0; i < vecScores.size(); ++i) {
         if (vecScores[i] > fAverage) vecResult.push_back(vecNames[i]); 
    }
    if ( vecResult.size() == 0) { vecResult.push_back("нет"); }

    return vecResult;
};

int main() {
    vector<string> vecRes;
    // vecRes = PrintCorrectCandidates( "1,2,3,5" , "dd,rr,tt,Penelopa");
    // vecRes = PrintCorrectCandidates("4,6,8,8,5,8,4,7,9,2", "Smith,Johnson,Williams,Brown,Jones, Miller,Davis,Garcia, Rodrigues,Wilson");
    // vecRes = PrintCorrectCandidates("7,7,7,7,7", "Dupont,Martin,Bernard,Leroy,Петров");
    // vecRes = PrintCorrectCandidates("1,9,2", "Smith,Brown,Lighter");
    vecRes = PrintCorrectCandidates("3,7,2,8,5", "Hall,Allen,Young,Hermandez,Wright");

    for (std::string val : vecRes) {
        cout << val << endl;
    }

}
