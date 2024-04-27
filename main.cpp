#include <fstream>
#include <iostream>
#include <vector>
#include<cstring>
#include<string>
#include "utils.hpp"
#include "citation.h"
#include "newstring.h"
#include <nlohmann/json.hpp>
int num;
void log(){
    std::cout<<num<<std::endl;
    num++;
}
std::vector<Citation*> loadCitations(const char*  filename) {
    // FIXME: load citations from file
    //open the file(.json)
    //std::cout<<filename<<std::endl;
     
    std::ifstream inputJson(filename);
   try{
    std::vector<Citation*> Cite{};
    
    nlohmann::json data = nlohmann::json::parse(inputJson);
    for (auto& item: data["citations"] )
    {
        
        Cite.push_back(CitationConstruct(item));
    }
    if(Cite.size()==0)std::exit(1);
    std::sort(Cite.begin(),Cite.end(),cmp);
    
    return Cite;}
    catch(const nlohmann::json::parse_error& e){
       // std::cout<<"json"<<std::endl;
        std::exit(1);    }
}
String readFromFile(const  char* filename)
//读文件,输入字母串组
{   
    
    int num{0};
    String FileResult{}; 
    std::string line;
    if(strcmp(filename,"-")!=0)
    {std::ifstream inputFile(filename);
    while(std::getline(inputFile,line))
      {num++;FileResult.Push_Back(line);}}
    else 
    {while(std::getline(std::cin,line))
       {num++;FileResult.Push_Back(line);}}
   if(num>0)return FileResult;
   else std::exit(1);
    //这里相当于起到了构造函数的作用
}



int main(int argc, char** argv) {
    // "docman", "-c", "citations.json", "input.txt"
    if(argc==4) {
       if(strcmp(argv[1],"-c")!=0)std::exit(1);
    }else
    if(argc==6){
       if(strcmp(argv[1],"-c")!=0||strcmp(argv[3],"-o")!=0) std::exit(1);
    }
    else std::exit(1);
    num=0;
    auto citations = loadCitations(argv[2]);
    std::vector<Citation*> printedCitations{};
    
    // FIXME: read all input to the string, and process citations in the input text
    int Pos{argc-1};
    auto input = readFromFile(argv[Pos]);
    
    auto ProcessedInput=CheckLegal(input);
    Process(ProcessedInput,citations,printedCitations);
    
    // ...
   
    if (Pos==5)

    {   
        std::ofstream output{argv[4]};
        output << input;  // print the paragraph first
        output << "\nReferences:\n";
       
    //check whether the input is legal.
    for (auto c : printedCitations) {
        
        c->Print(output);
        // FIXME: print citation
       
    }}
    else {
        
        std::ostream& output{std::cout};
        output << input;  // print the paragraph first
        output << "\nReferences:\n";
    //check whether the input is legal.
    for (auto c : printedCitations) {
         // print the paragraph first
        
        c->Print(output);
        // FIXME: print citation
       
    }}
    for (auto c : citations) {
        delete c;
    }
}

