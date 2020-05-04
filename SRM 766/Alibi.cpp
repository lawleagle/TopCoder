#include <cstdio>
#include <cmath>
#include <cstring>
#include <ctime>

#include <algorithm>
#include <typeinfo>
#include <vector>
#include <set>
#include <map>

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

class Alibi
{
    public:
    string findMurderer(string murderRoom, int murderTime, vector<int> eventTime, vector<string> eventPerson, vector<string> eventRoom)
    {
        set<string> suspects;
        if (murderRoom == "Hall")
        {
            suspects.insert("White");
            suspects.insert("Green");
            suspects.insert("Peacock");
            suspects.insert("Plum");
            suspects.insert("Scarlett");
            suspects.insert("Mustard");
        }
        for (int i = 0; i < eventTime.size(); ++i)
        {
            if (eventTime[i] > murderTime) break;
            if (eventRoom[i] == murderRoom)
            {
                suspects.insert(eventPerson[i]);
            }
            else
            {
                suspects.erase(eventPerson[i]);
            }
        }
        if (suspects.size() == 1)
            return *suspects.begin();
        return "";
    }
};

// CUT begin
ifstream data("Alibi.sample");

string next_line() {
    string s;
    getline(data, s);
    return s;
}

template <typename T> void from_stream(T &t) {
    stringstream ss(next_line());
    ss >> t;
}

void from_stream(string &s) {
    s = next_line();
}

template <typename T> void from_stream(vector<T> &ts) {
    int len;
    from_stream(len);
    ts.clear();
    for (int i = 0; i < len; ++i) {
        T t;
        from_stream(t);
        ts.push_back(t);
    }
}

template <typename T>
string to_string(T t) {
    stringstream s;
    s << t;
    return s.str();
}

string to_string(string t) {
    return "\"" + t + "\"";
}

bool do_test(string murderRoom, int murderTime, vector<int> eventTime, vector<string> eventPerson, vector<string> eventRoom, string __expected) {
    time_t startClock = clock();
    Alibi *instance = new Alibi();
    string __result = instance->findMurderer(murderRoom, murderTime, eventTime, eventPerson, eventRoom);
    double elapsed = (double)(clock() - startClock) / CLOCKS_PER_SEC;
    delete instance;

    if (__result == __expected) {
        cout << "PASSED!" << " (" << elapsed << " seconds)" << endl;
        return true;
    }
    else {
        cout << "FAILED!" << " (" << elapsed << " seconds)" << endl;
        cout << "           Expected: " << to_string(__expected) << endl;
        cout << "           Received: " << to_string(__result) << endl;
        return false;
    }
}

int run_test(bool mainProcess, const set<int> &case_set, const string command) {
    int cases = 0, passed = 0;
    while (true) {
        if (next_line().find("--") != 0)
            break;
        string murderRoom;
        from_stream(murderRoom);
        int murderTime;
        from_stream(murderTime);
        vector<int> eventTime;
        from_stream(eventTime);
        vector<string> eventPerson;
        from_stream(eventPerson);
        vector<string> eventRoom;
        from_stream(eventRoom);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(murderRoom, murderTime, eventTime, eventPerson, eventRoom, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1588257927;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 300 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    cout.setf(ios::fixed, ios::floatfield);
    cout.precision(2);
    set<int> cases;
    bool mainProcess = true;
    for (int i = 1; i < argc; ++i) {
        if ( string(argv[i]) == "-") {
            mainProcess = false;
        } else {
            cases.insert(atoi(argv[i]));
        }
    }
    if (mainProcess) {
        cout << "Alibi (300 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
