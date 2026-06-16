#include <iostream>
#include <vector>
#include <sstream>
#include <numeric>
#include <iomanip>

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
  
    while ( std::getline(streamScore,sBall, ',' ) && std::getline(streamFIO,sPerson, ',' ) ) {
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
    // setlocale(LC_ALL, "Russian");
    // std::locale::global(std::locale("")); 
    system("chcp 65001 > nul");
    // SetConsoleOutputCP(CP_UTF8);
    // SetConsoleCP(CP_UTF8);
    
    // string ratings = "8,8,8";
    // string names = "Алексей:Михайлович:Смирнов,Дмитрий:Александрович:Козлов,Елена:Владимировна:Новикова";

    // string ratings = "3";
    // string names = "Петр Аркадий Михаил:Сергеевич:О'Шин";

    // string ratings = "5,5,7,7,9,9,10,10";
    // string names = "Иван:Иванович:Иванов,Иван:Иванович:Иванов,Петр:Петрович:Петров,Петр:Петрович:Петров,Анна:Сергеевна:Сидорова,Анна:Сергеевна:Сидорова,Мария:Алексеевна:Кузнецова,Мария:Алексеевна:Кузнецова";

    string ratings = "4,6,8,5,7,9";
    string names = "Александр:Владимирович:Каракозов,Дарья:Олеговна:Старостина,Игорь:Николаевич:Макаренко,Наталья:Александровна:Виноградова,Сергей:Викторович:Романовсвский,Екатерина:Андреевна:Кузнецова-Смирнова";

    CandidateCatalog cc;
    cc.loadData(ratings , names );
    cc.PrintCandidates();
}
