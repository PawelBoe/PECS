//
// Created by Pawel Boening on 31.08.18.
//

#ifndef ECS_SMAP_H
#define ECS_SMAP_H


#include "sparse_set.h"

namespace pecs
{

    template <typename Key, typename Value, typename Hash>
    class sparse_map
    {
        template <typename K, typename V, typename H>
        struct PairHash
        {
            unsigned int operator()(std::pair<K, V> const& e) const
            {
                return _hash(e.first);
            }

            H _hash;
        };

    public:
        explicit sparse_map(unsigned int cap = 0);

        void resize(unsigned int new_cap);
        void add(Key k, Value v);
        void remove(Key k);
        unsigned int search(Key k) const;
        Value& at(Key k);
        const Value& at(Key k) const;
        void clear();

        unsigned int size() const;
        std::pair<Key, Value>* data();
        const std::pair<Key, Value>* data() const;

        using iterator = std::pair<Key, Value>*;
        iterator begin();
        const iterator begin() const;
        iterator end();
        const iterator end() const;

    private:
        sparse_set<std::pair<Key, Value>, PairHash<Key, Value, Hash>> _sset;
    };

    template<typename Key, typename Value, typename Hash>
    sparse_map<Key, Value, Hash>::sparse_map(unsigned int cap) : _sset(cap)
    {
    }

    template<typename Key, typename Value, typename Hash>
    void sparse_map<Key, Value, Hash>::resize(unsigned int new_cap)
    {
        return _sset.resize(new_cap);
    }

    template<typename Key, typename Value, typename Hash>
    void sparse_map<Key, Value, Hash>::add(Key k, Value v)
    {
        auto p = std::make_pair(k, v);
        return _sset.add(p);
    }

    template<typename Key, typename Value, typename Hash>
    void sparse_map<Key, Value, Hash>::remove(Key k)
    {
        Value v;
        auto p = std::make_pair(k, v);
        return _sset.remove(p);
    }

    template<typename Key, typename Value, typename Hash>
    unsigned int sparse_map<Key, Value, Hash>::search(Key k) const
    {
        Value v;
        auto p = std::make_pair(k, v);
        return _sset.search(p);
    }

    template<typename Key, typename Value, typename Hash>
    Value &sparse_map<Key, Value, Hash>::at(Key k)
    {
        auto idx = search(k);

        if (idx >= size())
            throw std::out_of_range("key not found in smap.");

        return _sset.data()[idx].second;
    }

    template<typename Key, typename Value, typename Hash>
    const Value &sparse_map<Key, Value, Hash>::at(Key k) const
    {
        auto idx = search(k);

        if (idx >= size())
            throw std::out_of_range("key not found in smap.");

        return _sset.data()[idx].second;
    }
    template<typename Key, typename Value, typename Hash>
    void sparse_map<Key, Value, Hash>::clear()
    {
        _sset.clear();
    }

    template<typename Key, typename Value, typename Hash>
    unsigned int sparse_map<Key, Value, Hash>::size() const
    {
        return _sset.size();
    }

    template<typename Key, typename Value, typename Hash>
    std::pair<Key, Value> *sparse_map<Key, Value, Hash>::data() // not allowed to change result of hash function
    {
        return _sset.data();
    }

    template<typename Key, typename Value, typename Hash>
    const std::pair<Key, Value> *sparse_map<Key, Value, Hash>::data() const // not allowed to change result of hash function
    {
        return _sset.data();
    }

    template<typename Key, typename Value, typename Hash>
    typename sparse_map<Key, Value, Hash>::iterator sparse_map<Key, Value, Hash>::begin()
    {
        return _sset.begin();
    }

    template<typename Key, typename Value, typename Hash>
    const typename sparse_map<Key, Value, Hash>::iterator sparse_map<Key, Value, Hash>::begin() const
    {
        return _sset.begin();
    }

    template<typename Key, typename Value, typename Hash>
    typename sparse_map<Key, Value, Hash>::iterator sparse_map<Key, Value, Hash>::end()
    {
        return _sset.end();
    }

    template<typename Key, typename Value, typename Hash>
    const typename sparse_map<Key, Value, Hash>::iterator sparse_map<Key, Value, Hash>::end() const
    {
        return _sset.end();
    }


}


#endif //ECS_SMAP_H
