#ifndef __IMap__
#define __IMap__
template <typename Key, typename Data>
class IMap{
public:
    virtual Data GetValue(const Key& key) = 0;
    virtual void Add(const Key& key, const Data& value) = 0;
    virtual void Del(const Key& k) = 0;
};
#endif