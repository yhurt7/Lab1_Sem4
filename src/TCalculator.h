#ifndef __TCalculator_H__
#define __TCalculator_H__

#include <iostream>
#include <vector>
#include <map>
#include "IMap.h"

using namespace std;

class TFormula {
private:
  string infix;
  string postfix;
  vector<string> lexems;
  map<string, int> priority;
  vector<string> operands;

  void Parse();
  void ToPostfix();
public:
  TFormula(string _infix);

  string GetInfix() const { return infix; }
  string GetPostfix() const;
  vector<string> GetOperands() const { return operands; };
};

template<class Key, class Data>
class TCalculator
{
private:
  IMap<Key,Data>** mapVariants;
  int mapMode;
  TFormula currFormula;
};

#endif
