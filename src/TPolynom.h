#include "TMonom.h"
#ifndef __TPolynom_H__
#define __TPolynom_H__

class TPolynom
{
struct PMonom
{
  TMonom mon;
  PMonom* next;
  PMonom(double coeff = 0, double powx = 0, double powy = 0, double powz = 0, PMonom* p = nullptr)
  {
    mon = TMonom(coeff, powx, powy, powz);
    next = p;
  }
  PMonom(const TMonom& p, PMonom* np = nullptr)
  {
    mon = TMonom(p);
    next = np;
  }
  PMonom(const PMonom& p)
  {
    mon = TMonom(p.mon);
    next = nullptr;
  }
};
protected:
  PMonom* begin;
  PMonom* end;
public:
  TPolynom();
  TPolynom(const TPolynom& p);
  ~TPolynom();

  double Calculate(const double x, const double y, const double z);

  void Add(TMonom& p);

  TPolynom& operator=(const TPolynom& p);
  TPolynom& operator+=(const TPolynom& p);
  TPolynom& operator-=(const TPolynom& p);
  TPolynom& operator*=(const double num);
  TPolynom& operator*(const double num);
  TPolynom& operator*=(const TPolynom& p);
  TPolynom& operator*(const TPolynom& p);
};

#endif