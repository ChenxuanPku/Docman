#pragma once
#ifndef CITATION_H
#define CITATION_H

#include <string>
#include <nlohmann/json.hpp>
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
class Book:public Citation{
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
  Book (nlohmann::json&item)
  {

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
  Article (nlohmann::json&item)
  {
    
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
  Webpage (nlohmann::json&item)
  {
    
  }
};
int TypeID(std::string s)
{
  if(s=="article")return 1;
  if(s=="book") return 2;
  if(s=="webpage") return 3;
  return 0;
}
Citation* CitationConstruct(nlohmann::json& item )
{  
  
  switch(TypeID(item["type"].get<std::string>())){
    case 1: {
      return new Article(item);
    }
    case 2:{
      return new Book(item);
    }
    case 3:{
      return new Webpage(item);
    }
    default:{
      return new Citation;
    }
  }
}
#endif