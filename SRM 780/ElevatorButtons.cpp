#include <bits/stdc++.h>
using namespace std;

struct ElevatorButtons
{
    void push(vector<int> &res, vector<int> &stops, int direction, int currentFloor)
    {
        if (direction > 0)
        {
            for (auto it = stops.begin(); it != stops.end(); ++it)
            {
                if (*it > currentFloor)
                {
                    res.push_back(*it);
                }
            }
        }
        else
        {
            for (auto it = stops.rbegin(); it != stops.rend(); ++it)
            {
                if (*it < currentFloor)
                {
                    res.push_back(*it);
                }
            }
        }
    }
    vector<int> nextStops(int currentFloor, int direction, vector<int> stops)
    {
        vector<int> res;

        sort(stops.begin(), stops.end());
        stops.erase(unique(stops.begin(), stops.end()), stops.end());
        push(res, stops, direction, currentFloor);
        push(res, stops, -direction, currentFloor);

        return res;
    }
};

// CUT begin
ifstream data("ElevatorButtons.sample");

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

template <typename T> string to_string(vector<T> ts) {
    stringstream s;
    s << "[ ";
    for (int i = 0; i < ts.size(); ++i) {
        if (i > 0) s << ", ";
        s << to_string(ts[i]);
    }
    s << " ]";
    return s.str();
}

bool do_test(int currentFloor, int currentDirection, vector<int> buttonsPressed, vector<int> __expected) {
    time_t startClock = clock();
    ElevatorButtons *instance = new ElevatorButtons();
    vector<int> __result = instance->nextStops(currentFloor, currentDirection, buttonsPressed);
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
        int currentFloor;
        from_stream(currentFloor);
        int currentDirection;
        from_stream(currentDirection);
        vector<int> buttonsPressed;
        from_stream(buttonsPressed);
        next_line();
        vector<int> __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(currentFloor, currentDirection, buttonsPressed, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1588851988;
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
        cout << "ElevatorButtons (300 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end