#include "TMonom.h"
#include <cmath>

TMonom::TMonom(double _coeff, double powax, double poway, double powaz)
{
  coeff = _coeff;
  powa = new double[3];
  powa[0] = powax;
  powa[1] = poway;
  powa[2] = powaz;
}

TMonom::TMonom(const TMonom& p)
{
  coeff = p.coeff;
  powa = new double[3];
  powa[0] = p.powa[0];
  powa[1] = p.powa[1];
  powa[2] = p.powa[2];
}

TMonom::~TMonom()
{
  if (powa != nullptr) { delete[] powa; }
  coeff = 0.0;
  powa = nullptr;
}

double TMonom::Calculate(const double x, const double y, const double z)
{
  return coeff * (pow(x, powa[0]) * pow(y, powa[1]) * pow(z, powa[2]));
}

TMonom& TMonom::operator=(const TMonom& p)
{
  coeff = p.coeff;
  powa = new double[3];
  powa[0] = p.powa[0];
  powa[1] = p.powa[1];
  powa[2] = p.powa[2];
  return *this;
}

TMonom& TMonom::operator+=(const TMonom& p)
{
  if (powa[0] == p.powa[0] && powa[1] == p.powa[1] && powa[2] == p.powa[2]) { coeff += p.coeff; }
  else { throw "Incorrect input"; }
  return *this;
}

TMonom& TMonom::operator-=(const TMonom& p)
{
  if (powa[0] == p.powa[0] && powa[1] == p.powa[1] && powa[2] == p.powa[2]) { coeff -= p.coeff; }
  else { throw "Incorrect input"; }
  return *this;
}

TMonom& TMonom::operator*=(const double num)
{
  coeff *= num;
  return *this;
}

TMonom& TMonom::operator*=(const TMonom& p)
{
  coeff *= p.coeff;
  powa[0] += p.powa[0];
  powa[1] += p.powa[1];
  powa[2] += p.powa[2];
  return *this;
}

TMonom& TMonom::operator+(const TMonom& p)
{
  if (powa[0] == p.powa[0] && powa[1] == p.powa[1] && powa[2] == p.powa[2])
  {
    TMonom temp(p);
    temp.coeff += coeff;
    return temp;
  }
  else { throw "Incorrect input"; }
}

TMonom& TMonom::operator-(const TMonom& p)
{
  if (powa[0] == p.powa[0] && powa[1] == p.powa[1] && powa[2] == p.powa[2])
  {
    TMonom temp(p);
    temp.coeff -= coeff;
    return temp;
  }
  else { throw "Incorrect input"; }
}

TMonom& TMonom::operator*(const double num)
{
  TMonom temp(*this);
  temp.coeff *= num;
  return temp;
}

TMonom& TMonom::operator*(const TMonom& p)
{
  TMonom temp(*this);
  temp *= p;
  return temp;
}

double TMonom::GetCoeff()
{
  return coeff;
}

double TMonom::GetPowX()
{
  return powa[0];
}

double TMonom::GetPowY()
{
  return powa[1];
}

double TMonom::GetPowZ()
{
  return powa[2];
}
