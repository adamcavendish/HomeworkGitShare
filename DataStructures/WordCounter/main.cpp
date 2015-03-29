// STL
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
// C-Standard
#include <cctype>
#include <cstdio>

// @brief split function splits string 's' into an array of strings into a vector
// @example split("Hello World to you to all", isspace)
//          --> vector{"Hello", "World", "to", "you", "to", "all"}
// @example split("Hello,World to;you_to,all", [](char c) {
//              return isspace(c) || (c == ',') || (c == ';') || (c == '_'); });
//          --> vector{"Hello", "World", "to", "you", "to", "all"}
template <typename UnaryFunc>
std::vector<std::string> split(const std::string & s, UnaryFunc isSeperator) {
	std::vector<std::string> ret;

    std::string::size_type wordStart = 0;
    std::string::size_type wordEnd = 0;
    std::string::size_type sLength = s.length();

    while(wordStart < sLength) {
        // find the first char that is not a seperator
        // @example: "   word here"
        //               ^
        //               wordStart = First char that is not a space
        wordStart = wordEnd;
        while(wordStart < sLength && isSeperator(s[wordStart]))
            ++wordStart;
        // find the first char that is a seperator
        // @example: "   word here"
        //                   ^
        //                   wordEnd = First char that is a space
        wordEnd = wordStart;
        while(wordEnd < sLength && !isSeperator(s[wordEnd]))
            ++wordEnd;

        if(wordStart < wordEnd)
            ret.push_back(s.substr(wordStart, wordEnd - wordStart));
    }

    return ret;
}

// @brief readAllInLines() will read in 'path' file into lines
std::vector<std::string> readAllInLines(const std::string & path) {
    std::vector<std::string> ret;

    // open file to read
    std::ifstream ifs(path);
    if(!ifs)
        throw std::runtime_error("cannot open file: " + path);

    std::string line;
    while(true) {
        std::getline(ifs, line);
        if(!ifs)
            break;
        ret.push_back(line);
    }

    return ret;
}

// @brief readAllInWords() will read in 'path' file into words, split by space
std::vector<std::string> readAllInWords(const std::string & path) {
    std::vector<std::string> ret;

    // open file to read
    std::ifstream ifs(path);
    if(!ifs)
        throw std::runtime_error("cannot open file: " + path);

    std::string word;
    while(true) {
        ifs >> word;
        if(!ifs)
            break;
        ret.push_back(word);
    }

    return ret;
}

struct WordInfo {
    std::string word;
    std::vector<std::size_t> lines;
};

void printWordInfos(const std::vector<WordInfo> & wordInfos, const std::vector<std::string> & lines) {
    // for each 'info' in 'wordInfos', here 'info' is a WordInfo type
    for(const WordInfo & info : wordInfos) {
        std::cout << info.word << ": " << info.lines.size() << " in total"
            << std::endl;
        for(const std::size_t lineNumber : info.lines)
            std::cout << "  @" << lineNumber << ": " << lines[lineNumber] << std::endl;
    }
}

int main(int argc, char * argv[])
{
    std::vector<std::string> lines = readAllInLines("file.txt");
    std::vector<std::string> analysisWords = readAllInWords("words.txt");

    // initialize 'wordInfos' with 'analysisWords' and empty vector
    std::vector<WordInfo> wordInfos;
    for(std::size_t i = 0; i < analysisWords.size(); ++i)
        wordInfos.push_back({ analysisWords[i], std::vector<std::size_t>() });

    // for each line
    for(std::size_t i = 0; i < lines.size(); ++i) {
        // i is actually the line number
        std::size_t lineNumber = i;

        std::vector<std::string> words = split(lines[i], isspace);
        // for each word in current line
        for(std::size_t j = 0; j < words.size(); ++j) {
            // if words[j] is in the 'wordInfos'
            auto iter = std::find_if(wordInfos.begin(), wordInfos.end(),
                    [&](const WordInfo & info) { return info.word == words[j]; });
            if(iter != wordInfos.end()) {
                // this means that word[j] is found
                iter->lines.push_back(lineNumber);
            }
        }
    }

    printWordInfos(wordInfos, lines);

    return 0;
}

