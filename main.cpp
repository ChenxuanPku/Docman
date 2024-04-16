#include <fstream>
#include <iostream>
#include <vector>

#include "utils.hpp"
#include "citation.h"
#include "newstring.h"
std::vector<Citation*> loadCitations(const std::string& filename) {
    // FIXME: load citations from file
    //open the file(.json)

}
String readFromFile(const std::string& filename)
//读文件,输入字母串组
{
    std::ifstream inputFile(filename);
    String FileResult{}; 
    std::string line;
    while(std::getline(inputFile,line))
      FileResult.Push_Back(line);
    return FileResult;
    //这里返回一整个std::vector<std::string>是不是太浪费内存了,或许我们可以动态分配内存.
    //或许我们应该重新写一个输出.
}
int main(int argc, char** argv) {
    // "docman", "-c", "citations.json", "input.txt"

    auto citations = loadCitations(argv[2]);
    std::vector<Citation*> printedCitations{};

    // FIXME: read all input to the string, and process citations in the input text
    auto input = readFromFile(argv[3]);
    // ...

    std::ostream& output = std::cout;

    for (auto c : printedCitations) {
        output << input;  // print the paragraph first
        output << "\nReferences: \n";
        c->Print(output);
        // FIXME: print citation
        // I guess I have done.
    }

    for (auto c : citations) {
        delete c;
    }
}

