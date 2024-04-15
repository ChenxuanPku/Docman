#include <fstream>
#include <iostream>
#include <vector>

#include "utils.hpp"
#include "citation.h"

std::vector<Citation*> loadCitations(const std::string& filename) {
    // FIXME: load citations from file
    //open the file(.json)

}
std::vector<std::string> readFromFile(const std::string& filename)
{
    
}
int main(int argc, char** argv) {
    // "docman", "-c", "citations.json", "input.txt"

    auto citations = loadCitations(argv[2]);
    std::vector<Citation*> printedCitations{};

    // FIXME: read all input to the string, and process citations in the input text
    // auto input = readFromFile(argv[3]);
    // ...

    std::ostream& output = std::cout;

    for (auto c : printedCitations) {
        // output << input;  // print the paragraph first
        output << "\nReferences: \n";
        c->Print(output);
        // FIXME: print citation
        // I guess I have done.
    }

    for (auto c : citations) {
        delete c;
    }
}

