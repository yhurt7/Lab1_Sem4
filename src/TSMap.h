#include "IMap.h"
#include <iostream>
#ifndef __TSMap_H__
#define __TSMap_H__

template<class Key, class Data>
class TSMap : public IMap<Key, Data>
{
struct TItem
{
  Key key;
  Data data;
};
protected:
  TItem* items;
  int size;
  int count;
  int FindID(const Key& key);
public:
  TSMap(int _size = 100);
  TSMap(const TSMap<Key, Data>& p);
  ~TSMap();
  int GetSize();
  int GetCount();
  Data GetValue(const Key& key);
  void Add(const Key& key, const Data& value);
  void Del(const Key& key);

  template<class T>
  friend std::ostream& operator<<(std::ostream& ostr, const TSMap<Key, Data>& _map);
};

template<class Key, class Data>
inline int TSMap<Key, Data>::FindID(const Key& key)
{
  int start = 0;
  int index = count / 2;
  int end = count - 1;
  while (start <= end)
  {
	if (items[index].key == key)
	{
	  return index;
	}
	if (key > items[index].key)
	{
	  start = index;
	  index = (start + end) / 2;
	}
	if (key < items[index].key)
	{
	  end = index;
	  index = (end - start) / 2;
	}
	if (start == end)
	{
	  return -1;
	}
  }
}

template<class Key, class Data>
inline TSMap<Key, Data>::TSMap(int _size)
{
  if (_size <= 0) { throw "Invalid size"; }

  size = _size;
  count = 0;
  items = new TItem[size];

  for (int i = 0; i < size; i++)
  {
	items[i].key = NULL;
	items[i].data = NULL;
  }
}

template<class Key, class Data>
inline TSMap<Key, Data>::TSMap(const TSMap<Key, Data>& p)
{
  size = p.size;
  count = p.count;
  items = new TItem[p.size];
  for (int i = 0; i < count; i++)
  {
	items[i].key = p.items[i].key;
	items[i].data = p.items[i].data;
  }
}

template<class Key, class Data>
inline TSMap<Key, Data>::~TSMap()
{
  if (items != nullptr) { delete[] items; }
  items = nullptr;
  size = NULL;
  count = NULL;
}

template<class Key, class Data>
int TSMap<Key, Data>::GetSize()
{
  return size;
}

template<class Key, class Data>
int TSMap<Key, Data>::GetCount()
{
  return count;
}

template<class Key, class Data>
inline Data TSMap<Key, Data>::GetValue(const Key& key)
{
  if (FindID(key) >= 0) { return items[FindID(key)].data; }
  else { throw "Key not found"; }
}

template<class Key, class Data>
inline void TSMap<Key, Data>::Add(const Key& key, const Data& value)
{
  int tmp = count;
  if (count + 1 > size) { throw "OOR"; }
  for (int i = 0; i < count; i++) { if (items[i].key == key) { throw "Such key already exists"; } }
  if (count == 0)
  {
	items[count].key = key;
	items[count].data = value;
	count++;
  }
  else
  {
	for (int i = 0; i < count; i++)
	{
	  if (items[i].key > key)
	  {
		tmp = i;
		break;
	  }
	}
	for (int i = tmp + 1; i < count + 1; i++)
	{
	  items[i].key = items[i - 1].key;
	  items[i].data = items[i - 1].data;
	}
	items[tmp].key = key;
	items[tmp].data = value;
	count++;
  }
}

template<class Key, class Data>
inline void TSMap<Key, Data>::Del(const Key& key)
{
  int index = FindID(key);
  if (index >= 0)
  {
	for (int i = index; i < count - 1; i++)
	{
	  items[i].key = items[i + 1].key;
	  items[i].data = items[i + 1].data;
	}
	count--;
  }
  else { throw "OOR"; }
}

template<class Key, class Data>
std::ostream& operator<<(std::ostream& ostr, const TSMap<Key, Data>& _map)
{
  ostr << "Size: " << _map.size;
  ostr << "Count: " << _map.count;
  ostr << "Key   |   Item";
  for (int i = 0; i < _map.count; i++) { ostr << _map.items[i].key << "   |   " << _map.items[i].data; }
  return ostr;
}

#endif