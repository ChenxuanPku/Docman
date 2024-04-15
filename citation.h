#pragma once
#ifndef CITATION_H
#define CITATION_H

#include <string>

class Citation {
private:


public: 
std::string Title; 
virtual std::string getType() 
  {
     return "citation";
  } 
};
class Book: Citation{
private:
std::string Author;
std::string Publisher;
std::string Year;
public:
std::string getType() 
  {
     return "book";
  } 
};
class Article:public Citation{
private:
std::string Author;
std::string Year;
std::string Journal;
std::string Volume;
std::string Issue;
public:
std::string getType() 
  {
     return "article";
  } 
};
class Webpage:public Citation{
private:
std::string Url;
public:
std::string getType() 
  {
     return "webpage";
  } 
};
#endif