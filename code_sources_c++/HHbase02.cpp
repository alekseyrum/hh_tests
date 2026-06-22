// #include "login_generator.h"
#include <sstream>
#include <vector>
#include <algorithm>
#include <cctype>
#include <iostream>

std::vector<std::string>
generate_logins(const std::string & first_names_line,
                const std::string & last_names_line) {
    std::string sWord;
    std::stringstream stInput(first_names_line);
    std::vector<std::string> vecFirstNames;
    while ( std::getline(stInput,sWord, ',' )) {
        vecFirstNames.push_back( sWord );
    }
    stInput.clear();
    stInput.str(last_names_line);
    std::vector<std::string>vecLastNames;
    while ( std::getline(stInput,sWord, ',' )) {
        vecLastNames.push_back( sWord );
    }

    std::vector<std::string>vecResult;
    std::string sLogin;
    for (size_t i = 0; i < vecFirstNames.size(); ++i) {
        sLogin = vecFirstNames[i].substr(0,3);
        sLogin[0] = std::tolower( sLogin[0], std::locale() );
        sLogin[1] = std::toupper( sLogin[1], std::locale() );
        sLogin[2] = std::tolower( sLogin[2], std::locale() );
        sLogin += std::toupper(vecLastNames[i][4], std::locale() );
        sLogin += std::tolower(vecLastNames[i][3], std::locale() );
        sLogin += std::toupper(vecLastNames[i][2], std::locale() );
        vecResult.push_back(sLogin);

    }
    return vecResult;
}

int main() {
    system("chcp 65001 > nul");
    std::vector<std::string> vecRes;
    // vecRes = generate_logins("John,Michael,Elizabeth", "Johnson,Williams,Anderson");
    // vecRes = generate_logins("Ale,Vic", "Pesko,Skaya");
    // vecRes = generate_logins("Xyz,Abc,Qwe,Asd,Zxc,Rty,Fgh,Vbn", "Xylophone,Abacus,Quetzal,Asdfgh,Zxcvbn,Rtyuio,Fghijk,Vbnmk");
    // vecRes = generate_logins("abcdefghijklmnoprstuvwxyzabcdefghijklm", "rStUvWxYzAbCdEfGhIjKlMAbCdefGhIjKlMnOpQ");
    vecRes = generate_logins("MixedCase,DIFFERENT,lower,UPPER", "MixedToo,NOTATION,variation,UPCAPS");


    for (std::string val : vecRes) {
        std::cout << val << std::endl;
    }

}

/*
// - - - - - - - - - - - - - - - - 
// #include ""
#include <iostream>
#include <vector>

#include <sstream>
#include <numeric>

#include <iomanip>

using namespace std;

// vector<string>splitString()
// std::vector<std::string> ProcessingCandidates::PrintCorrectCandidates(
std::vector<std::string> PrintCorrectCandidates(
const std::string &  sScores,
const std::string &  sNames )
{
    // напишите ваш код
    std::string sWord;
    std::stringstream stInput(sScores);

    vector<int> vecScores;
    // while ( stInput >> sWord ) {
    while ( std::getline(stInput,sWord, ',' )) {
        vecScores.push_back( std::stoi(sWord) );
    }
    // cout << "scores items = " << vecScores.size() << endl;
    int iTotal = std::accumulate( vecScores.begin(), vecScores.end(), 0);
    // cout << "total value = " << iTotal << endl;
    float fAverage = (float)iTotal / vecScores.size();
    cout << "Average value = " << std::fixed << std::setprecision(2) << fAverage << endl;

    stInput.clear();
    stInput.str(sNames);
    vector<string>vecNames;
    while ( std::getline(stInput,sWord, ',' )) {
        vecNames.push_back( sWord );
    }
    vector<string>vecResult;
    for (size_t i = 0; i < vecScores.size(); ++i) {
         if (vecScores[i] > fAverage) vecResult.push_back(vecNames[i]); 
    }
    if ( vecResult.size() == 0) { vecResult.push_back("net"); }

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
*/