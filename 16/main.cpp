#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include <string>

using namespace std;

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

string checksum(ifstream & ifs, bool part2) {
    string is;
    getline(ifs, is);
    size_t length;
    if (part2)
        length = 35651584;
    else {
        string line;
        getline(ifs, line);
        length = stoul(line);
    }

    std::cout<<"is: "<<is<<'\n';
    std::cout<<"length : "<<length <<'\n';

    vector<bool> isv;
    for (auto c : is)
        isv.push_back(c=='1');

    while (isv.size() < length) {
        size_t old_length = isv.size();
        isv.push_back(0);
        for (size_t i=0; i<old_length; ++i)
            isv.push_back(!isv[old_length - 1 - i]);
    }

    isv.resize(length);

    vector<bool> csm;

    do {
        for (size_t i=0; i<isv.size(); i+=2)
            csm.push_back(isv[i] == isv[i+1]);
        isv = csm;
        csm.clear();
    } while ((isv.size() % 2) == 0);

    string ret;
    for (auto b : isv)
        ret.push_back(b ? '1' : '0');

    return ret;
}


string run1(ifstream ifs)
{
    return checksum(ifs, false);
}

string run2(ifstream ifs)
{
    return checksum(ifs, true);
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
