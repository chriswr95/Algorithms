#ifndef DIGRAPH_H
#define DIGRAPH_H

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <cassert>
#include <iostream>
#include <algorithm>
#include <stack>
#include <list>

class digraph
{
public:
    typedef std::string T;
    typedef std::unordered_set<T> TSet;

    digraph()
    {
        _n = _m = 0;
    }

    // pre: none
    // post: returns the number of vertices
    std::size_t n() const
    {
        return _n;
    }

    // pre: none
    // post: returns the number of edges
    std::size_t m() const
    {
        return _m;
    }

    std::size_t outdegree(const T & v) const
    {

        assert(_V.count(v) == 1);
        return _t.at(v).size();
    }

    std::size_t indegree(const T & v) const
    {
        std::size_t ans(0);

        assert(_V.count(v) == 1);

        for (auto s: _V)
            if (_t.at(s).count(v) == 1)
                ++ans;

        return ans;
    }

    void add_vertex(const T & v)
    {
        if (_V.count(v) == 1)
            return;

        _t[v] = TSet();
        _V.insert(v);
        ++_n;

    }

    void add_edge(const T & s, const T & d)
    {
        assert(_V.count(s) == 1 && _V.count(d) == 1);

        if ((_t[s].insert(d)).second == true)
            ++_m;

    }

    TSet V() const
    {
        return _V;
    }

    TSet Adj(const T & v) const
    {
        assert(_V.count(v) == 1);
        return _t.at(v);
    }

    void remove_edge(const T & s, const T & d)
    {
        assert(_V.count(s) == 1 && _V.count(d) == 1);

        _m -= _t[s].erase(d);
    }

    void remove_vertex(const T & v)
    {
        assert(_V.count(v) == 1);
        for (auto s: _V)
        {
            _m -= _t[s].erase(v);

        }

        _t.erase(v);
        _V.erase(v);
        --_n;
    }

    digraph reverse() const
    {
        digraph R;

        for (auto v: _V)
            R.add_vertex(v);


        for (auto v: _V)
            for (auto w: Adj(v))
                R.add_edge(w, v);

        return R;
    }

    void rdfs(const T & s,
              std::unordered_map<T, std::size_t> & pre,
              std::unordered_map<T, std::size_t> & post,
              std::size_t &time,
              std::list<T> & l) const
    {
        pre[s] = time++;
        for (auto v: Adj(s))
        {
            if (pre.count(v) == 0)
            {
                //std::cout << s << ", " << v << " is a tree edge" << std::endl;
                rdfs(v, pre, post, time, l);
            }
            else
            {
                if (post.count(v) == 0)
                    // std::cout << s << ", " << v << " is a back edge" << std::endl;
                    ;
                else
                {
                    if (pre[v] > pre[s])
                        // std::cout << s << ", " << v << " is a forward edge" << std::endl;
                        ;
                    else
                        //std::cout << s << ", " << v << " is a cross edge" << std::endl;
                        ;


                }
            }
        }
        post[s] = time++;
        l.push_front(s);
    }

    void dfs() const
    {
        std::unordered_map<T, std::size_t> pre, post;
        std::list<T> l;
        std::size_t time(1);

        for (auto s: _V)
            if (pre.count(s) == 0)
                rdfs(s, pre, post, time, l);
    }

    void ts1(const T & v,
             std::unordered_map<T, std::size_t> & pre,
             std::unordered_map<T, std::size_t> & post,
             std::size_t & time,
             std::stack<T> & st) const
    {
        pre[v] =time++;
        for (auto w: Adj(v))
        {
            if (pre.count(w) == 0)
                ts1(w, pre, post, time, st);
        }
        post[v] = time++;
        st.push(v);

    }
    std::vector<T> ts() const
    {
        std::stack<T> st;

        std::unordered_map<T, std::size_t> pre, post;
        std::size_t time(1);

        for (auto start: _V)
        {
            if (pre.count(start) == 0)
                ts1(start, pre, post, time, st);
        }

        std::vector<T> ans;

        while (!st.empty())
        {
            ans.push_back(st.top());
            st.pop();
        }

        return ans;

    }

    std::unordered_map<T, std::size_t> scc() const
    {
        digraph R = reverse();

        std::unordered_map<T, std::size_t> pre, post;
        std::list<T> l;
        std::size_t time(1);

        for (auto s: R.V())
            if (pre.count(s) == 0)
                R.rdfs(s, pre, post, time, l);


        pre.clear();
        post.clear();
        time =1 ;

        std::size_t nc(0);
        std::unordered_map<T, std::size_t> ans;

        for (auto v: l)
        {
            std::list<T> c;
            if (pre.count(v) == 0)
            {

                rdfs(v, pre, post, time, c);
                ++nc;

                std::cout << "Component: ";
                for (auto e: c)
                {
                    std::cout << e << " ";
                    ans[e] = nc;
                }
                std::cout << std::endl;
            }
        }

        return ans;
    }

    bool isAdj(T s, T d) const
    {
       if(Adj(s).count(d) > 0)
       {
           return true;
       }
        return false;

    }

    std::vector<std::vector<std::size_t>> apsp() const
    {
        //Need to place a numerical ordering on vertices
        std::vector<T> vertices;
        for(auto v: V())
        {
            vertices.push_back(v);
        }
        sort(vertices.begin(), vertices.end());
        //debug
        std::cout << "test: vertices in sorted order: " << std::endl;
        for (auto v: vertices)
            std::cout << v << " ";
        std::cout << std::endl;
        std::cout << std::endl;
        //end debug

        //Initialize Matrix
        std::vector<std::vector<std::size_t>> matrix;
        matrix.resize(vertices.size());
        for(std::size_t i = 0; i < matrix.size(); i++)
        {
            matrix[i].resize(vertices.size());
            for(std::size_t j = 0; j < matrix[0].size(); j++)
            {
                if(i == j) {
                    matrix[i][j] = 0;
                } else if (isAdj(vertices[i], vertices[j])) {
                    matrix[i][j] = 1;
                } else {
                    matrix[i][j] = vertices.size();
                }
            }
        }

        //Find Shortest Paths
        for(std::size_t k = 0; k < vertices.size(); k++){
            for(std::size_t i = 0; i < vertices.size(); i++){
                for(std::size_t j = 0; j < vertices.size(); j++){
                    if(matrix[i][j] > matrix[i][k] + matrix[k][j])
                        matrix[i][j] = matrix[i][k] + matrix[k][j];
                }
            }
        }

        return matrix;
    }



private:

    std::unordered_map<T, TSet> _t;     //  adjacency "lists"
    TSet _V;                            //  vector of vertices
    std::size_t _n, _m;                 //  number of vertices and edges
};


std::ostream & operator << (std::ostream & os, const digraph & D)
{
    os << D.n() << " " << D.m() << std::endl;
    for (auto v: D.V())
        os << v << " ";
    os << std::endl;
    for (auto v: D.V())
    {
        os << v << ": ";
        for (auto n: D.Adj(v))
            os << n << " ";
        os << std::endl;
    }
    return os;
}

std::istream & operator >> (std::istream & is, digraph & D)
{
    std::size_t n, m;
    std::string s, d;

    is >> n >> m;

    for (std::size_t i = 0; i < n; ++i)
    {
        is >> s;
        D.add_vertex(s);
    }

    for (std::size_t i = 0; i < m; ++i)
    {
        is >> s >> d;
        D.add_edge(s, d);
    }

    return is;


}





#endif // DIGRAPH_H
