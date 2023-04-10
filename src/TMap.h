#include "IMap.h"
#include <iostream>
#ifndef __TMap_H__
#define __TMap_H__

template <class Key, class Data>
class TMap : public IMap<Key, Data>
{
protected:
  int size;
  int count;
  Key* keys;
  Data* items;
  int FindID(Key k);
public:
  TMap(int _size = 100);
  TMap(const TMap<Key, Data>& p);
  ~TMap();
  int GetSize();
  int GetCount();
  Data GetValue(const Key& key);
  Data& operator[](Key k);
  void Add(const Key& key, const Data& value);
  void Del(const Key& k);

  template<class T>
  friend std::ostream& operator<<(std::ostream& ostr, const TMap<Key, Data>& _map);
};

template<class Key, class Data>
int TMap<Key, Data>::FindID(Key k)
{
  for (int i = 0; i < size; i++)
  {
    if (keys[i] != NULL)
    {
      if (keys[i] == k)
      {
        return i;
      }
    }
  }

  return -1;
}

template<class Key, class Data>
TMap<Key, Data>::TMap(int _size)
{
  if ( _size <= 0 ) { throw "Invalid size"; }

  size = _size;
  count = 0;
  keys = new Key[size];
  items = new Data[size];

  for (int i = 0; i < size; i++)
  {
    keys[i] = NULL;
    items[i] = NULL;
  }
}

template<class Key, class Data>
TMap<Key, Data>::TMap(const TMap<Key, Data>& p)
{
  size = p.size;
  count = p.count;
  keys = new Key[size];
  items = new Data[size];

  for (int i = 0; i < size; i++)
  {
    keys[i] = p.keys[i];
    items[i] = p.items[i];
  }
}

template<class Key, class Data>
TMap<Key, Data>::~TMap()
{
  size = 0;
  count = 0;
  if (keys != nullptr) { delete[] keys; }
  if (items != nullptr) { delete[] items; }
  keys = nullptr;
  items = nullptr;
}

template<class Key, class Data>
int TMap<Key, Data>::GetSize()
{
  return size;
}

template<class Key, class Data>
int TMap<Key, Data>::GetCount()
{
  return count;
}

template<class Key, class Data>
Data TMap<Key, Data>::GetValue(const Key& key)
{
  for (int i = 0; i < count; ++i)
  {
    if (keys[i] == key)
    {
      return items[i];
    }
  }

  throw "Key not found";
}

template<class Key, class Data>
Data& TMap<Key, Data>::operator[](Key k)
{
  for (int i = 0; i < size; i++)
  {
    if (keys[i] != NULL)
    {
      if (keys[i] == k)
      {
        return items[i];
      }
    }
  }
}

template<class Key, class Data>
void TMap<Key, Data>::Add(const Key& key, const Data& value)
{
  if (count >= size)
  {
    throw "OOR";
  }

  keys[count] = key;
  items[count] = value;
  count++;
}

template<class Key, class Data>
void TMap<Key, Data>::Del(const Key& k)
{
  if (count > 0)
  {
    int i = FindID(k);
    if (i != -1)
    {
      keys[i] = NULL;
      items[i] = NULL;
      for (; i < count - 1; i++)
      {
        keys[i] = keys[i + 1];
        items[i] = items[i + 1];
      }
      count--;
    }
  }
  else { throw "OOR"; }
}

template<class Key, class Data>
std::ostream& operator<<(std::ostream& ostr, const TMap<Key, Data>& _map)
{
  ostr << "Size: " << _map.size;
  ostr << "Count: " << _map.count;
  ostr << "Key   |   Item";
  for (int i = 0; i < _map.count; i++) { ostr << _map.keys[i] << "   |   " << _map.items[i]; }
  return ostr;
}

#endif