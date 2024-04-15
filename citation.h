#pragma once
#ifndef CITATION_H
#define CITATION_H

#include <string>

class Citation {



public: 
  int id;
  std::string Title; 
  virtual std::string getType() 
  {
     return "citation";
  } 
  virtual void Print(std::ostream& output);
};
class Book: Citation{
private:
  std::string Author;
  std::string Publisher;
  std::string Year;
  std::string Type{"book"};
public:
  std::string getType() 
  {
     return "book";
  } 
  void Print(std::ostream& output)
  {
    output<<"["<<id<<"] "<<Type<<": "<<Author<<","<<Title<<","<<Publisher<<Year<<std::endl;
  }
};

class Article:public Citation{
private:
  std::string Author;
  std::string Year;
  std::string Journal;
  std::string Volume;
  std::string Issue;
  std::string Type{"artcile"};
public:
std::string getType() 
  {
     return "article";
  } 
    void Print(std::ostream& output)
  {
    output<<"["<<id<<"] "<<Type<<": "<<Author<<","<<Title<<","<<Journal<<","<<Year<<","<<","<<Volume<<","<<Issue<<std::endl;
  }
};
class Webpage:public Citation{
private:
std::string Url;
std::string Type{"webpage"};
public:
std::string getType() 
  {
     return "webpage";
  } 
   void Print(std::ostream& output)
  {
    output<<"["<<id<<"] "<<Type<<": "<<Title<<". Avaiable at"<<Url<<std::endl;
  } 
};
#endif