#include <iostream>
#include <fstream>
#include "digraph.h"

using namespace std;

int main(int argc, char *argv[])
{

    vector<string> names {"tarjan1.txt", "tarjan2.txt", "tarjan3.txt", "tarjan4.txt"};

    for (auto s: names)
    {
        ifstream is(s);
        if (is.fail())
        {
            cout << "Can't open file!" << endl;
            is.close();
            return 1;
        }

        digraph D;
        is >> D;
        cout << endl << endl;
        cout << "Input graph:" << endl;
        cout << D << endl;

        cout << "Output: " << endl;
        unordered_map<string, size_t> tscc = D.Tarjan_scc();

        unordered_map<size_t, list<string>> m2;
        for (auto e: tscc)
            m2[e.second].push_front(e.first);

        for (auto p: m2)
        {
            cout << p.first << ": ";
            for (auto e: p.second)
                cout <<  e << " ";
            cout << endl;
        }

        is.close();
    }

    return 0;
}
