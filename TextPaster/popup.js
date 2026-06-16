
const copyBtn = document.getElementById("copyBtn");
copyBtn.addEventListener("click",() => {
	// console.log("ddsdfsdf");
	var textNum = document.getElementById("txtNum");
    /*
	var whatToPaste;
	switch (textNum.value) 
	{
		case "base01": { whatToPaste = base01_text; break;}
		case "base02": { whatToPaste = base02_text; break;}
		case "base03": { whatToPaste = base03_text; break;}
	} 
    */
	navigator.clipboard.writeText( globalThis[textNum.value + "_text" ] );
});

const selectList = document.getElementById("txtNum");
selectList.addEventListener("change",(event) => {
    const selectedValue = event.target.value; 
    // const selectedText = selectElement.options[selectElement.selectedIndex].text;
    // resultElement.textContent = `Вы выбрали: ${selectedText} (код: ${selectedValue})`;
    document.getElementById('description-block').textContent =  globalThis[selectedValue + "_description" ]; //  "Текст добавлен через JavaScript!";
});

var base01_description = `Отдел кадров фирмы провел собеседование на вакантную должность и получил для каждого кандидата баллы рейтинга. Выведите канлдидатов, которые имеют рейтинг строго выше среднего, согласно их расположению во входных данных. Если такие отсутствуют, выведите "нет".`;
var base01_text = `#include <iostream>
#include <vector>
#include <sstream>
#include <numeric>
#include <iomanip>
using namespace std;

std::vector<std::string> ProcessingCandidates::PrintCorrectCandidates(
const std::string & /*scoreInput*/,
const std::string & /*namesInput*/ )
{
    // напишите ваш код
    // return ();

    std::string sWord;
    std::stringstream stInput(sScores);
    vector<int> vecScores;
  
    while ( std::getline(stInput,sWord, ',' )) {
        vecScores.push_back( std::stoi(sWord) );
    }
    int iTotal = std::accumulate( vecScores.begin(), vecScores.end(), 0);
    float fAverage = (float)iTotal / vecScores.size();
    // cout << "Average value = " << std::fixed << std::setprecision(2) << fAverage << endl;

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
}`;

var base02_description = `Согласно принятой политике безопасности, при регистрации пользователя в корпоративной информационной системе ему назначается имя пользователя (логин) и пароль.`;
var base02_text = `#include <sstream>
#include <vector>
#include <algorithm>
#include <cctype>

#include <iostream>

std::vector<std::string>
generate_logins(const std::string & first_names_list,
                const std::string & last_names_list) {
    // ваш код ниже
    // return {}
    std::string sWord;
    std::stringstream stInput(first_names_list);
    std::vector<std::string> vecFirstNames;
    while ( std::getline(stInput,sWord, ',' )) {
        vecFirstNames.push_back( sWord );
    }
    stInput.clear();
    stInput.str(last_names_list);
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
}`;

var base03_description = `Отдел кадров компании планирует внедрение новой информационной системы для работы с кандидатами на вакантные должности.
Для информационной системы необходимо разработать модуль, который, позволяет сформировать каталог для хранения информации о кандидатах в формате Имя,Отчество,Фамилия,Рейтинг.`;
var base03_text = `#include <iostream>
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
}`;

var base04_description = `Платформа онлайн-дистрибуции компьютерных игр сформировала список названий игр и количества скачиваний за год. Для анализа качества игр, размещенных на платформе, нужно определить соотношение востребованных и невостребованных игр. Рассчитайте, какой процент игр от общего количества представленных на платформе игр имеет количество скачиваний строго меньше среднего значения.`;
var base04_text = `#include <iostream>
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
}`;

var base05_description = `на будущее`;
var base05_text = `пока пусто`;

var base06_description = `not yet`;
var base06_text = `_not_implemented_`;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
// Средний уровень: 
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
var middle01_description = `Отдел управления персоналом ИТ-компании формирует отчет для департамента по налогам по количеству внештатных сотрудников в разных странах за прошлый год в формате:
Фамилия;ГодРождения;НазваниеСтраны;ProjectID.
Требуется проверить корректность данных`;

var middle01_text = `#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <charconv>
#include <map>
using namespace std;

std::vector<std::string> generate_report(const std::vector<std::string> & lines) 
{
    std::vector<std::string> vecResult;
    std::map<string, int> mapWorkers;

    for (const std::string &word : lines) {
        std::string_view sv(word);
        int delim1 = sv.find(';');
        int delim2 = sv.find(';', delim1+1);
        int delim3 = sv.find(';', delim2+1);
        if (delim3 == std::string_view::npos) {
            continue;
        }
        std::string_view svName = sv.substr(0,delim1);
        std::string_view svYear = sv.substr(delim1+1, delim2-delim1-1);
        std::string_view svCountry = sv.substr(delim2+1, delim3-delim2-1);
        std::string_view svProject = sv.substr(delim3+1, sv.size()-delim3);
        // cout << "name:" << svName << " year:" << svYear << " contry:" << svCountry << " proj:" << svProject << endl;
        if ( svName.size() > 40 || svCountry.size() > 40 || svCountry.size() < 2) { 
            cout << "wrong field length:" << svName << " or " << svCountry << endl;
            continue; 
        }
        if ( ! std::all_of(svName.begin(), svName.end(), [](unsigned char c) { return std::isalpha(c); } ) )  {
            cout << "wrong name:" << svName << endl;
            continue; 
        }
        int iYearVal = 0;
        std::from_chars_result fcr = std::from_chars(svYear.data(), svYear.data() + svYear.size() , iYearVal );
        if ( iYearVal < 1960 || iYearVal > 2007) {
            cout << "wrong year:" << iYearVal << endl;
            continue;
        }

        if ( ! std::all_of(svCountry.begin(), svCountry.end(), [](unsigned char c) { return std::isalpha(c); } ) )  {
            cout << "wrong country:" << svCountry << endl;
            continue; 
        }
        // - - - [field ProjectID] - - -
        if ( svProject.size() != 5 || ! std::all_of(svProject.begin(), svProject.begin()+2, [](unsigned char c) { return (c >= 'A' && c <= 'Z');} ) ) {
            cout << "wrong project format:" << svProject << endl;
            continue;
        }    
        if ( ! std::all_of(svProject.begin()+3, svProject.begin()+5, [](unsigned char c) { return std::isdigit(c); } ) ) {
            cout << "wrong project format:" << svProject << endl;
            continue;
        }   
        // here all ok:
        std::map<string,int>::iterator itWorkers = mapWorkers.find( std::string(svCountry) );
        if ( itWorkers == mapWorkers.end() ) {
            mapWorkers.insert( { std::string(svCountry), 1 } );
        } else {
            itWorkers->second++;
        }
    }

    if ( mapWorkers.size() == 0 ) {
        return {"none:0"};
    }

    std::vector<std::pair<std::string, int>> vec4Sort(mapWorkers.begin(), mapWorkers.end());
    std::sort(vec4Sort.begin(), vec4Sort.end(), [](const auto& a, const auto& b) {
        if (a.second != b.second) return a.second > b.second;
        return a.first < b.first;
    });
    for (auto cc : vec4Sort) {
        vecResult.push_back( cc.first + ":" + std::to_string(cc.second) );
    }
    return vecResult;
}`;

var middle02_description = `Администратор сайта сформировал данные о размещенных разработчиками компьютерных инди-играх в формате:
gameID->Название->Рейтинг->КоличествоСкачиваний.
Для стандартизации данных в описании игры на сайте и проведения маркетинговой кампании службе продвижения сайта требуется информаци об играх с высокой, средней или низкой популярностью.
Требуетсяя разработать модуль, который выполняет проверку данных на корректность (проверка останавливается при первой ошибке) и для каждой записи о компьютерной игре выводит информацию в следующем формате:
gameID:Название:Message`;
var middle02_text = `#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

std::vector<std::string> report(const std::vector<std::string> & lines) 
{
    std::vector<std::string> vecResult;

    for (auto cc : lines) {
        std::string_view sv(cc);

        int delim1 = sv.find("->");
        int delim2 = sv.find("->", delim1+2);
        int delim3 = sv.find("->", delim2+2);
        if (delim3 == std::string_view::npos) {
            cout << "fields too few" << endl;
            return vecResult;
        }
        std::string svGameid(sv.substr(0,delim1) );
        std::string svName(sv.substr(delim1+2, delim2-delim1-2) ) ; 
        std::string svRate(sv.substr(delim2+2, delim3-delim2-2) );
        std::string svLoad(sv.substr(delim3+2, sv.size()-delim3) );
       
        int iGameID = 0 ; 
        if ( svGameid.empty() ) { 
            svGameid = "unknown" ;
        } else {
            iGameID = std::stoi(svGameid);
        }
        
        int iRate = std::stoi(svRate);
        int iDownLoad = std::stoi(svLoad);
        std::string sMsg = "low";

        if (iGameID < 1000 || iGameID > 9999 || svName.length() < 5 || svName.length() > 40 
            || ! std::all_of(svName.begin(), svName.end(), [](unsigned char c) { return std::isalpha(c); })
            || iRate < 0 || iRate > 100
            || iDownLoad < 0 || iDownLoad > 10000000
            ) { 
            if ( svName.empty() ) { svName = "unknown"; }
            vecResult.push_back(svGameid + ":" + svName + ":incorrect data");
        } else {
            if (iRate >= 90 || iDownLoad > 100000) { sMsg = "top"; }
            else if ( (iRate > 60 && iRate <= 89) || (iDownLoad > 50000 && iDownLoad < 99999 ) ) 
            { sMsg = "middle"; }
            vecResult.push_back(svGameid + ":" + svName + ":" + sMsg);
        }         
    }  
    return vecResult; 
}`;


var middle03_description = `Вы разрабатываете модуль анализа активности системных служб в корпоративной информационной системе на основе исследования логов запросов, поступающих на сервер.
Запись лога имеет следующий вид:
<service="serviceID" data="dataID" action="readwrite">.
Нужно определить корректные записи логов сервера.`;
var middle03_text = `#include <iostream>
#include <vector>
#include <map>
#include <regex>

using namespace std;

struct OpStatus {
    int read;
    int write;
};

std::vector<std::string> report(const std::vector<std::string> & lines) 
{
    std::vector<std::string> vecResult;
    std::map<string, OpStatus> mStates;
    std::map<string, OpStatus>::iterator itElem;

    std::regex pattern("^<service=\"(\\d{5})\" data=\"(\\w{9})\" action=\"(\\w{4,5})\">"); 
    std::smatch matches;

    std::vector<std::string>::const_iterator itLine = lines.begin();
    while ( itLine != lines.end() )
    {
        if (std::regex_search( *itLine , matches, pattern)) {
            itElem = mStates.find( matches.str(1) );
            if ( itElem == mStates.end() ) {
                OpStatus os;
                os.read = 0;
                os.write = 0;
                auto pIns = mStates.insert( { matches.str(1) , os } );
                itElem = pIns.first;
            } 
            if ( matches.str(3) == "read") {
                itElem->second.read++;
            } else if (matches.str(3) == "write") {
                itElem->second.write++;
            }
        }
        itLine++;
    }
    // write-out to result:
    for (const auto & dd : mStates) {
        int iWriteLimit = (dd.second.write + dd.second.read) *0.75;
        if ( dd.second.write >= iWriteLimit) {
            vecResult.push_back( "Alert! " + dd.first + " has suspicious activity" );
        } else {
            vecResult.push_back( "{service=\"" + dd.first + "\",\"read\":" + std::to_string(dd.second.read) + ",\"write\":" + std::to_string(dd.second.write) + "}" );
        }
    }
    if ( vecResult.size() == 0 ) {
        vecResult.push_back( "none" );
    }
    return vecResult;
}`;


var middle04_description = `Вы разрабатываете систему мониторинга изменений цен акций отдела ценообразования в большой компании-ритейлере.
Каждое событие изменения цены акции имеет формат:
*Symbol::Price::ChangeDirection::Timestamp.
*Symbol - тикер акции (например AAPL).
*Price - текущая цена (целое число).
*ChangeDirection - направление изменения: UP (рост) или DOWN (падение).
*Timestamp - время изменения в формате ЧЧ:ММ:СС.`;
var middle04_text = `#include <iostream>
#include <vector>
#include <map>
#include <chrono>
#include <regex>

using namespace std;

struct AState {
    int price;
    std::chrono::seconds time;
};

std::vector<std::string> report(const std::vector<std::string> & lines) 
{
    std::vector<std::string> vecResult;
    std::map<std::string,AState> mPapers;
    std::map<std::string,AState>::iterator itPaper;
    std::vector<std::string>::const_iterator itLine = lines.begin();

    std::regex pattern("^(\\w{4})::(\\d+)::(\\w{2,4})::(\\d{2}:\\d{2}:\\d{2})$"); 
    std::smatch matches;

    while ( itLine != lines.end() )
    {
        if (! std::regex_search( *itLine , matches, pattern)) {
            cout << "regexp parsing not found mathces in line:" << endl;
            cout << *itLine << endl;
            itLine++;
            continue;
        }
        std::istringstream iss( matches.str(4) );
        std::chrono::seconds time_val; 
        iss >> std::chrono::parse("%H:%M:%S", time_val);
        if ( iss.fail()) {
            cout << "ERROR time parsing from string:" << matches.str(4) << endl;
            itLine++;
            continue;
        }
        int iNewPrice = std::stoi(matches.str(2));
        std::string sPaperName = matches.str(1);
        itPaper = mPapers.find( sPaperName );
        if ( itPaper == mPapers.end() ) {
            AState nS;
            nS.price = iNewPrice;
            nS.time = time_val;
            mPapers.insert( { sPaperName , nS } );
        } else {
            // PAPER already exists
            // cout << "paper exists wit time = " <<  itPaper->second.time << endl;
            if (itPaper->second.time >= time_val) {
                itLine++;
                continue;
            }
            itPaper->second.time = time_val;
            if ( matches.str(3) == "UP" ) {
                vecResult.push_back("{\"Symbol\":\"" + sPaperName + "\",\"Price\":" + std::to_string(iNewPrice) + ",\"Trend\":\"UP\"}" );
            } else {
                int iDeltaPrice = itPaper->second.price - iNewPrice;
                vecResult.push_back(sPaperName + " DOWN " + std::to_string(iDeltaPrice) );
            }
            itPaper->second.price = iNewPrice;
        }
        itLine++;
    }
    if (vecResult.size() == 0) vecResult.push_back("none");
    return vecResult;
}`;

var middle05_description = `none`;
var middle05_text = `нету.`;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
// Сложный уровень: 
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
var hard01_description = `Вы разрабатываете для рекрутинговой компании модуль подбора программистов, которые могут быть привлечены к участию в различных проектах.
Данные о каждом программисте имеют следующий формат:
Фамилия::Стаж::Навык1,Навык2,...,НавыкN
Результатом работы модуля является сортировка программистов по навыкам и стажу (поиск лучших из лучших): список программистов упорядочивается по убыванию количества навыков; если у нескольких программистов количество навыков одинаковое, то они выводятся по убыванию стажа; если у нескольких программистов стаж одинаковый, то их фамилии выводятся в алфавитном порядке.`;
var hard01_text = `#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>
using namespace std;

struct ProgrammerData {
    string family;
    int stage;
    int skills;
};

class ProcessingProgrammerData{
public:
    std::vector<std::string> process(const std::vector<std::string> & lines) const;
};

std::vector<std::string>
ProcessingProgrammerData::process(const std::vector<std::string> & lines) const
{
    ProgrammerData newProg;
    vector<ProgrammerData> vP;

    int delimPos = 0;
    int delim2Pos = 0;
    for (string curStr : lines) {
        if (curStr[0] != ' ') {
            newProg.family = curStr.substr(0, delimPos = curStr.find(':') );
        } else {
            newProg.family = curStr.substr(1, delimPos = curStr.find(':') );
        }
        
        newProg.stage = std::stoi ( curStr.substr(delimPos+2, delim2Pos = curStr.find(':', delimPos + 2) ));
        delim2Pos += 2;
        std::string curSkill = curStr.substr(delim2Pos, curStr.length()-delim2Pos);
        delimPos = 0;
        newProg.skills = 1;
        
        while (  std::string::npos != (delimPos = curSkill.find(',',delimPos))  )
        {
            delimPos++;
            newProg.skills++;
        }
        vP.push_back(newProg);
    }
    std::sort(vP.begin(), vP.end(), [](const auto& a, const auto& b) {
        if (a.skills != b.skills ) return a.skills > b.skills;
        if (a.stage != b.stage ) return a.stage > b.stage ;
        return a.family < b.family;
    } );

    vector<string> vOutResult;
    for (ProgrammerData curP : vP) {
        vOutResult.push_back (curP.family + "::" + std::to_string(curP.skills)  + "::" + std::to_string(curP.stage) );
    }
    return vOutResult;
}`;

var hard02_description = `Вы разрабатываете модуль анализа обработки заказов клиентов для интернет-магазина.
Требуется найти клиентов, которые в указанном месяце сделали возвраты (действия rejected). Для таких клиентов необходимо рассчитать:
*общую сумму возвратов;
*количество возвратных заказов.
Нужно вывести Nclients клиентов с наибольшей суммой возвратов. При равенстве - большее количество заказов, при равенстве - меньший ClientID. Если таких клиентов меньше, чем Nclients, нужно вывести none.`;
var hard02_text = `#include <vector>
#include <iostream>
#include <string_view>
#include <span>
#include <charconv>
#include <map>
#include <algorithm>
using namespace std;

struct ClientData {
    int clientid;
    int sum;
    int orders;
};
std::vector<std::string> process(const std::vector<std::string> & lines) 
// Solution::ProcessingClientData::process(const std::vector<std::string> & lines) const
{
    std::string_view str0 = lines[0];

    int delimPos = str0.find(' ');
    int months = 0;
    std::from_chars_result fcr = std::from_chars(str0.data(), str0.data() + delimPos, months);
    int Nclients = 0;
    fcr = std::from_chars(str0.data() + delimPos+1, str0.data() + str0.size(), Nclients);

    std::vector<std::string>::const_iterator itCurLine = lines.begin() + 1;

    map<int, ClientData> mapClients;
    ClientData newOrder;
    while (itCurLine != lines.end() ) {
        std::string_view viewLine = *itCurLine;
        delimPos = viewLine.find(':');
        int iClid = 0;
        fcr = std::from_chars(viewLine.data(), viewLine.data() + delimPos, iClid);
        int delim2Pos = viewLine.find(':', delimPos+1);
        int iOrdid = 0;
        fcr = std::from_chars(viewLine.data()+delimPos+1, viewLine.data() + delim2Pos-1, iOrdid);

        int delim3Pos = viewLine.find(':', delim2Pos+1);
        std::span<const char> const_span(viewLine.data()+delim2Pos+1, delim3Pos - delim2Pos -1 );
        if ( std::string_view(const_span.data(), const_span.size()) == "accepted") { 
            itCurLine++; 
            continue; 
        }
        int delim4Pos = viewLine.find(':', delim3Pos+1);
        int iCost = 0;
        fcr = std::from_chars(viewLine.data()+delim3Pos+1, viewLine.data() + (delim4Pos), iCost);

        auto itClient = mapClients.find(iClid); // или std::map<std::string, int>::iterator
        if (itClient == mapClients.end()) {
            newOrder.clientid = iClid;
            newOrder.sum = iCost;
            newOrder.orders = 1;
            mapClients.emplace(iClid , newOrder);
        } else {
            itClient->second.sum += iCost;
            itClient->second.orders++;
        }
        itCurLine++;
    }
    // сортировка:
    std::vector<std::pair<int,ClientData>> vecSort(mapClients.begin(), mapClients.end());
    std::sort(vecSort.begin(), vecSort.end(), [](const auto& a, const auto& b) {
        if ( a.second.sum != b.second.sum ) return a.second.sum > b.second.sum ;
        if ( a.second.orders != b.second.orders ) return a.second.orders > b.second.orders ;
        return a.second.clientid < b.second.clientid; // по возрастанию значений
    });

    vector<string> vResult;
    if (Nclients > vecSort.size()) {
        vResult.push_back("none");
        return vResult;
    }
   
    auto itRec = vecSort.begin();
    for (int iCurRec = 0; iCurRec < Nclients; iCurRec++) {
        vResult.push_back( std::to_string(itRec->first) + ":" + std::to_string(itRec->second.sum) + ":" + std::to_string(itRec->second.orders) );
        itRec++;
    }
    return vResult;
}`;

var hard03_description = `Вы разрабатываете модуль обработки данных о поступлении страховых платежей от клиентов.
Требуется разработать метод, который обрабатывает входные данные, считывает общую сумму платежей и возвращает топ-3 типов страхования по общей сумме страховых платежей.
На вход модуля поступают данные в формате CSV:
Type,ClientID,PolicyCode1:Payment1,PolicyCode2:Payment2,PolicyCode3:Payment3,PolicyCode4:Payment4`;
var hard03_text = `#include <algorithm>
#include <unordered_map>
#include <shared_mutex>
#include <mutex>
#include <vector>
#include <iostream>
#include <execution>
#include <ranges>
#include <charconv>

using namespace std;

template <typename Key, typename Value>
class ThreadSafeDictionary {
private:
    std::unordered_map<Key, Value> data;
    mutable std::shared_mutex mtx;
public:
    // Потокобезопасное добавление или обновление значения
    void add_or_update(const Key& key, Value val) {
        std::unique_lock<std::shared_mutex> lock(mtx);
        data[key] += val; // Выполняет суммирование
    }
    // Потокобезопасное чтение
    Value get_value(const Key& key) const {
        std::shared_lock<std::shared_mutex> lock(mtx);
        auto it = data.find(key);
        if (it != data.end()) {
            return it->second;
        }
        return Value(); // Значение по умолчанию, если ключ отсутствует
    }
    auto getKeysView() const {
        return data | std::views::keys;
    }
};

std::vector<std::string> process(const std::vector<std::string> & lines) 
{
    ThreadSafeDictionary<std::string, int> dict;

    std::for_each(std::execution::par, lines.begin(), lines.end(), [&dict](auto& curLine) {
        int delim1 = curLine.find(',');
        int delim2 = curLine.find(',', delim1+1);
        std::string_view sInputLine = curLine;
        std::string_view sType = sInputLine.substr(0, delim1);
        delim1 = delim2;
        delim2 = curLine.find(',', delim1+1);
        std::from_chars_result fcr;
        int iPaySum = 0;
        int payVal = 0;
        int delimDots = 0;
        while ( delim2 != std::string::npos ) {
            delimDots = curLine.find(':', delim1);
            fcr = std::from_chars(curLine.data()+curLine.find(':',delim1)+1, curLine.data() + delim2, payVal);
            iPaySum += payVal;

            delim1 = delim2;
            delim2 = curLine.find(',', delim1+1);
        }
        delimDots = curLine.find(':', delim1);
        fcr = std::from_chars(curLine.data()+ delimDots+1, curLine.data() + curLine.size()-delim1, payVal);
        iPaySum += payVal;

        dict.add_or_update( std::string(sType) , iPaySum);
    });
    auto resKeys = dict.getKeysView();
    std::vector< std::pair<string, int> > sortedPay;
    std::vector<std::string> vResult;

    for (const auto& name : resKeys) {
        int iVal = dict.get_value(name);
        sortedPay.push_back( std::pair<string, int>(name,iVal) );
    }
     std::sort(sortedPay.begin(), sortedPay.end(), [](const auto& a, const auto& b) {
        if ( a.second  != b.second ) return a.second > b.second ;
        return a.first < b. first; 
    });
    std::vector< std::pair<string, int> >::const_iterator it = sortedPay.begin();
    int iNumRec = 0;
    while (it != sortedPay.end() && iNumRec < 3) {
         vResult.push_back( it->first + "," + std::to_string(it->second) );
         it++;
         iNumRec++;
    }
    return vResult;
}`;

var hard04_description = `В связи с модернизацией модуля обработки потока запросов на подключение игроков к игровым серверам MMORPG-игры возникла проблема с увеличением числа отказов в подключении.
Вам необходимо разработать модуль анализа отказов в подключении игроков.
От игроков поступают запросы вида UserID:Action.`;
var hard04_text = `#include <charconv>
#include <iostream>
#include <vector>
#include <set>
using namespace std;

int process(const std::vector<std::string> & lines) 
{
    std::string_view sInputLine = lines[0];
    int delim1 = sInputLine.find(' ');
    int delim2 = sInputLine.find(' ', delim1+1);
    int iServer1, iServer2, iServer3 = 0;

    std::from_chars_result fcr;
    fcr = std::from_chars(sInputLine.data(), sInputLine.data() + delim1, iServer1);
    fcr = std::from_chars(sInputLine.data()+delim1+1, sInputLine.data() + delim2, iServer2);
    fcr = std::from_chars(sInputLine.data()+delim2+1, sInputLine.data() + sInputLine.size()-delim2, iServer3);

    int iTotalGamers = iServer1 + iServer2 + iServer3;
    set<int> setGamers;
    int iRejected = 0;

    std::vector<std::string>::const_iterator itLine = ++lines.begin();
    while (itLine != lines.end() ) {
        
        std::string_view curStr = *itLine ;
        delim1 = curStr.find(':');
        int clid;
        fcr = std::from_chars(curStr.data(), curStr.data() + delim1, clid);
        std::string_view strType = curStr.substr(delim1+1, curStr.size()- delim1);

        if ( setGamers.contains(clid) ) {
            if (strType == "disconnect") {
                setGamers.erase(clid);
            }
        } else {
            if (strType == "connect") {
                if ( setGamers.size() < iTotalGamers ) {
                    setGamers.insert(clid);
                } else {
                    iRejected++;
                }
            }
        }
        itLine++;
    }
    return iRejected;
}`;

var hard05_description = `Вы разрабатываете модуль предварительной обработки данных для системы компьютерного зрения на основе медианного фильтра для последующего определения сильно зашумленных изображений.
На вход модуля подается изображение в виде матрицы точек размером NxN, элемент матрицы - это код цвета в оттенках серого (целое число от 0 до 255 включительно). Число N - это количество строк и столбцов в матрице. N является степенью 2 и N больше или равно 2.`;
var hard05_text = `#include <iostream>
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

    // - - - [processing matrix:] - - - - - - - - - - - - - - - -
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
}`;

var hard06_description = `none`;
var hard06_text = ``;