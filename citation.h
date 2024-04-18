#pragma once
#ifndef CITATION_H
#define CITATION_H

#include <string>
#include <nlohmann/json.hpp>
#include<map>
#include <cpp-httplib/httplib.h>
#include "utils.hpp"

std::string HTstring(const std::string& str)//在字符串前后加/ /
{
  std::string ans{"/"};
  ans+=str;
  ans.append("/");
  return ans;

} 
class Citation {
public: 
  std::string id;
  std::string Title; 
  std::map<std::string,std::string> IniInf;
  std::map<std::string,std::string> GetInf;
  Citation (){}
  Citation (const std::map<std::string,std::string>& T,std::map<std::string,std::string>& TT)
  : IniInf{T},GetInf{TT} {}
  virtual std::string getType() 
  {
     return "citation";
  } 
  virtual void Print(std::ostream& output);
  
};
class Book:public Citation{
private:
  
  
  
  std::string Type{"book"};
  std::string Isbn{};
  std::map<std::string,std::string>IniInf={{"id",""},{"isbn",""}};
  std::map<std::string,std::string> GetInf={
    {"author",{}},
    {"title",{}},
    {"year",{}}};
public:
  std::string getType() 
  {
     return "book";
  } 
  void Print(std::ostream& output)
  {
    output<<"["<<id<<"] "<<Type<<": "<<GetInf["author"]<<","<<GetInf["title"]<<","<<GetInf["publisher"]<<","<<GetInf["year"]<<std::endl;
  }
  Book (nlohmann::json&item):
  Citation(IniInf,GetInf)
  {
    for (auto a:IniInf)
    {
      if (item[a.first].is_string()) a.second=item[a.first].get<std::string>();
    }
    if (item["id"].is_string()) IniInf["id"]=item["id"].get<std::string>();//else 报错
    if (item["isbn"].is_string()) IniInf["isbn"]=item["isbn"].get<std::string>();//else 报错
    httplib::Client client{ "http://docman.lcpu.dev" };
    for (auto a:GetInf)
    {
      auto response=client.Get(HTstring(a.first) + encodeUriComponent(Isbn));
      a.second=response->body;
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