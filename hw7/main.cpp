#include <iostream>
#include "mlist.h"
#include <set>
#include <algorithm>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

bool check(int n)
{
    mlist<int> M;
    set<int> S;
    vector<int> V;

    for (int i = 1; i <= n; ++i)
        V.push_back(i);

    random_shuffle(V.begin(), V.end());

    int pinsert(0), pdelete(0);

    for (int i = 1; i <= n; ++i)
    {
        assert(S.size() == M.size());
        int choice = rand() % 5;
        switch(choice)
        {
            case 0:
                if (S.size() == 0)
                    break;
                cout << "Median: ";
                if (M.median() != *next(S.begin(), ((1+S.size())/2 - 1)))
                    return false;
                cout << "passed" << endl;
                break;

            case 1:
            {
                cout << "Member: ";
                int x = rand() % n + 1;
                if (M.member(x) != (S.count(x) == 1))
                    return false;
                cout << "passed" << endl;
                break;
            }

            case 2:
                cout << "Insert " << V[pinsert] << ": ";
                M.insert(V[pinsert]);
                S.insert(V[pinsert]);
                ++pinsert;
                cout << "passed" << endl;
                break;

            case 3:
                cout << "Delete ";
                if (pdelete <= pinsert)
                {
                    cout << V[pdelete] << ": ";
                    M.erase(V[pdelete]);
                    S.erase(V[pdelete]);
                    ++pdelete;
                }
                cout << "passed" << endl;
                break;

            case 4:
                cout << "Empty: ";
                if (M.empty() != S.empty())
                    return false;
                cout << "passed" << endl;
                break;
        }
    }
    return true;
}

bool check2(int n)
{
    vector<int> V;
    for (int i = 1; i <= n; ++i)
        V.push_back(i);

    random_shuffle(V.begin(), V.end());

    mlist<int> M;
    set<int> S;

    for (auto e: V)
    {
        M.insert(e);
        S.insert(e);
        if (M.median() != *next(S.begin(), ((1+S.size())/2 - 1)))
            return false;
    }
    return true;
}


int main()
{
    srand(time(0));
    for (int i = 1; i <= 100; ++i)
    {
        cout << "i = " << i << endl;
        if (!check(1000))
        {
            cout << "FAILED" << endl;
            return 1;
        }
        if (!check2(1000))
        {
            cout << "FAILED" << endl;
            return 1;
        }
    }

    cout << "PASSED!" << endl;
    return 0;
}


