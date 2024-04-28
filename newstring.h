#pragma once
#ifndef NEWSTRING_H
#define NEWSTRING_H
#include <iostream>
#include<string>
#include<vector>
#include <bitset>

class String{
//利用多个std::string储存文本内容
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
  //检查文本的合规性,同时整理所有的id
  //始终保持对中括号符号差的统计
  std::vector<std::string> Return{};
  for(std::string Para:s.str)
  {
  std::string currentNumber;
    int count = 0;
    for (char c:Para)
    {
      if (c == '[') {
            count++; 
        } else if (c == ']') {
            count--;
            if (currentNumber.length()>0) {
                if(std::find(Return.begin(),Return.end(),currentNumber)==Return.end())
                Return.push_back(currentNumber);
                currentNumber.clear();
            }else std::exit(1);
        } else if(count!=0)
          { 
            if(count==1){
                currentNumber+=c;
            }
            else std::exit(1);
    }
  }
    if(count!=0)std::exit(1);
   std::sort(Return.begin(),Return.end());
   }return Return;
}
#endif