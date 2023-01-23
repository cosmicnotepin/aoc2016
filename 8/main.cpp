#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include <numeric>

using namespace std;

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

void displ(auto itrbl) {
    for (auto val : itrbl) {
        cout<<(val ? '#' : ' ')<<", ";
    }
    cout<<'\n';
}

void displl(auto itrbl) {
    for (auto val : itrbl)
        displ(val);
    cout<<'\n';
}

void rotate_row(array<array<bool, 50>, 6> & screen,
        size_t row, size_t count)
{
    rotate(screen[row].begin(), screen[row].end()-count, screen[row].end()); 
}

void rotate_col(array<array<bool, 50>, 6> & screen,
        size_t col, size_t count)
{
    array<bool, 6> orig_col;
    for (size_t i=0; i<6; ++i)
        orig_col[i] = screen[i][col];
    rotate(orig_col.begin(), orig_col.end()-count, orig_col.end()); 
    for (size_t i=0; i<6; ++i)
        screen[i][col] = orig_col[i];
}


string run1(ifstream ifs)
{
    unordered_map<string, function<decltype(rotate_row)>> rot_funs 
    {{"column", rotate_col}, {"row", rotate_row}};
    array<array<bool, 50>, 6> screen {false};
    regex rect_pat {R"(rect (\d+)x(\d+))"};
    regex rot_pat {R"(rotate (row|column) (x|y)=(\d+) by (\d+))"};
    smatch sm;
    for (string line; getline(ifs, line);) {
        if (regex_match(line, sm, rect_pat)) {
            for (size_t row=0; row<stoul(sm[2].str()); ++row)
                for (size_t col=0; col<stoul(sm[1].str()); ++col)
                    screen[row][col] = true;
            displl(screen);
        } else if (regex_match(line, sm, rot_pat)) {
            rot_funs[sm[1].str()](screen, stoul(sm[3]), stoul(sm[4]));
            displl(screen);
        }
    }
    int res = accumulate(screen.begin(), screen.end(), 0, 
            [] (auto acc, auto & lhs) {
            return acc + accumulate(lhs.begin(), lhs.end(), 0);});
    return to_string(res);
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
