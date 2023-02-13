#include <vector>
#include <iterator>
#include <numeric>
#include <iostream>

using namespace std;

void displ(auto itrbl) {
    for (auto val : itrbl)
        cout<<val<<", ";
    cout<<'\n';
}

void displl(auto itrbl) {
    for (auto val : itrbl)
        displ(val);
    cout<<'\n';
}

template<typename InputIt, typename T=InputIt::value_type>
class Combinations {
    public:
    // member typedefs provided through inheriting from std::iterator
        class Itr: public iterator<
                        input_iterator_tag,   // iterator_category
                        vector<T>,             // value_type
                        int,                      // difference_type
                        const vector<T>*,      // pointer
                        vector<T> &>            // reference
        {
            InputIt begin;
            InputIt end;
            int R;
            bool done;
            int N;
            vector<int> inds;
            vector<T> cur;
        public:
            explicit Itr(InputIt begin, InputIt end, int R, bool done) :
                     begin{begin},
                     end{end},
                     R{R},
                     done{done},
                     N{int(distance(begin, end))},
                     inds(R),
                     cur(R)
            {
                if (done)
                    iota(inds.begin(), inds.end(), N-R);
                else
                    iota(inds.begin(), inds.end(), 0);
                for (size_t i = 0; i<inds.size(); ++i)
                    cur[i] = *(begin+inds[i]);
            }

            Itr& operator++()
            { 
                int i = inds.size() - 1;
                for(; i>=0; --i)
                    if (inds[i] !=  i + N - R)
                        break;
                if (i == -1) {
                    done = true;
                    return *this;
                }

                iota(inds.begin()+i, inds.end(), inds[i] + 1);

                for (size_t i = 0; i<inds.size(); ++i)
                    cur[i] = *(begin+inds[i]);

                return *this;
            }

            Itr operator++(int)
            {
                Itr retval = *this; ++(*this);
                return retval;
            }

            bool operator==(Itr other) const
            {
                return inds == other.inds && done == other.done;
            }

            bool operator!=(Itr other) const {return !(*this == other);}

            const vector<T> & operator*() const 
            {
                return cur;
            }
        };

        Combinations(InputIt begin, InputIt end, int R) : cbegin(begin), cend(end), cR(R) {}

        Itr begin() {return Itr(cbegin, cend, cR, false);}
        Itr end() {return Itr(cbegin, cend, cR, true);}
        InputIt cbegin;
        InputIt cend;
        int cR;
};

template<typename InputIt, typename T=InputIt::value_type>
class Combinations_with_replacement {
    public:
    // member typedefs provided through inheriting from std::iterator
        class Itr: public iterator<
                        input_iterator_tag,   // iterator_category
                        vector<T>,             // value_type
                        int,                      // difference_type
                        const vector<T>*,      // pointer
                        vector<T> &>            // reference
        {
            InputIt begin;
            InputIt end;
            int R;
            bool done;
            int N;
            vector<int> inds;
            vector<T> cur;
        public:
            explicit Itr(InputIt begin, InputIt end, int R, bool done) :
                     begin{begin},
                     end{end},
                     R{R},
                     done{done},
                     N{int(distance(begin, end))},
                     inds(R, done ? distance(begin, end) - 1 : 0),
                     cur(R, *begin)
                     {}

            Itr& operator++()
            { 
                int i = inds.size() - 1;
                for(; i>=-1; --i)
                    if (inds[i] != N - 1)
                        break;
                if (i < 0) {
                    done = true;
                    return *this;
                }

                int v = inds[i] + 1;
                for (size_t j=i; j<inds.size(); ++j)
                    inds[j] = v;

                for (size_t i = 0; i<inds.size(); ++i)
                    cur[i] = *(begin+inds[i]);

                return *this;
            }

            Itr operator++(int)
            {
                Itr retval = *this; ++(*this);
                return retval;
            }

            bool operator==(Itr other) const
            {
                return inds == other.inds && done == other.done;
            }

            bool operator!=(Itr other) const {return !(*this == other);}

            const vector<T> & operator*() const 
            {
                return cur;
            }
        };
        Combinations_with_replacement(InputIt begin, InputIt end, int R) : cbegin(begin), cend(end), cR(R) {}

        Itr begin() {return Itr(cbegin, cend, cR, false);}
        Itr end() {return Itr(cbegin, cend, cR, true);}
        InputIt cbegin;
        InputIt cend;
        int cR;
};

auto powerset(vector<int> itrbl) {
    vector<vector<int>> ps;
    for (size_t r=0; r<itrbl.size() + 1; ++r)
        for (auto cmbn : Combinations(itrbl.begin(), itrbl.end(), r))
            ps.emplace_back(cmbn);
    return ps;
}

