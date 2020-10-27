#ifndef MAP_H_
#define MAP_H_

#include <vector>
#include <utility>

using std::make_pair;
using std::pair;
using std::vector;

template <typename T, typename U>
class Map
{
private:
    vector<pair<T, U>> data;

public:
    bool empty();
    size_t size();
    void insert(const T &key, const U &value);
    void remove(const T &key);
    U& at(size_t index);
    U value(const T &key) const;
    vector<T> keys() const;
    bool contains(const T &key) const;
};

// Definitions

template <typename T, typename U>
bool Map<T, U>::empty()
{
    return data.empty();
}

template <typename T, typename U>
size_t Map<T, U>::size()
{
    return data.size();
}

template <typename T, typename U>
void Map<T, U>::insert(const T &key, const U &value)
{
    for (size_t i = 0; i < data.size(); i++)
    {
        if (data[i].first == key)
        {
            data[i].second = value;
            return;
        }
    }
    data.push_back(make_pair(key, value));
}

template <typename T, typename U>
void Map<T, U>::remove(const T &key)
{
    for (size_t i = 0; i < data.size(); i++)
    {
        if (data[i].first == key)
        {
            data.erase(data.begin() + i);
            return;
        }
    }
}

template <typename T, typename U>
U Map<T, U>::value(const T &key) const
{
    for (size_t i = 0; i < data.size(); i++)
    {
        if (data[i].first == key)
        {
            return data[i].second;
        }
    }
    U u;
    return u;
}

template <typename T, typename U>
vector<T> Map<T, U>::keys() const
{
    vector<T> keys;
    for (size_t i = 0; i < data.size(); i++)
    {
        keys.push_back(data[i].first);
    }
    return keys;
}

template <typename T, typename U>
U& Map<T, U>::at(size_t index) {
    if (index >= data.size() || index < 0) throw "Out of range";
    return data[index].second;
}

template <typename T, typename U>
bool Map<T, U>::contains(const T &key) const
{
    for (size_t i = 0; i < data.size(); i++)
    {
        if (data[i].first == key)
        {
            return true;
        }
    }
    return false;
}

#endif // MAP_H_
