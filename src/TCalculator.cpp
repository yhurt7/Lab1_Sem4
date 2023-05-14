#include "TCalculator.h"
#include "TStack.h"

void TFormula::Parse()
{
  int i = 0;
  string temp;
  while (i < infix.length())
  {
    switch (infix[i])
    {
    case '@': case '#': case '&': case '$': case '!': case '%': case '|': case '~': case '?': case '>': case '<': case ':': case ';':
      throw "Unknown symbol in expression";
      break;
    case '+': 
      lexems.push_back("+");
      break;
    case '-':
      lexems.push_back("-");
      break;
    case '*':
      lexems.push_back("*");
      break;
    case '=':
      lexems.push_back("=");
      break;
    default:
      if (isalpha(infix[i]) || isdigit(infix[i]) || infix[i] == '_')
      {
        temp.push_back(infix[i]);
        i++;
        while ((isalpha(infix[i]) || isdigit(infix[i]) || infix[i] == '_') && (i < infix.length()))
        {
          temp.push_back(infix[i]);
          i++;
        }
        i--;
        lexems.push_back(temp);
        temp.clear();
      }
    }
    i++;
  }
}

void TFormula::ToPostfix()
{
  Parse();
  TStack<string> st;
  string stackItem;
  for (string item : lexems)
  {
    if (item == "(")
    {
      st.Push(item);
    }
    else if (item == ")")
    {
      stackItem = st.Pop();
      while (stackItem != "(")
      {
        postfix += stackItem;
        stackItem = st.Pop();
      }
    }
    else if (item == "+" || item == "-" || item == "*" || item == "=")
    {
      while (!st.IsEmpty())
      {
        stackItem = st.Pop();
        if (priority[item] <= priority[stackItem]) { postfix += stackItem; }
        else {
          st.Push(stackItem);
          break;
        }
      }
      st.Push(item);
    }
    else{
      operands.push_back(item);
      postfix += item;
    }
  }
  while (!st.IsEmpty())
  {
    stackItem = st.Pop();
    postfix += stackItem;
  }
}

TFormula::TFormula(string _infix) : infix(_infix)
{
  priority = { {"=", 1}, {"+", 2}, {"-", 2}, {"*", 3}};
  ToPostfix();
}

string TFormula::GetPostfix() const
{
  return postfix;
}