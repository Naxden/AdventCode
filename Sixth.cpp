#include <iostream>
#include <string>
#include <fstream>

bool findMarkerRecursive(const std::string &word, int start, int end)
{
    if (start == end)
        return true;
    
    if (word[start] == word[end])
        return false;

    return  findMarkerRecursive(word, start, end - 1) &&
            findMarkerRecursive(word, start + 1, end); 
}

int findMarker(const std::string &word)
{
    bool condition = false; 

    for (int i = 0; i < word.length() - 4; i++)
    {
        condition = findMarkerRecursive(word, i, i + 3);
        if (condition)
            return i + 4;
    }

    return -1; 
}

int findMessage(const std::string &word)
{
    bool condition = false; 

    for (int i = 0; i < word.length() - 14; i++)
    {
        condition = findMarkerRecursive(word, i, i + 13);
        if (condition)
            return i + 14;
    }

    return -1; 
}

int main()
{
    std::ifstream input("input6.txt", std::ios::in);

    if (input.good())
    {
        std::string line;
        int sum = 0;
        while (!input.eof())
        {
            std::getline(input, line);

            std::cout << findMarker(line) << std::endl;

            line = "";            
        }
        std::cout << sum << std::endl; 
    }

    input.close();

    return 0;
}