
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
        while (curStr[0] == ' ') {
            curStr = curStr.substr(1, curStr.length()-1);
        }
        newProg.family = curStr.substr(0, delimPos = curStr.find(':') );        
        if (newProg.family.length() == 0) continue;
        
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
    system("chcp 65001 > nul");

/*
    vector<string> vInputData = {
        "Киселёв::10::Java,Python,C#,JavaScript,TypeScript,Go,Rust,Kotlin,Dart,Scala,Haskell",
        " ",
        "    Савельев::10::Java,Python,C#,JavaScript,TypeScript,Go,Rust,Kotlin,Dart,Scala,Haskell",
        "Орлов::3::Elixir,Clojure",
        "Медведев::5::PHP,HTML,CSS,SQL,PLSQL",
        "Егоров::10::Java,Python,C#,JavaScript,TypeScript,Go,Rust,Kotlin,Dart,Scala,Haskell",
        "Фролов::2::Swift,Rubby",
        "Щербаков::4::Bash,Perl,Lua",
        "Кудрявцев::1::VBA",
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
        "Коновалов::1::Lua" };


    ProcessingProgrammerData ppg;
    vector<string> vResult = ppg.process (vInputData);
    for ( string ss : vResult) {
        cout << ss << endl;
    }
}


