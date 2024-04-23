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
  Citation (){}
  virtual std::string getType() 
  {
     return "citation";
  } 
  virtual void Print(std::ostream& output);
  
};
class Book:public Citation{
private:
  std::string Type{"book"};
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
    output<<"["<<IniInf["id"]<<"] "<<Type<<": "<<GetInf["author"]<<","<<GetInf["title"]<<","<<GetInf["publisher"]<<","<<GetInf["year"]<<std::endl;
  }
  Book (nlohmann::json&item)
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
      auto response=client.Get(HTstring(a.first) + encodeUriComponent(IniInf["isbn"]));
      a.second=response->body;
    }
    
  }
};

class Article:public Citation{
private:
  std::map<std::string,std::string>IniInf={
    {"id",""},
    {"title",""},
    {"author",""},
    {"year",""},
    {"journal",""},
    {"volume",""},
    {"issue",""}
  };
  std::string Type{"article"};
public:
std::string getType() 
  {
     return "article";
  } 
    void Print(std::ostream& output)
  {
    output<<"["<<IniInf["id"]<<"] "<<Type<<": "<<IniInf["author"]<<","<<IniInf["title"]<<","<<IniInf["journal"]<<","<<IniInf["year"]<<","<<","<<IniInf["volume"]<<","<<IniInf["issue"]<<std::endl;
  }
  Article (nlohmann::json&item)
  {
    for (auto a:IniInf)
    {
      if (item[a.first].is_string()) a.second=item[a.first].get<std::string>(); //else;
    }
  }
};
class Webpage:public Citation{
private:
std::string Type{"book"};
  std::map<std::string,std::string>IniInf={{"id",""},{"url",""}};
  std::map<std::string,std::string> GetInf={
    {"title",{}}};
std::string Type{"webpage"};
public:
std::string getType() 
  {
     return "webpage";
  } 
   void Print(std::ostream& output)
  {
    output<<"["<<IniInf["id"]<<"] "<<Type<<": "<<IniInf["title"]<<". Avaiable at"<<IniInf["url"]<<std::endl;
  } 
  Webpage (nlohmann::json&item)
  {
     for (auto a:IniInf)
    {
      if (item[a.first].is_string()) a.second=item[a.first].get<std::string>();
    }
   
    httplib::Client client{ "http://docman.lcpu.dev" };
    for (auto a:GetInf)
    {
      auto response=client.Get(HTstring(a.first) + encodeUriComponent(IniInf["url"]));
      a.second=response->body;
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