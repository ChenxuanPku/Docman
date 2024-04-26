#pragma once
#ifndef CITATION_H
#define CITATION_H

#include <string>
#include<nlohmann/json.hpp>
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
protected:
  std::map<std::string,std::string>IniInf{};
  std::map<std::string,std::string> GetInf{};  
public: 
  
  Citation (){}
  Citation (std::map<std::string,std::string>&IniInf,std::map<std::string,std::string>& GetInf,nlohmann::json&item);
  virtual void Print(std::ostream& output){}
  std::string GetId()
  {
    return IniInf["id"];
  }
};
class Book:public Citation{
private:
  std::map<std::string,std::string>oIniInf={{"id","-"},{"isbn","-"},{"type","book"}};
  std::map<std::string,std::string> oGetInf={
    {"author","-"},
    {"title","-"},
    {"year","-"}};
public:
  

  void Print(std::ostream& output)
  {
    output<<"["<<Citation::IniInf["id"]<<"] "<<IniInf["type"]<<": "<<Citation::GetInf["author"]<<","<<Citation::GetInf["title"]<<","<<Citation::GetInf["publisher"]<<","<<Citation::GetInf["year"]<<std::endl;
  }
  Book (nlohmann::json&item):Citation(oIniInf,oGetInf,item)
  {std::cout<<"construct book"<<std::endl;
  }
};

class Article:public Citation{
private:
  std::map<std::string,std::string>oIniInf={
    {"id","-"},
    {"title","-"},
    {"author","-"},
    {"year","-"},
    {"journal","-"},
    {"volume","-"},
    {"issue","-"},
    {"type","article"}
  };
  std::map<std::string,std::string>oGetInf={};
public:

    void Print(std::ostream& output)
  {
    output<<"["<<Citation::IniInf["id"]<<"] "<<IniInf["type"]<<": "<<Citation::IniInf["author"]<<","<<Citation::IniInf["title"]<<","<<Citation::IniInf["journal"]<<","<<Citation::IniInf["year"]<<","<<","<<Citation::IniInf["volume"]<<","<<Citation::IniInf["issue"]<<std::endl;
  }
  Article (nlohmann::json&item):Citation(oIniInf,oGetInf,item)
  {std::cout<<"construct article"<<std::endl;
  }
};
class Webpage:public Citation{
private:

  std::map<std::string,std::string>oIniInf={{"id","-"},{"url","-"},{"type","webpage"}};
  std::map<std::string,std::string> oGetInf={
    {"title","-"}};

public:
   void Print(std::ostream& output)
  {
    output<<"["<<IniInf["id"]<<"] "<<IniInf["type"]<<": "<<IniInf["title"]<<". Avaiable at"<<IniInf["url"]<<std::endl;
  } 
  Webpage (nlohmann::json&item):Citation(oIniInf,oGetInf,item){std::cout<<"construct webpage"<<std::endl;}
};
int TypeID(std::string s)
{
  if(s=="article")return 1;
  if(s=="book") return 2;
  if(s=="webpage") return 3;
  return 0;
}
Citation::Citation (std::map<std::string,std::string>& otherIniInf,std::map<std::string,std::string>& otherGetInf,nlohmann::json&item):IniInf(otherIniInf),GetInf(otherGetInf)
{
  std::cout<<"construct citation"<<std::endl;

  for (auto a:IniInf)
    {
      if (item[a.first].is_string()) a.second=item[a.first].get<std::string>();else std::exit(1);
    }
  httplib::Client client{ API_ENDPOINT };
  if(IniInf["type"]=="book")

  {
    for (auto a:GetInf)
    {
       auto response=client.Get(HTstring(a.first) + encodeUriComponent(IniInf["isbn"]));
      if(response->status==200) a.second=response->body;else std::exit(1);
      a.second=response->body;
    }}
  if(IniInf["type"]=="webpage")
  {for (auto a:GetInf)
    {
      auto response=client.Get(HTstring(a.first) + encodeUriComponent(IniInf["url"]));
      if(response->status==200) a.second=response->body;else std::exit(1);
    }}  
}
Citation* CitationConstruct(nlohmann::json& item )
{  
  std::cout<<item["id"].get<std::string>()<<item["type"].get<std::string>()<<std::endl;
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
      std::exit(1);
      return new Citation;
    }
  }
}
bool cmp(Citation* a,Citation* b)
{
  return a->GetId()<b->GetId();
}

void Process(std::vector<std::string>& Lib, std::vector<Citation*>& Input,std::vector<Citation*>& Output){
  std::sort(Lib.begin(),Lib.end()); 
  int SizeLib{Lib.size()};
  int SizeIn{Input.size()};
  int PtrLib{0},PtrIn{0};
  for(;PtrIn!=SizeIn;PtrIn++)
  {
    if(Lib[PtrLib]==Input[PtrIn]->GetId())
    {
       Output.push_back(Input[PtrIn]);
       PtrLib++;
       
    }
    if(PtrLib==SizeLib) break;
  }if (PtrLib!=SizeLib) std::exit(1);
}
#endif