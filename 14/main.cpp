#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include "md5.h"
#include <set>

using namespace std;

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}


vector<string> xlet(string hash, size_t len, bool all)
{
    vector<string> res;
    for (size_t i=0; i<hash.size()-(len-1); ++i) {
        for (size_t j=1; j<len; ++j)
            if (hash[i] != hash[i+j])
                goto skip;
        res.push_back(hash.substr(i,len));
        if (!all)
            return res;
skip:   ;
    }

    return res;
}

size_t iofith(string salt, size_t ith, size_t extra_hashes)
{
    size_t keycount {0};
    map<size_t, string> triplet_indices;
    map<size_t, vector<string>> quintet_indices;
    for (size_t i=0; i<1000; ++i) {
        string hash = md5(salt+to_string(i));
        for (size_t i=0; i<extra_hashes; ++i)
            hash = md5(hash);
        for (auto trplt : xlet(hash, 3, false)) {
            triplet_indices[i] = trplt;
        }
        for (auto qntt : xlet(hash, 5, true)) {
            quintet_indices[i].push_back(qntt);
        }
    }

    for (size_t i=1000; i<numeric_limits<size_t>::max(); ++i) {
        quintet_indices.erase(i-1000);

        string hash = md5(salt+to_string(i));
        for (size_t i=0; i<extra_hashes; ++i)
            hash = md5(hash);

        for (auto qntt : xlet(hash, 5, true)) {
            quintet_indices[i].push_back(qntt);
        }
        for (auto trplt : xlet(hash, 3, false)) {
            triplet_indices[i] = trplt;
        }

        if (i == 22511) {
            std::cout<<"keycount: "<<keycount<<'\n';
            std::cout<<"triplet_indices.contains(i-1000): "<<triplet_indices.contains(i-1000)<<'\n';

        }
        if (!triplet_indices.contains(i-1000))
            continue;

        auto trplt = triplet_indices[i-1000];
        size_t count {0};
        for (auto [qk, qv] : quintet_indices)
            for (auto qntt : qv)
                if (trplt == qntt.substr(0,3)) {
                    ++count;
                    break;
                }

        if (count == 1) {
            ++keycount;
            std::cout<<"keycount: "<<keycount<<'\n';
            if (keycount == ith)
                return i - 1000;
        }
        triplet_indices.erase(i-1000);
    }
    return 0;
}

string run1(ifstream ifs)
{
    string salt;
    getline(ifs, salt);
    return to_string(iofith(salt, 64, 0));
}

string run2(ifstream ifs)
{
    string salt;
    getline(ifs, salt);
    std::cout<<"salt: "<<salt<<'\n';
    return to_string(iofith(salt, 64, 2016));
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
