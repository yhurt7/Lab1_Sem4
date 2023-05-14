#include "IMap.h"
#ifndef __THMap_H__
#define __THMap_H__

template <class Key, class Data>
class THMap: public IMap<Key, Data>
{
struct TItem
{
  Key key;
  Data data;
};
protected:
  TItem* data;
  int size;
  int count;
  int HashFunc(const Key& key);
  int HashFuncRepeat(const Key& key);
public:
  THMap(int _size = 100);
  ~THMap();
  Data GetValue(const Key& key);
  void Add(const Key& key, const Data& value);
  void Del(const Key& key);
};

template<class Key, class Data>
inline int THMap<Key, Data>::HashFunc(const Key& key)
{
  return key % size;
}

template<class Key, class Data>
inline int THMap<Key, Data>::HashFuncRepeat(const Key& key)
{
  int delta = 1;
  return (HashFunc(key) + delta) % size;
}

template<class Key, class Data>
inline THMap<Key, Data>::THMap(int _size)
{
  if (_size <= 0) { throw "Incorrect size"; }
  size = _size;
  count = 0;
  data = new TItem[size];
  for (int i = 0; i < size; i++)
  {
    data[i].key = 0;
    data[i].data = 0;
  }
}

template<class Key, class Data>
inline THMap<Key, Data>::~THMap()
{
  if (data != nullptr) delete[] data;
  data = nullptr;
  size = 0;
  count = 0;
}

template<class Key, class Data>
inline Data THMap<Key, Data>::GetValue(const Key& key)
{
  int num = HashFunc(key);
  if (data[num].key == key) { return data[num].data; }
  else {
    num = HashFuncRepeat(key);
    while (data[num].key != key)
    {
      num++;
      if (num >= size) { throw "OOR"; }
    }
    return data[num].data;
  }
}

template<class Key, class Data>
inline void THMap<Key, Data>::Add(const Key& key, const Data& value)
{
  int num = HashFunc(key);
  if (data[num].key == 0) {
    data[num].key = key;
    data[num].data = value;
  }
  else {
    int num = HashFuncRepeat(key);
    while (data[num].key != 0)
    {
      num++;
      if (num >= size) { throw "OOR"; }
    }
    data[num].key = key;
    data[num].data = value;
  }
}

template<class Key, class Data>
inline void THMap<Key, Data>::Del(const Key& key)
{
  int num = HashFunc(key);
  if (data[num].key == key)
  {
    data[num].key = 0;
    data[num].data = 0;
  }
  else {
    num = HashFuncRepeat(key);
    while (data[num].key != key)
    {
      num++;
      if (num >= size) { throw "OOR"; }
    }
    data[num].key = 0;
    data[num].data = 0;
  }
}

#endif
