#include <iostream>
#include <vector>
#include <sstream>
#include <numeric>
#include <iomanip>

// #include <windows.h>

using namespace std;

class Candidate {
public:
    std::string name;
    std::string surname;
    std::string family;
    int ratio;
};

class CandidateCatalog {
    vector<Candidate> vData;
public: 
    void loadData( const std::string & inScores , const std::string & inFIO );
    void PrintCandidates (); //  { std::cout << "_not_implemented_" << std::endl; };
};

void CandidateCatalog::loadData( const std::string & inScores , const std::string & inFIO ) {
    std::string sBall;
    std::string sPerson;
    std::stringstream streamScore(inScores);
    std::stringstream streamFIO(inFIO);
    // vector<int> vecScores;
    // while ( stInput >> sWord ) {
    while ( std::getline(streamScore,sBall, ',' ) && std::getline(streamFIO,sPerson, ',' ) ) {
        // vecScores.push_back( std::stoi(sWord) );
        std::stringstream streamFields(sPerson);
        Candidate newCandid;
        newCandid.ratio = std::stoi(sBall);
        std::getline(streamFields,newCandid.name, ':' );
        std::getline(streamFields,newCandid.surname, ':' );
        std::getline(streamFields,newCandid.family, ':' ); 
        vData.push_back(newCandid);
    }
}

void CandidateCatalog::PrintCandidates() {
    for ( Candidate curCandid : vData) {
        std::cout << curCandid.name << " " << curCandid.surname << " " <<  curCandid.family << " - " << curCandid.ratio << endl;
    }
}

int main() {
    // SetConsoleOutputCP(CP_UTF8);
    // SetConsoleCP(CP_UTF8);

    CandidateCatalog cc;
    cc.loadData("1,2,3,2" , "Вася:Михалыч:Пупкин,Петя:Петрович:Петров,Коля:Дармидонтович:Сидоров,Акакий:Дионисиевич:Гукин");
    cc.PrintCandidates();

}
