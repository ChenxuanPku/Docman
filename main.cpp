#include <fstream>
#include <iostream>
#include <vector>

#include "utils.hpp"
#include "citation.h"
#include "newstring.h"
#include <nlohmann/json.hpp>
int num;
void log(){
    std::cout<<num<<std::endl;
    num++;
}
std::vector<Citation*> loadCitations(const std::string& filename) {
    // FIXME: load citations from file
    //open the file(.json)
    //std::cout<<filename<<std::endl;
    
    std::ifstream inputJson(filename);
    std::vector<Citation*> Cite{};
    
    nlohmann::json data = nlohmann::json::parse(inputJson);
    for (auto& item: data["citations"] )
    {
        
        Cite.push_back(CitationConstruct(item));
    }
    std::sort(Cite.begin(),Cite.end(),cmp);
    
    return Cite;
}
String readFromFile(const std::string& filename)
//读文件,输入字母串组
{   
    
    
    String FileResult{}; 
    std::string line;
    if(filename!="-")
    {std::ifstream inputFile(filename);
    while(std::getline(inputFile,line))
      FileResult.Push_Back(line);}
    else 
    {while(std::getline(std::cin,line))
      FileResult.Push_Back(line);}
    return FileResult;
    //这里相当于起到了构造函数的作用
}



int main(int argc, char** argv) {
    // "docman", "-c", "citations.json", "input.txt"
    
    num=0;
    
    auto citations = loadCitations(argv[2]);
    std::vector<Citation*> printedCitations{};
    
    // FIXME: read all input to the string, and process citations in the input text
    int Pos;
    if(argv[3]=="-o")Pos=5;else Pos=3;
    auto input = readFromFile(argv[Pos]);
   
    auto ProcessedInput=CheckLegal(input);
    
    Process(ProcessedInput,citations,printedCitations);
    // ...

    if (Pos==5)
    {std::ofstream output{argv[4]};
    output << input;  // print the paragraph first
        output << "\nReferences:\n";
      //  std::cout<<input;
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

