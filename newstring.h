#pragma once
#ifndef NEWSTRING_H
#define NEWSTRING_H
#include <iostream>
#include<string>
#include<vector>


class String{
private:
  std::vector<std::string> str{};
public:
  std::ostream& operator<<(std::ostream& os)
  {
    for (std::string s:str)
      os<<s;
    os<<std::endl;
    return os;
  }
  void Push_Back(const std::string s)
  {
    str.push_back(s);
  }
};

#endif