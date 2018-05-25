#ifndef DS_H
#define DS_H

#include <cassert>

template <class T>
class ds
{
public:
    struct node
    {
        T value;
        std::size_t rank;
        node * parent;

        node (const T & x)
        {
            value =x;
            rank = 0;
            parent = this;
        }

    };



    ds()
    {

    }

    ~ds()
    {
        for (auto e: _data)
            delete e.second;
    }

    void make_set(const T & x)
    {
        assert(_data.count(x) == 0);
        _data[x] = new node(x);
    }

    node * find(const T & x)
    {
        assert(_data.count(x) == 1);

        if (_data[x]->parent == _data[x])
            return _data[x];

        return (_data[x]->parent = find(_data[x]->parent->value));


    }



    void join(const T & a, const T & b)
    {
        assert(_data.count(a) == 1 && _data.count(b) == 1);

        node * r1(find(a)), *r2(find(b));

        if (r1->rank == r2->rank)
        {
            r2->parent =r1;
            r1->rank++;

        }

        else if (r1->rank > r2->rank)
            r2->parent = r1;
        else
            r1->parent = r2;


    }
private:
    std::unordered_map<T, node *> _data;
};

#endif // DS_H
