#pragma once
#ifndef CITATION_H
#define CITATION_H

#include <string>
#include<nlohmann/json.hpp>
#include<map>
#include <cpp-httplib/httplib.h>
#include "utils.hpp"
std::map<std::string,std::string>bookIniInf={{"id",""},{"isbn",""},{"type","book"}};
std::map<std::string,std::string>bookGetInf={
    {"author",""},
    {"title",""},
    {"publisher",""},
    {"year",""}};
std::map<std::string,std::string>articleIniInf={
    {"id",""},
    {"title",""},
    {"author",""},
    {"year",""},
    {"journal",""},
    {"volume",""},
    {"issue",""},
    {"type","article"}
  };
std::map<std::string,std::string>articleGetInf={{"",""}};
std::map<std::string,std::string>webIniInf={{"id",""},{"url",""},{"type","webpage"}};
std::map<std::string,std::string>webGetInf={
    {"title",""}};
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
  std::map<std::string,std::string>GetInf{};  
public: 
  
  Citation (){}
  Citation (nlohmann::json&item, std::map<std::string,std::string>&IniInf, std::map<std::string,std::string>& GetInf);
  virtual void Print(std::ostream& output){}
  std::string GetId()
  {
    return IniInf["id"];
  }
};
class Book:public Citation{
private:
  
public:
  

  void Print(std::ostream& output)
  {
    output<<"["<<Citation::IniInf["id"]<<"] "<<IniInf["type"]<<": "<<Citation::GetInf["author"]<<", "<<Citation::GetInf["title"]<<", "<<Citation::GetInf["publisher"]<<", "<<Citation::GetInf["year"]<<std::endl;
  }
  Book (nlohmann::json&item):Citation(item,bookIniInf,bookGetInf)
  {
    
  }
};
class Article:public Citation{
private:
  
public:

    void Print(std::ostream& output)
  {
    output<<"["<<Citation::IniInf["id"]<<"] "<<IniInf["type"]<<": "<<Citation::IniInf["author"]<<", "<<Citation::IniInf["title"]<<", "<<Citation::IniInf["journal"]<<", "<<Citation::IniInf["year"]<<", "<<Citation::IniInf["volume"]<<", "<<Citation::IniInf["issue"]<<std::endl;
  }
  Article (nlohmann::json&item):Citation(item,articleIniInf,articleGetInf)
  {
  }
};
class Webpage:public Citation{
private:

 
public:
   void Print(std::ostream& output)
  {
    output<<"["<<IniInf["id"]<<"] "<<IniInf["type"]<<": "<<GetInf["title"]<<". Available at "<<IniInf["url"]<<std::endl;
  } 
  Webpage (nlohmann::json&item):Citation(item,webIniInf,webGetInf){}
};
int TypeID(std::string s)
{
  if(s=="article")return 1;
  if(s=="book") return 2;
  if(s=="webpage") return 3;
  return 0;
}
Citation::Citation (nlohmann::json&item, std::map<std::string,std::string>& otherIniInf,std::map<std::string,std::string>& otherGetInf):IniInf(otherIniInf),GetInf(otherGetInf)
{
 
  for (auto a:IniInf)
    { 
      
      if (item.contains(a.first)){
        if(item[a.first].is_null()) std::exit(1);
        if(item[a.first].is_number_integer())IniInf[a.first]=std::to_string(item[a.first].get<int>());
        else if(item[a.first].is_string())IniInf[a.first]=item[a.first].get<std::string>();else std::exit(1);
       }else std::exit(1);
    
    }
  
  //std::cout<<a.first<<" "<<a.second<<std::endl;
 
 httplib::Client client{"http://docman.lcpu.dev"};
 if(IniInf["type"]=="book")

  {
    
       auto response=client.Get("/isbn/" + encodeUriComponent(IniInf["isbn"]));
      
      if(response && response->status == httplib::OK_200)
      {
       // std::cout << response->body << std::endl; 
         nlohmann::json data = nlohmann::json::parse(response->body);
        for(auto a:GetInf)
        {
        
          GetInf[a.first]=data[a.first].get<std::string>();
        }
      }
        else{
        std::exit(1);
      } 
     
    }
   
  if(IniInf["type"]=="webpage")
  {
    
      auto response=client.Get("/title/" + encodeUriComponent(IniInf["url"]));
      //std::cout<<IniInf["url"]<<" "<<response->body<<std::endl;
           if(response && response->status == httplib::OK_200)
           {
             nlohmann::json data = nlohmann::json::parse(response->body);
             for(auto a:GetInf)
             {if (item.contains(a.first)){
        if(item[a.first].is_null()) std::exit(1);
        if(item[a.first].is_number_integer())GetInf[a.first]=std::to_string(item[a.first].get<int>());
        else if(item[a.first].is_string())GetInf[a.first]=item[a.first].get<std::string>();else std::exit(1);
       }else std::exit(1);
           } 
           }
           else{std::exit(1);

    }  }
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
 
  int SizeLib{Lib.size()};
  int SizeIn{Input.size()};
  int PtrLib{0},PtrIn{0};
  for(;PtrIn!=SizeIn;PtrIn++)
  {
   // std::cout<<PtrIn<<" "<<PtrLib<<std::endl;
   // std::cout<<Lib[PtrLib]<<" "<<Input[PtrIn]->GetId()<<std::endl;
    if(Lib[PtrLib]==Input[PtrIn]->GetId())
    {
     //  std::cout<<Input[PtrIn]->GetId()<<std::endl;
       Output.push_back(Input[PtrIn]);
       PtrLib++;
       
    }
    if(PtrLib==SizeLib) break;
  }if (PtrLib!=SizeLib) std::exit(1);
}
#endif