#include <bits/stdc++.h>
using namespace std;

int mod(int a, int b)
{
    int c = a%b;
    if (c < 0) c += b;
    return c;
}

struct manutime
{
    int hours;
    int minutes;
};

manutime operator-(manutime t)
{
    t.hours = -t.hours-1;
    t.minutes = 60-t.minutes;
    return t;
}
manutime operator+(manutime t1, manutime t2)
{
    manutime t = {0};
    t.hours = t1.hours + t2.hours;

    t.minutes = t1.minutes + t2.minutes;
    t.hours += floor(1.0f * t.minutes / 60.0f);
    t.minutes = mod(t.minutes, 60);

    return t;
}
manutime operator-(manutime t1, manutime t2)
{
    return t1 + (-t2);
}
struct TimeDifference
{
    int parseInt(string s, int index)
    {
        int n = 0;
        int sign = 1;
        while (('0' <= s[index] && s[index] <= '9') || s[index] == '-')
        {
            if (s[index] == '-') sign = -1;
            else n = n * 10 + s[index] - '0';

            index++;
            if (index >= s.size())
                break;
        }
        return n * sign;
    }
    manutime parseTime(string s)
    {
        manutime t;

        t.hours = parseInt(s, 0);

        int i = 0;
        while (s[i] != ':')
            i++;
        t.minutes = parseInt(s, i+1);

        return t;
    }
    string calculate(string startTime, string endTime)
    {
        manutime s = parseTime(startTime);
        manutime e = parseTime(endTime);

        manutime dif = e - s;

        stringstream ss;
        if (dif.hours < 0) {
            dif.minutes = 60 - dif.minutes;
            if (dif.minutes == 60) {
                dif.minutes = 0;
                dif.hours--;
            }
            dif.hours++;
            if (dif.hours == 0)
                ss << "-";
        }
        ss << dif.hours << ":";
        if (dif.minutes < 10)
            ss << "0" << dif.minutes;
        else
            ss << dif.minutes;
        return ss.str();
    }
};

// CUT begin
ifstream data("TimeDifference.sample");

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

template <typename T>
string to_string(T t) {
    stringstream s;
    s << t;
    return s.str();
}

string to_string(string t) {
    return "\"" + t + "\"";
}

bool do_test(string startTime, string endTime, string __expected) {
    time_t startClock = clock();
    TimeDifference *instance = new TimeDifference();
    string __result = instance->calculate(startTime, endTime);
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
        string startTime;
        from_stream(startTime);
        string endTime;
        from_stream(endTime);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(startTime, endTime, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1590045762;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 250 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "TimeDifference (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
