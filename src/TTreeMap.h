#include "IMap.h"
#ifndef __TTreeMap_H__
#define __TTreeMap_H__

template <class Key, class Data>
class TTreeMap : public IMap<Key, Data>
{
struct TItem
{
  Key key;
  Data data;
};
struct TNode
{
  TItem data;
  TNode* pLeft;
  TNode* pRight;
};
protected:
  TNode* pRoot;
public:
  TTreeMap();
  TTreeMap(const Key k, const Data d);
  ~TTreeMap();
  Key GetRootKey();
  Key GetLChildKey(const Key& key);
  Key GetRChildKey(const Key& key);
  Data GetValue(const Key& key);
  void Add(const Key& key, const Data& value);
  void Del(const Key& key);
};

template<class Key, class Data>
inline TTreeMap<Key, Data>::TTreeMap()
{
  pRoot = new TNode;
  pRoot->data = 0;
  pRoot->pLeft = nullptr;
  pRoot->pRight = nullptr;
}

template<class Key, class Data>
inline TTreeMap<Key, Data>::TTreeMap(const Key k, const Data d)
{
  pRoot = new TNode;
  pRoot->data.key = k;
  pRoot->data.data = d;
  pRoot->pLeft = nullptr;
  pRoot->pRight = nullptr;
}

template<class Key, class Data>
inline TTreeMap<Key, Data>::~TTreeMap()
{
  if (pRoot != nullptr) { delete pRoot; }
  pRoot = nullptr;
}

template<class Key, class Data>
inline Key TTreeMap<Key, Data>::GetRootKey()
{
  if (pRoot != nullptr) { return pRoot->data.key; }
  else { throw "OOR"; }
}

template<class Key, class Data>
inline Key TTreeMap<Key, Data>::GetLChildKey(const Key& key)
{
  TNode* curr = pRoot;

  while (curr != nullptr) {
	if (curr->data.key == key) {
	  if (curr->pLeft == nullptr) { return 0; }
	  else { return curr->pLeft->data.key; }
	}
	else {
	  if (key < curr->data.key) {
		curr = curr->pLeft;
	  }
	  else {
		curr = curr->pRight;  
	  }
	}
  }

  throw "Key not found";
}

template<class Key, class Data>
inline Key TTreeMap<Key, Data>::GetRChildKey(const Key& key)
{
  TNode* curr = pRoot;

  while (curr != nullptr) {
	if (curr->data.key == key) {
	  if (curr->pRight == nullptr) { return 0; }
	  else { return curr->pRight->data.key; }
	}
	else {
	  if (key < curr->data.key) {
		curr = curr->pLeft;
	  }
	  else {
		curr = curr->pRight;
	  }
	}
  }

  throw "Key not found";
}

template<class Key, class Data>
inline Data TTreeMap<Key, Data>::GetValue(const Key& key)
{
  TNode* curr = pRoot;

  while (curr != nullptr) {
	if (curr->data.key == key) { return curr->data.data; }
	else {
	  if (key < curr->data.key) {
		curr = curr->pLeft;
	  }
	  else {
		curr = curr->pRight;
	  }
	}
  }

  throw "Key not found";
}

template<class Key, class Data>
inline void TTreeMap<Key, Data>::Add(const Key& key, const Data& value)
{
  TNode* node = new TNode;
  node->data.key = key;
  node->data.data = value;
  node->pLeft = nullptr;
  node->pRight = nullptr;

  TNode* y = nullptr;
  TNode* x = pRoot;

  while (x != nullptr) {
	if (x->data.key == key) { throw "Invalid key"; }
	y = x;
	if (key < x->data.key) {
	  x = x->pLeft;
	}
	else {
	  x = x->pRight;
	}
  }

  if (y == nullptr) {
	pRoot = node;
  }
  else if (key < y->data.key) {
	y->pLeft = node;
  }
  else {
	y->pRight = node;
  }
}

template<class Key, class Data>
inline void TTreeMap<Key, Data>::Del(const Key& key)
{
  TNode* y = nullptr;
  TNode* x = pRoot;

  while (x != nullptr) {
	if (x->data.key == key) { break; }
	y = x;
	if (key < x->data.key) {
	  x = x->pLeft;
	}
	else {
	  x = x->pRight;
	}
  }

  if (x == nullptr) { throw "OOR"; }
  else if (y == nullptr)
  {
	TNode* currLC = x->pLeft;
	TNode* currRC = x->pRight;
	if (currLC == nullptr) { pRoot = currRC; }
	else if (currRC == nullptr) { pRoot = currLC; }
	else
	{
	  TNode* temp = currRC->pLeft;
	  currRC->pLeft = currLC;
	  pRoot = currRC;
	  Add(temp->data.key, temp->data.data);
	}
  }	
  else
  {
	TNode* currLC = x->pLeft;
	TNode* currRC = x->pRight;
	if (x->data.key < y->data.key) {
	  y->pLeft = nullptr;
	}
	else {
	  y->pRight = nullptr;
	}
	if (currLC != nullptr) { Add(currLC->data.key, currLC->data.data); }
	if (currRC != nullptr) { Add(currRC->data.key, currRC->data.data); }
  }
}

#endif
