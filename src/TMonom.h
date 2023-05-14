#ifndef __TMonom_H__
#define __TMonom_H__

class TMonom
{
protected:
  double coeff;
  double* powa;
public:
  TMonom(double _coeff = 0.0, double powx = 0.0, double powy = 0.0, double powz = 0.0);
  TMonom(const TMonom& p);
  ~TMonom();

  double Calculate(const double x, const double y, const double z);

  TMonom& operator=(const TMonom& p);
  TMonom& operator+=(const TMonom& p);
  TMonom& operator-=(const TMonom& p);
  TMonom& operator*=(const double num);
  TMonom& operator*=(const TMonom& p);
  TMonom& operator+(const TMonom& p);
  TMonom& operator-(const TMonom& p);
  TMonom& operator*(const double num);
  TMonom& operator*(const TMonom& p);

  double GetCoeff();
  double GetPowX();
  double GetPowY();
  double GetPowZ();
};

#endif