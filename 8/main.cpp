#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include <numeric>
#include <valarray>

using namespace std;

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

void displ(auto & va, int x, int y)
{
    for (auto yi=0; yi<y; ++yi) {
        for (auto xi=0; xi<x; ++xi)
            cout<<(va[yi*x + xi] > 0 ? '#' : ' ')<<", ";
        cout<<'\n';
    }

}

string run1(ifstream ifs)
{
    size_t X = 50, Y = 6;
    valarray<int> screen(X*Y);
    auto auto_slice = [X,Y](char roc, int i) {
        return roc == 'y' ? slice(i*X, X, 1) : slice(i, Y, X);};

    for (string line; getline(ifs, line);) {
        unsigned int x,y;
        char c;
            sscanf(line.c_str(), "rotate %*s %c=%d by %d", &c, &x, &y) ||
        sscanf(line.c_str(), "%c%*s %dx%d", &c, &x, &y);
        if (c=='r')
            screen[gslice(0, {y,x}, {X,1})] = 1;
        else {
            screen[auto_slice(c, x)] = 
                valarray<int> {screen[auto_slice(c, x)]}.cshift(-y);
        }
           
    }
    displ(screen, X, Y);
    return to_string(screen.sum());
}

string run2(ifstream ifs)
{
    return to_string(0);
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
