#pragma once
#ifndef CITATION_H
#define CITATION_H

#include <string>
#include <nlohmann/json.hpp>
#include<map>
#include <cpp-httplib/httplib.h>
#include "utils.hpp"
class Citation {
public: 
  std::string id;
  std::string Title; 
  virtual std::string getType() 
  {
     return "citation";
  } 
  virtual void Print(std::ostream& output);
  
};
class Book:public Citation{
private:
  std::string Author{};
  std::string Publisher{};
  std::string Year{};
  std::string Type{"book"};
  std::string Isbn{};
public:
  std::string getType() 
  {
     return "book";
  } 
  void Print(std::ostream& output)
  {
    output<<"["<<id<<"] "<<Type<<": "<<Author<<","<<Title<<","<<Publisher<<","<<Year<<std::endl;
  }
  Book (nlohmann::json&item)
  {
    if (item["id"].is_string()) id=item["id"].get<std::string>();
    if (item["isbn"].is_string()) Isbn=item["isbn"].get<std::string>();
    httplib::Client client{ "http://docman.lcpu.dev" };
    if (item["author"].is_string()) Author=item["author"].get<std::string>();
    else{auto response = client.Get("/author/" + encodeUriComponent(Isbn));
        Author=response->body;

    }
    if (item["title"].is_string()) Title=item["title"].get<std::string>();
    else{
        auto response = client.Get("/title/" + encodeUriComponent(Isbn));
        Title=response->body;
    }
    if (item["publisher"].is_string()) Publisher=item["publisher"].get<std::string>();
    else{
        auto response = client.Get("/publisher/" + encodeUriComponent(Isbn));
        Publisher=response->body;
    }
    if (item["year"].is_number()) Year=item["year"].get<int>();
    else{
      auto response = client.Get("/year/" + encodeUriComponent(Isbn));
      Year=response->body;
    }
    
  }
};

class Article:public Citation{
private:
  std::string Author{};
  std::string Year{};
  std::string Journal{};
  std::string Volume{};
  std::string Issue{};
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
    if (item["id"].is_string()) id=item["id"].get<std::string>();
    if (item["author"].is_string()) Author=item["author"].get<std::string>();
    if (item["title"].is_string()) Title=item["author"].get<std::string>();
    if (item["journal"].is_string()) Journal=item["journal"].get<std::string>();
    if (item["year"].is_number()) Year=item["year"].get<int>();
    if (item["volume"].is_number()) Volume=item["volume"].get<int>();
    if (item["issue"].is_number()) Issue=item["issue"].get<int>();
  }
};
class Webpage:public Citation{
private:
std::string Url{};
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
     if (item["id"].is_string()) id=item["id"].get<std::string>();
     else{}
     if (item["url"].is_string()) Url=item["url"].get<std::string>();
     else{}
     if (item["title"].is_string()) Title=item["title"].get<std::string>();
     else {
        httplib::Client client{ "http://docman.lcpu.dev" };
        auto title_response = client.Get("/title/" + encodeUriComponent(Url));
        Title=title_response->body;
     }
     
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