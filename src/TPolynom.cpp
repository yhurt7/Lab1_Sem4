#include "TPolynom.h"

TPolynom::TPolynom()
{
  begin = new PMonom();
  end = nullptr;
  begin->next = end;
}

TPolynom::TPolynom(const TPolynom& p)
{
  begin = new PMonom(*(p.begin));
  if (p.end != nullptr) { end = new PMonom(*(p.end)); }
  else { end = nullptr; }
  PMonom* temp = p.begin->next;
  PMonom* curr = begin;
  while (temp != p.end && temp != nullptr)
  {
    curr->next = new PMonom(*(temp));
    curr = curr->next;
    temp = temp->next;
  }
  curr->next = end;
}

TPolynom::~TPolynom()
{
  PMonom* curr = begin;
  PMonom* next = begin->next;
  while (next != nullptr)
  {
    delete curr;
    curr = next;
    next = next->next;
  }
  delete curr;
}

double TPolynom::Calculate(const double x, const double y, const double z)
{
  double csum = 0.0;
  PMonom* curr = begin;
  PMonom* next = begin->next;
  while (next != nullptr)
  {
    csum += curr->mon.Calculate(x, y, z);
    curr = next;
    next = next->next;
  }
  csum += curr->mon.Calculate(x, y, z);
  return csum;
}

void TPolynom::Add(TMonom& p)
{
  double npowx = p.GetPowX();
  double npowy = p.GetPowY();
  double npowz = p.GetPowZ();
  PMonom* curr = begin;
  PMonom* next = begin->next;
  bool flag = true;
  while (next != nullptr)
  {
    if (curr->mon.GetPowX() == npowx && curr->mon.GetPowY() == npowy && curr->mon.GetPowZ() == npowz)
    {
      curr->mon += p;
      flag = false;
      break;
    }
    curr = next;
    next = next->next;
  }
  if (curr->mon.GetPowX() == npowx && curr->mon.GetPowY() == npowy && curr->mon.GetPowZ() == npowz)
  {
    curr->mon += p;
    flag = false;
  }
  if (flag) 
  {
    end->next = new PMonom(p);
    end = end->next;
  }
}

TPolynom& TPolynom::operator=(const TPolynom& p)
{
  begin = new PMonom(*(p.begin));
  if (p.end != nullptr) { end = new PMonom(*(p.end)); }
  else { end = nullptr; }
  PMonom* temp = p.begin->next;
  PMonom* curr = begin;
  while (temp != p.end && temp != nullptr)
  {
    curr->next = new PMonom(*(temp));
    curr = curr->next;
    temp = temp->next;
  }
  curr->next = end;
  return *this;
}

TPolynom& TPolynom::operator+=(const TPolynom& p)
{
  PMonom* curr = p.begin;
  PMonom* next = p.begin->next;
  while (next != nullptr)
  {
    Add(curr->mon);
    curr = next;
    next = next->next;
  }
  Add(curr->mon);
  return *this;
}

TPolynom& TPolynom::operator-=(const TPolynom& p)
{
  PMonom* curr = p.begin;
  PMonom* next = p.begin->next;
  while (next != nullptr)
  {
    Add(curr->mon * (-1));
    curr = next;
    next = next->next;
  }
  Add(curr->mon * (-1));
  return *this;
}

TPolynom& TPolynom::operator*=(const double num)
{
  PMonom* curr = begin;
  PMonom* next = begin->next;
  while (next != nullptr)
  {
    curr->mon *= num;
    curr = next;
    next = next->next;
  }
  curr->mon *= num;
  return *this;
}

TPolynom& TPolynom::operator*(const double num)
{
  TPolynom temp = TPolynom(*(this));
  temp *= num;
  return temp;
}

TPolynom& TPolynom::operator*=(const TPolynom& p)
{
  PMonom* curr1 = begin;
  PMonom* next1 = begin->next;
  while (next1 != nullptr)
  {
    PMonom* curr2 = p.begin;
    PMonom* next2 = p.begin->next;
    while (next2 != nullptr)
    {
      curr1->mon *= curr2->mon;
      curr2 = next2;
      next2 = next2->next;
    }
    curr1->mon *= curr2->mon;
    curr1 = next1;
    next1 = next1->next;
  }
  PMonom* curr2 = p.begin;
  PMonom* next2 = p.begin->next;
  while (next2 != nullptr)
  {
    curr1->mon *= curr2->mon;
    curr2 = next2;
    next2 = next2->next;
  }
  curr1->mon *= curr2->mon;
  return *this;
}

TPolynom& TPolynom::operator*(const TPolynom& p)
{
  TPolynom temp = TPolynom(*(this));
  temp *= p;
  return temp;
}
