#ifndef WEDGE_H
#define WEDGE_H

#include <utility>


// specialize hash to provide a hash function for Edge (pair of strings)

struct WEdge
{
    std::string s, d;
    double w;

    WEdge(const std::string & s = "", const std::string & d = "", double w = 0.0) : s(s), d(d), w(w)
    {}

};

bool operator ==(const WEdge & e1, const WEdge & e2)
{
    return (e1.s == e2.s && e1.d == e2.d && e1.w == e2.w);
}

bool operator < (const WEdge & e1, const WEdge & e2)
{
    return ((e1.w < e2.w) ||
            (e1.w == e2.w && e1.s < e2.s) ||
            (e1.w == e2.w && e1.s == e2.s && e1.d < e2.d));
}

std::ostream & operator << (std::ostream & os, const WEdge & e)
{
    os << "(" << e.s << ", " << e.d << ", " << e.w << ") ";
    return os;
}

namespace std
{
    template <>
    class hash<std::pair<std::string, std::string>>
    {
    public:

        std::size_t operator() (const std::pair<std::string, std::string> & p) const
        {
            return std::hash<std::string> () (p.first) ^
                    std::hash<std::string> () (p.second);
        }
    };

    template <>
    class hash<WEdge>
    {
    public:
        std::size_t operator() (const WEdge & e) const
        {
            return std::hash<std::string> () (e.s) ^
                    std::hash<std::string> () (e.d) ^
                    std::hash<double> () (e.w);

        }
    };
}

#endif
