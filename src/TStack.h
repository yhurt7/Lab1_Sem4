#pragma once

#ifndef __TStack_H__
#define __TStack_H__

const int MAX_MEM_SIZE = 25; // Максимальный размер памяти для стека

template <class T>
class TStack {
protected:
  T* pMem; // Указатель на массив элементов
  int size; // Размер памяти для СД
  int dataCount; // Количество элементов в СД
  int top; // Индекс вершины стека
public:
  TStack(int _size = MAX_MEM_SIZE); // Конструктор
  ~TStack(); // Деструктор

  int IsEmpty() const { return (dataCount == 0); } // Проверка пустоты
  int IsFull() const { return (dataCount == size); } // Проверка переполнения

  void Push(const T& val); // Добавить значение
  virtual T Pop(void); // Извлечь значение
};

template <class T>
TStack<T>::TStack(int _size)
{
  if (_size <= 0) { size = MAX_MEM_SIZE; }
  else { size = _size; }
  dataCount = 0;
  top = -1;
  pMem = new T[size];
}

template <class T>
TStack<T>::~TStack()
{
  size = 0;
  dataCount = 0;
  top = 0;
  if (pMem != nullptr) { delete[] pMem; }
  pMem = nullptr;
}

template <class T>
void TStack<T>::Push(const T& val)
{
  if (IsFull()) { throw "Cannot insert more elements in stack"; }
  pMem[++top] = val;
  dataCount++;
}

template <class T>
T TStack<T>::Pop(void)
{
  if (IsEmpty()) { throw "No elements left in stack"; }
  dataCount--;
  return pMem[top--];
}

#endif
