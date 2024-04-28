#pragma once
#ifndef NEWSTRING_H
#define NEWSTRING_H
#include <iostream>
#include<string>
#include<vector>
#include <bitset>

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
  std::string currentNumber;
      int count = 0;
      int scount{0};
      int bcount{0};
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
    }else{
      if(c=='{')bcount++;
      if(c=='}')bcount--;
      if(c=='(')scount++;
      if(c==')')scount--;
    }
  }
    if(count!=0)std::exit(1);
   std::sort(Return.begin(),Return.end());
  
}return Return;}
#endif