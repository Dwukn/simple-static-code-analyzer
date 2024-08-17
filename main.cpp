#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <regex>


void analyzeCode(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    std::string line;
    int lineNumber = 0;
    int commentCount = 0;
    std::vector<std::string> functionNames;
    std::vector<std::string> classNames;
    std::vector<std::string> variableDeclarations;

    // Regular expressions to match C++ constructs
    std::regex commentRegex("//.*|/\\*.*\\*/");
    std::regex functionRegex(R"(\b(\w+)\s+(\w+)\s*\([^)]*\)\s*\{)");
    std::regex classRegex(R"(\bclass\s+(\w+))");
    std::regex varRegex(R"(\b(\w+)\s+(\w+)\s*[\w\*]*\s*(?:=\s*[^;]*)?;)");

    while (std::getline(file, line)) {
        ++lineNumber;

        // Count comments
        if (std::regex_search(line, commentRegex)) {
            ++commentCount;
        }

        // Extract functions
        std::smatch functionMatch;
        if (std::regex_search(line, functionMatch, functionRegex)) {
            functionNames.push_back(functionMatch[2]);
        }

        // Extract classes
        std::smatch classMatch;
        if (std::regex_search(line, classMatch, classRegex)) {
            classNames.push_back(classMatch[1]);
        }

        // Extract variable declarations
        std::smatch varMatch;
        if (std::regex_search(line, varMatch, varRegex)) {
            variableDeclarations.push_back(line);
        }
    }

    // Output results
    std::cout << "Total lines: " << lineNumber << std::endl;
    std::cout << "Total comments: " << commentCount << std::endl;

    std::cout << "Functions:" << std::endl;
    for (const auto& func : functionNames) {
        std::cout << "  " << func << std::endl;
    }

    std::cout << "Classes:" << std::endl;
    for (const auto& cls : classNames) {
        std::cout << "  " << cls << std::endl;
    }

    std::cout << "Variable declarations:" << std::endl;
    for (const auto& var : variableDeclarations) {
        std::cout << "  " << var << std::endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <source-file>" << std::endl;
        return 1;
    }
    if (argc ==2 && std::strcmp(argv[1], "-h") == 0){
        std::cout << "Usage: analyze <source-file>" << std::endl;
        return 0;
    }

    analyzeCode(argv[1]);
    return 0;
}