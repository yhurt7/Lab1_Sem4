#include "IMap.h"
#ifndef __TRBTreeMap_H__
#define __TRBTreeMap_H__

template <class Key, class Data>
class TRBTreeMap : public IMap<Key, Data>
{
struct TItem
{
  Key key;
  Data data;
};
struct TNode
{
  TItem data;
  bool blackColor;
  TNode* pParent;
  TNode* pLeft;
  TNode* pRight;
};
protected:
  TNode* pRoot;
  TNode* TNULL;
  void Rotate_L(TNode* p);
  void Rotate_R(TNode* p);
  void Fix_Add(TNode* p);
  void Fix_Del(TNode* p);
  void Transplant(TNode* p1, TNode p2);
public:
  TRBTreeMap();
  TRBTreeMap(const Key k, const Data d);
  ~TRBTreeMap();
  Key GetRootKey();
  Key GetLChildKey(const Key& key);
  Key GetRChildKey(const Key& key);
  Data GetValue(const Key& key);
  void Add(const Key& key, const Data& value);
  void Del(const Key& k);
};

template<class Key, class Data>
inline void TRBTreeMap<Key, Data>::Rotate_L(TNode* p) {
  TNode* t = p->pRight;
  p->pRight = t->pLeft;
  if (t->pLeft != TNULL) {
	t->pLeft->pParent = p;
  }
  t->pParent = p->pParent;
  if (p->pParent == nullptr) {
	pRoot = t;
  }
  else if (p == p->pParent->pLeft) {
	p->pParent->pLeft = t;
  }
  else {
	p->pParent->pRight = t;
  }
  t->pLeft = p;
  p->pParent = t;
}

template<class Key, class Data>
inline void TRBTreeMap<Key, Data>::Rotate_R(TNode* p) {
  TNode* t = p->pLeft;
  p->pLeft = t->pRight;
  if (t->pRight != TNULL) {
	t->pRight->pParent = p;
  }
  t->pParent = p->pParent;
  if (p->pParent == nullptr) {
	pRoot = t;
  }
  else if (p == p->pParent->pRight) {
	p->pParent->pRight = t;
  }
  else {
	p->pParent->pLeft = t;
  }
  t->pRight = p;
  p->pParent = t;
}

template<class Key, class Data>
inline void TRBTreeMap<Key, Data>::Fix_Add(TNode* p)
{
  TNode* t;
  while (p->pParent->blackColor == false) {
	if (p->pParent == p->pParent->pParent->pRight) {
	  t = p->pParent->pParent->pLeft;
	  if (t->blackColor == false) {
		t->blackColor = true;
		p->pParent->blackColor = true;
		p->pParent->pParent->blackColor = false;
		p = p->pParent->pParent;
	  }
	  else {
		if (p == p->pParent->pLeft) {
		  p = p->pParent;
		  Rotate_R(p);
		}
		p->pParent->blackColor = true;
		p->pParent->pParent->blackColor = false;
		Rotate_L(p->pParent->pParent);
	  }
	}
	else {
	  t = p->pParent->pParent->pRight;
	  if (t->blackColor == false) {
		t->blackColor = true;
		p->pParent->blackColor = true;
		p->pParent->pParent->blackColor = false;
		p = p->pParent->pParent;
	  }
	  else {
		if (p == p->pParent->pRight) {
		  p = p->pParent;
		  Rotate_L(p);
		}
		p->pParent->blackColor = true;
		p->pParent->pParent->blackColor = false;
		Rotate_R(p->pParent->pParent);
	  }
	}
	if (p == pRoot) {
	  break;
	}
  }
  pRoot->blackColor = true;
}

template<class Key, class Data>
inline void TRBTreeMap<Key, Data>::Fix_Del(TNode* p)
{
  TNode* t;
  while (p != pRoot && p->blackColor == true) {
	if (p == p->pParent->pLeft) {
	  t = p->pParent->pRight;
	  if (t->blackColor == false) {
		t->blackColor = true;
		t->pParent->blackColor = false;
		Rotate_L(p->pParent);
		t = p->pParent->pRight;
	  }
	  if (t->pLeft->blackColor == true && t->pRight->blackColor == true) {
		t->blackColor = false;
		p = p->pParent;
	  }
	  else {
		if (t->pRight->blackColor == true) {
		  t->pLeft->blackColor = true;
		  t->blackColor = false;
		  Rotate_R(t);
		  t = p->pParent->pRight;
		}
		t->blackColor = p->pParent->blackColor;
		p->pParent->blackColor = true;
		t->pRight->blackColor = true;
		Rotate_R(p->pParent);
		p = pRoot;
	  }
	}
	else {
	  t = p->pParent->pLeft;
	  if (t->blackColor == false) {
		t->blackColor = true;
		p->pParent->blackColor = false;
		Rotate_R(p->pParent);
		t = p->pParent->pLeft;
	  }
	  if (t->pRight->blackColor == true && t->pRight->blackColor == true) {
		t->blackColor = false;
		p = p->pParent;
	  }
	  else {
		if (t->pLeft->blackColor == true) {
		  t->pRight->blackColor = true;
		  t->blackColor = false;
		  Rotate_L(t);
		  t = p->pParent->pLeft;
		}
		t->blackColor = p->pParent->blackColor;
		p->pParent->blackColor = true;
		t->pLeft->blackColor = true;
		Rotate_R(p->pParent);
		p = pRoot;
	  }
	}
  }
  p->blackColor = true;
}

template<class Key, class Data>
inline void TRBTreeMap<Key, Data>::Transplant(TNode* p1, TNode p2)
{
  if (p1->pParent == nullptr) {
	pRoot = p2;
  }
  else if (p1 == p1->pParent->pLeft) {
	p1->pParent->pLeft = p2;
  }
  else {
	p1->pParent->pRight = p2;
  }
  p2->pParent = p1->pParent;
}

template<class Key, class Data>
inline TRBTreeMap<Key, Data>::TRBTreeMap()
{
  TNULL = new TNode;
  TNULL->data = NULL;
  TNULL->blackColor = true;
  TNULL->pLeft = nullptr;
  TNULL->pRight = nullptr;
  TNULL->pParent = nullptr;
  pRoot = TNULL;
}

template<class Key, class Data>
inline TRBTreeMap<Key, Data>::TRBTreeMap(const Key k, const Data d)
{
  pRoot = new TNode;
  pRoot->data.key = k;
  pRoot->data.data = d;
  pRoot->blackColor = true;
  pRoot->pParent = nullptr;
  pRoot->pLeft = TNULL;
  pRoot->pRight = TNULL;
}

template<class Key, class Data>
inline TRBTreeMap<Key, Data>::~TRBTreeMap()
{
  if (pRoot != nullptr) { delete pRoot; }
  pRoot = nullptr;
  if (TNULL != nullptr) { delete TNULL; }
  TNULL = nullptr;
}

template<class Key, class Data>
inline Key TRBTreeMap<Key, Data>::GetRootKey()
{
  if (pRoot != nullptr && pRoot != TNULL) { return pRoot->data.key; }
  else { throw "OOR"; }
}

template<class Key, class Data>
inline Key TRBTreeMap<Key, Data>::GetLChildKey(const Key& key)
{
  TNode* curr = pRoot;

  while (curr != TNULL && curr != nullptr) {
	if (curr->data.key == key) { return curr->pLeft->data.key; }
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
inline Key TRBTreeMap<Key, Data>::GetRChildKey(const Key& key)
{
  TNode* curr = pRoot;

  while (curr != TNULL && curr != nullptr) {
	if (curr->data.key == key) { return curr->pRight->data.key; }
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
inline Data TRBTreeMap<Key, Data>::GetValue(const Key& key)
{
  TNode* curr = pRoot;

  while (curr != TNULL && curr != nullptr) {
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
inline void TRBTreeMap<Key, Data>::Add(const Key& key, const Data& value)
{
  TNode* node = new TNode;
  node->data.key = key;
  node->data.data = value;
  node->pLeft = TNULL;
  node->pRight = TNULL;
  node->pParent = nullptr;
  node->blackColor = false;

  TNode* y = nullptr;
  TNode* x = pRoot;

  while (x != TNULL) {
	y = x;
	if (node->data.key < x->data.key) {
	  x = x->pLeft;
	}
	else {
	  x = x->pRight;
	}
  }

  node->pParent = y;
  if (y == nullptr) {
	pRoot = node;
  }
  else if (node->data.key < y->data.key) {
	y->pLeft = node;
  }
  else {
	y->pRight = node;
  }

  if (node->pParent == nullptr) {
	node->blackColor = true;
	return;
  }

  if (node->pParent->pParent == nullptr) {
	return;
  }

  Fix_Add(node);
}

template<class Key, class Data>
inline void TRBTreeMap<Key, Data>::Del(const Key& k)
{
  TNode* z = TNULL;
  TNode* x, y;
  TNode* temp = pRoot;
  while (temp != TNULL) {
	if (temp->data.key == k) {
	  z = temp;
	}
	if (temp->data.key < k) {
	  temp = temp->pRight;
	}
	else {
	  temp = temp->pLeft;
	}
  }
  if (z == TNULL) { throw "OOR"; }
  y = z;
  bool t = y->blackColor;
  if (z->pLeft == TNULL) {
	x = z->pRight;
	Transplant(z, z->pRight);
  }
  else if (z->pRight == TNULL) {
	x = z->pLeft;
	Transplant(z, z->pLeft);
  }
  else {
	y = minim(z->pRight);
	t = y->blackColor;
	x = y->pRight;
	if (y->pParent == z) {
	  x->pParent = y;
	}
	else {
	  Transplant(y, y->pRight);
	  y->pRight = z->pRight;
	  y->pRight->pParent = y;
	}
	Transplant(z, y);
	y->pLeft = z->pLeft;
	y->pLeft->pParent = y;
	y->blackColor = z->blackColor;
  }
  delete z;
  if (t == true) { Fix_Del(x); }
}

#endif