#include "test_runner.h"
#include "profile.h"

#include <algorithm>
#include <vector>
#include <string>
#include <set>
#include <iostream>
#include <sstream>

//-------------------------------------------------------------------------------------------------
class Learner 
{
private:
    std::set<std::string> dict;
public:
    int Learn(const std::vector<std::string>& words)
    {
        int newWords = 0;

        for (const auto& word : words)
        {
            if (dict.find(word) == dict.end())
            {
                newWords++;
                dict.insert(word);
            }
        }
        return newWords;
    }

    std::vector<std::string> KnownWords()
    {
        return {dict.begin(), dict.end()};
    }
};
//-------------------------------------------------------------------------------------------------
int main()
{
    Learner learner;
    std::string line;
    while (std::getline(std::cin, line))
    {
        std::vector<std::string> words;
        std::stringstream ss(line);
        std::string word;
        while (ss >> word)
        {
            words.push_back(word);
        }
        std::cout << learner.Learn(words) << "\n";
    }
    std::cout << "=== known words ===\n";

    for (auto word : learner.KnownWords())
    {
        std::cout << word << "\n";
    }
    return 0;
}
//-------------------------------------------------------------------------------------------------