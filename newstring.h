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
  friend std::ostream& operator<<(std::ostream& os,String Str)
  {
    for (std::string s:Str.str)
      os<<s;
    os<<std::endl;
    return os;
  }
  void Push_Back(const std::string s)
  {
    str.push_back(s);
  }
  friend std::vector<std::string> CheckLegal(String& s);
};
std::vector<std::string> CheckLegal(String& s)
{
  std::vector<std::string> Return{};
  for(std::string Para:s.str)
  {
    auto Ptr=0;
    while(Ptr!=Para.length())
    {
      auto TmpPtr=Para.find('[',Ptr);
      Ptr=TmpPtr;
      do{ TmpPtr++;
      if (Para[TmpPtr]<'0'&&Para[TmpPtr]>'9') break;}
      while(Para[TmpPtr]!=']'&& TmpPtr!=Para.length());
      if (Para[TmpPtr]==']')
      {
        Return.push_back( Para.substr(Ptr+1,TmpPtr-Ptr));
        Ptr=TmpPtr+1;
      }
      else std::exit(1);
    }
  }
  return Return;
}
#endif