
#include <vector>
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
        // cout << "str.Len = " << curStr.length() << " pos = " << delim2Pos << endl;

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
        // vOutResult.push_back (curP.family );
    }
    return vOutResult;
}

int main ()
{
    //             1
    //  012345678901
    // vector<string> vInputData = { "Петров::3::JavaScript,TypeScript", "Сидоров::5::C#,Java", "Иванов::5::C#,Java,Python", "Кузнецов::7::Go"} ;
    // vector<string> vInputData = { "Михайлов::5::Java,Python", "Широков::3::C#,JavaScript", "Ковалев::3::Go,Rust", "Субботин::4::Kotlin,Dart", "Власов::6::Scala,Haskell"} ;
    /*
    vector<string> vInputData = { "Киселёв::10::Java,Python,C#,JavaScript,TypeScript,Go,Rust,Kotlin,Dart,Scala,Haskell", 
        "Савельев::10::Java,Python,C#,JavaScript,TypeScript,Go,Rust,Kotlin,Dart,Scala,Haskell", 
        "Орлов::3::Elixir,Clojure", 
        "Медведев::5::PHP,HTML,CSS,SQL,PLSQL", 
        "Егоров::10::Java,Python,C#,JavaScript,TypeScript,Go,Rust,Kotlin,Dart,Scala,Haskell",
        "Фролов::2::Swift,Rubby",
        "Щербаков::4::Bash,Perl,Lua",
        "Кудрявцев::1::VBA"
    } ;
    
    vector<string> vInputData = {
        "Блинов::9::Java,Python,C#,JavaScript,TypeScript,Go,Rust,Kotlin,Dart",
        "Колесников::9::Java,Python,C#,JavaScript,TypeScript,Go,Rust,Kotlin,Dart",
        "Тарасов::3::Scala,Haskell",
        " Самсонов::6::PHP,HTML,CSS,PLSQL,MySQL",
        "Лазарев::9::Java,Python,C#,JavaScript,TypeScript,Go,Rust,Kotlin,Dart",
        "Баранов::2::Elixir,Clojure",
        "Гусев::4::Swift,Ruby",
        "Виноградов::1::Objective-C"
    };
    */

    vector<string> vInputData = {
        "Королев::8::Java,Python,C#,JavaScript,TypeScript,Go,Rust",
        "Ефимов::8::Java,Python,C#,JavaScript,TypeScript,Go,Rust",
        "Шестаков::3::Kotlin,Dart",
        " Сорокин::5::PHP,HTML,CSS,SQL,PLSQL",
        "Носов::8::Java,Python,C#,JavaScript,TypeScript,Go,Rust",
        "Одинцов::2::Scala,Haskell",
        "Крылов::4::Bash,Perl",
        "Коновалов::1::Lua"
    };

    ProcessingProgrammerData ppg;
    vector<string> vResult = ppg.process (vInputData);
    for ( string ss : vResult) {
        cout << ss << endl;
    }
}


