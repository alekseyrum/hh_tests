
#include <algorithm>
#include <unordered_map>
#include <shared_mutex>
#include <mutex>
#include <vector>
#include <iostream>
#include <execution>
#include <charconv>

using namespace std;

template <typename Key, typename Value>
class ThreadSafeDictionary {
private:
    std::unordered_map<Key, Value> data;
    mutable std::shared_mutex mtx;
public:
    void add_or_update(const Key& key, Value val) {
        std::unique_lock<std::shared_mutex> lock(mtx);
        data[key] += val; 
    }
    Value get_value(const Key& key) const {
        std::shared_lock<std::shared_mutex> lock(mtx);
        auto it = data.find(key);
        if (it != data.end()) {
            return it->second;
        }
        return Value(); 
    }
    vector<Key> getAllKeys() const {
        vector<Key> vRet;
        vRet.reserve( data.size() );
        for (const auto& pair : data) {
            vRet.push_back(pair.first);
        }
        return vRet;
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
    auto resKeys = dict.getAllKeys();
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
}

int main()
{
    system("chcp 65001 > nul");
    /*
    vector<string> vInputData = { 
       "Car,10000,ABCD:5000,EFGH:3000",
        "Home,10001,IJKL:10000",
        "Car,10001,MNOP:7000,QRST:2000",
        "Life,10003,UVWX:15000",
        "Home,10004,YZAB:8000,CDEF:4000",
        "Life,10005,GHIJ:12000" };

    
    vector<string> vInputData = { 
        "Life,90006,IJKL:40000",
        "Life,90006,IJKL:40000,MNOP:50000",
        "Life,90006,IJKL:40000,MNOP:50000,QRST:60000",
        "Life,90006,IJKL:40000,MNOP:50000,QRST:60000,UVWX:70000" };

    vector<string> vInputData = { 
        "Medical,70001,KLMN:25000",
        "Dental,70002,OPQR:35000,STUV:45000",
        "MentalHealth,70003,WXYZ:55000",
        "SubstanceAbuse,70004,ABCD:65000,EFGH:75000",
        "Vision,70005,IJKL:85000",
        "Drug,70006,MNOP:95000,QRST:5000",
        "ShortTermCare,70007,UVWX:15000",
        "LongTermCare,70008,YZAB:25000,CDEF:35000" };

    vector<string> vInputData = { 
        "Hospice,80001,GHIJ:45000",
        "HomeHealth,80002,KLMN:55000,OPQR:65000",
        "DMEPOS,80003,STUV:75000",
        "AdvancedImaging,80004,WXYZ:85000,ABCF:95000",
        "MRIs,80005,EFGH:5000",
        "CTScans,80006,IJKL:15000,MNOP:25000",
        "PETScans,80007,QRST:35000",
        "PreventiveCare,80008,UWX:45000,YZAB:55000" };
*/

    vector<string> vInputData = { 
    "Screening,90001,CDFE:10000",
    "Immunization,90002,GHIJ:20000,KLMN:30000",
    "Rehabilitation,90003,OPQR:40000",
    "Home,90004,STUV:50000,WXYZ:10000,ABCD:20000",
    "Car,90005,EFGH:30000",
    "Life,90006,IJKL:40000,MNOP:50000,QRST:60000,UVWX:70000",
    "Pet,90007,YZAB:80000",
    "Fire,90008,CDFE:90000,GHIJ:10000",
    "Medical,90009,KLMN:20000,OPQR:30000",
    "Dental,90010,STUV:40000",
    "MentalHealth,90011,WXYZ:50000,ABCD:60000,EFGH:70000",
    "SubstanceAbuse,90012,IJKL:80000,MNOP:90000" };

    vector<string> vResult = process(vInputData);
    for ( auto ss : vResult) {
        cout << ss << endl;
    }
}

