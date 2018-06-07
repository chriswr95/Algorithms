#ifndef NETWORK_H
#define NETWORK_H

#include "wedge.h"
#include "digraph.h"
#include <set>
#include "dary-heap.h"

class network: public digraph
{

public:
    typedef std::pair<T, T> Edge;

    network()
    {}

    void add_edge(const T &s, const T &d, double w)
    {
        digraph::add_edge(s, d);
        _w[{s, d}] = w;
    }

    void add_edge(const WEdge & e)
    {
        add_edge(e.s, e.d, e.w);
    }

    void remove_edge(const T &s, const T &d)
    {
        digraph::remove_edge(s, d);
        _w.erase({s,d});
    }

    void remove_edge(const Edge & e)
    {
        remove_edge(e.first, e.second);
    }

    void remove_vertex(const T & v)
    {
        for (auto w: Adj(v))
            _w.erase({v, w});

        for (auto w: V())
            _w.erase({w, v});

        digraph::remove_vertex(v);

    }

    double cost(const T & s, const T & d) const
    {
        return _w.at({s, d});
    }

    double cost(const Edge & e) const
    {
        return _w.at(e);
    }

    std::set<WEdge> E() const
    {
        std::set<WEdge> ans;

        for (auto v: V())
            for (auto w: Adj(v))
                ans.insert({v, w, cost(v, w)});

        return ans;

    }

    std::unordered_map<Edge, double> Floyd() const
    {
        std::unordered_map<Edge, double> d;
        std::unordered_map<Edge, T> I;

        for (auto v: V())
            for (auto w: V())
            {
                if (v == w)
                    d[{v,w}] = 0;
                else if (_w.count({v,w}) == 1)
                    d[{v,w}] = _w.at({v,w});
                else
                    d[{v,w}] = std::numeric_limits<double>::infinity();
            }

        for (auto k: V())
            for (auto i: V())
                for (auto j: V())
                {
                    double t= d[{i,k}] + d[{k,j}];
                    if (t < d[{i,j}])
                    {
                        d[{i,j}] = t;
                        I[{i,j}] = k;
                    }
                }

        return d;


    }

    network Bellman_Ford(const T & s) const
    {

        std::unordered_map<T, double> d;
        std::unordered_map<T, T> parent;

        // SSSP_0
        for (auto v: V())
            d[v] = std::numeric_limits<double>::infinity();
        d[s] =0;

        for (std::size_t l = 1; l < n(); ++l)
            for (auto e: E())
            {
                double temp = d[e.s] + e.w;
                if (d[e.d] > temp)
                {
                    d[e.d] = temp;
                    parent[e.d] = e.s;
                }

            }

        network ans;

        for (auto v: V())
            ans.add_vertex(v);

        for (auto e: parent)
            ans.add_edge(e.second, e.first, cost(e.second, e.first));

        return ans;




    }

    network Dijkstra(const T & s) const
    {
        network ans;
        dary_heap<WEdge> H;
        std::unordered_map<T, WEdge> best;

        for (auto v: V())
            ans.add_vertex(v);

        H.push({s, s, 0});

        while (!H.empty())
        {
            WEdge e(H.min());
            H.pop_min();

            if (e.s != e.d)
                ans.add_edge(e.s, e.d, cost(e.s, e.d));

            for (auto n: Adj(e.d))
            {
                WEdge fringe({e.d, n, best[e.d].w + cost(e.d, n)});

                if (best.count(n) == 0)
                {
                    H.push(fringe);
                    best[n] = fringe;
                }
                else if (fringe.w < best[n].w)
                {
                    H.decrease_key(best[n], fringe);
                    best[n] = fringe;
                }
            }

        }

        return ans;

    }


private:
    std::unordered_map<Edge, double> _w;  //maps an edge to its cost

};

std::ostream & operator << (std::ostream & os, const network & N)
{
    os << N.n() << " " << N.m() << std::endl;
    for (auto v: N.V())
        os << v << " ";
    os << std::endl;
    for (auto v: N.V())
        for (auto w: N.Adj(v))
            os << v << " " << w << " " << N.cost(v, w) << std::endl;

    return os;
}

std::istream & operator >> (std::istream & is, network & N)
{
    std::size_t n, m;
    std::string s, d;
    double w;

    is >> n >> m;

    for (std::size_t i = 0; i < n; ++i)
    {
        is >> s;
        N.add_vertex(s);
    }

    for (std::size_t i = 0; i < m; ++i)
    {
        is >> s >> d >> w;
        N.add_edge(s, d, w);
    }
    return is;

}

#endif // NETWORK_H
