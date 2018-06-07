#include <iostream>
#include "network.h"
#include <fstream>
#include <utility>

using namespace std;

int main()
{
    vector<string> files = {"test81.txt", "test82.txt", "test83.txt"};
    for(size_t i = 0; i < 3; i ++) {
        network N;

        ifstream is(files[i]);
        if (is.fail()) {
            cout << "Can't open file!" << endl;
            return 1;
        }

        is >> N;


        std::unordered_map<string, std::size_t> scc = N.scc();

        string status = "rankable";
        if (scc["nc"] != N.n()) {
            for (auto v: N.V()) {
                for (auto d: N.Adj(v)) {
                    if (scc[v] == scc[d] && N.cost(v, d) != 0) {
                        status = "unrankable";
                    }
                }
            }
        }
        cout << files[i] << " is " << status << endl;

    }
    return 0;
}
