#include <iostream>
#include <fstream>
#include "graph.h"

using namespace std;

void buildGraph(string dictName, graph & G);
void findPathWrapper(string start, string end, graph & G);
int compare(string a, string b);


int main(int argc, char *argv[])
{
    //Doublets puzzle code
    cout << "Doublet's Puzzle: " << endl;
    graph G;
    buildGraph("knuth.txt", G);

    findPathWrapper("black", "white", G);
    findPathWrapper("tears", "smile", G);
    findPathWrapper("small", "giant", G);
    findPathWrapper("stone", "money", G);
    findPathWrapper("angel", "devil", G);
    findPathWrapper("amino", "right", G);
    findPathWrapper("amigo", "signs", G);

    //Code for complete1.txt
    ifstream is("complete1.txt");

    if (is.fail())
    {
        cout << "Can't open file!" << endl;
        return 1;
    }
    graph H;

    cout << "Enter a graph: " << endl;
    is >> H;

    cout << "Read graph: " << endl;
    cout << H << endl;

    cout << "complete1.txt complete? " << H.is_complete() << endl;
    is.close();

    // Code for complete2.txt

    is.open("complete2.txt");

    if (is.fail())
    {
        cout << "Can't open file!" << endl;
        return 1;
    }
    graph I;

    cout << "Enter a graph: " << endl;
    is >> I;

    cout << "Read graph: " << endl;
    cout << I << endl;

    cout << "complete2.txt complete? " << I.is_complete() << endl;

    return 0;
}

//pre: an empty dictionary is passed in
//post: dict is populated with contents of knuth.txt
void buildGraph(string dictName, graph & G){
    ifstream file(dictName.c_str());
    string str;
    if(file.fail()){
        cout << "dictionary failed to open!" << endl;
    }
    cout << "Importing dictionary... (this may take a few minutes)" << endl;
    while (getline(file, str)) {
        G.add_vertex(str);
    }

    for(auto a: G.V()){
        for(auto b: G.V()){
            if(compare(a, b) == 1){
                G.add_edge(a, b);
            }
        }
    }

}
void findPathWrapper(string start, string end, graph & G){
    std::unordered_set<string> visited;
    vector <string > path = G.findPath(start, end, visited);
    cout << "Path from " << start << " to " << end << ": ";
    if(path.size() == 0){
        cout << "No Path" << endl;
        return;
    }
    for(int i = 0 ; i < path.size(); i++){
        cout << path[i] << " ";
    }
    cout << endl;
}

// Pre: Two strings a and b
// Post: Returns the number of differing letters between the two strings
int compare(string a, string b){
    int diff = 0;
    int i = 0;
    while(i < a.size() && i < b.size()){
        if(a[i] != b[i]){
            diff++;
        }
        i++;
    }
    return diff;
}