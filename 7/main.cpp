#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>

using namespace std;
using sri = sregex_iterator;

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}


bool has_ABBA(const string s)
{
    for (size_t i=0; i+3<s.size(); ++i)
        if (s[i] == s[i+3] && s[i+1] == s[i+2] && s[i] != s[i+1])
            return true;
    return false;
}

string run1(ifstream ifs)
{
    int no_tls_ip {0};
    using sri = sregex_iterator;
    regex hyper_pat {R"(\[.*?\])"};
    for (string line; getline(ifs, line);) {
        auto it = sri(line.begin(), line.end(), hyper_pat);
        for(; it != sri {}; ++it) {
            if (has_ABBA((*it).str()))
                goto nope;
        }
        line = regex_replace(line, hyper_pat, " ");
        if (has_ABBA(line))
            ++no_tls_ip;
nope:;
    }
    return to_string(no_tls_ip);
}

vector<string> get_BABs(string s)
{
    vector<string> ret;
    regex BAB_pat {R"((.)(?!\1).\1)"};
    smatch sm;
    for (auto sit = s.cbegin();regex_search(sit, s.cend(), sm, BAB_pat);) {
        ret.emplace_back(sm[0].str());
        sit += sm.position()+1;
    }
    return ret;
}

string run2(ifstream ifs)
{
    int no_tls_ip {0};
    regex hyper_pat {R"(\[.*?\])"};
    for (string line; getline(ifs, line);) {

        vector<string> babs;
        auto it = sri(line.begin(), line.end(), hyper_pat);
        for(; it != sri {}; ++it) {
            string in_b = (*it).str();
            auto new_babs = get_BABs(in_b);
            babs.insert(babs.end(), new_babs.begin(), new_babs.end());
        }

        line = regex_replace(line, hyper_pat, "  ");
        auto abas = get_BABs(line);
        for (auto aba : abas) {
            if (find(babs.begin(), babs.end(), aba.substr(1,2)+aba.substr(1,1)) != babs.end()) {
                ++no_tls_ip;
                break;
            }
        }

    }
    return to_string(no_tls_ip);
}

int main(int argc, char** argv)
{
    string (*funs[])(ifstream) = {&run1, &run2};
    auto start = chrono::steady_clock::now();
    auto res = funs[atoi(argv[1])-1](ifstream {argv[2]});
    auto end = chrono::steady_clock::now();
    chrono::duration<double> time_s = end-start;
    cout<<"result: "<<res<<'\n';
    cout<<fixed;
    cout.precision(6);
    cout<<"time: "<<time_s.count()<<'\n';
}
