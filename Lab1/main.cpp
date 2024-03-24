#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

class Line {
private:
    std::vector<std::string> words;

public:
    Line(const std::string& line) {
        std::istringstream iss(line);
        std::string word;
        while (iss >> word) {
            words.push_back(word);
        }
    }

std::string getAlignedLine(int lineLength) const {
    std::string alignedLine;
    int currentLength = 0;

    for (const auto& word : words) {
        if (currentLength + word.length() > lineLength) {
            alignedLine += "\n" + word + " ";
            currentLength = word.length() + 1;
        } else {
            alignedLine += word + " ";
            currentLength += word.length() + 1;
        }
    }

    return alignedLine;
}
};

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input_file> <line_length>" << std::endl;
        return 1;
    }

    std::ifstream inputFile(argv[1]);
    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open input file." << std::endl;
        return 1;
    }

    int lineLength = std::stoi(argv[2]);

    std::vector<Line> lines;
    std::string line;
    while (std::getline(inputFile, line)) {
        Line currentLine(line);
        lines.push_back(currentLine);
    }

    for (const auto& line : lines) {
        std::string alignedLine = line.getAlignedLine(lineLength);
        std::cout << alignedLine << std::endl;
    }

    inputFile.close();
    return 0;
}