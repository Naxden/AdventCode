#include <iostream>
#include <fstream>
#include <string>

typedef struct Set
{
    int begin;
    int end;
} Set;

int convertAndErase(std::string &text,const char &oper)
{
    int value;
    size_t index = text.find(oper);

    value = std::stoi(text.substr(0, index));
    text.erase(0, index + 1);

    return value;
}

int isSubset(const Set &a, const Set &b)
{
    if (a.begin <= b.begin && a.end >= b.end)
        return 1;
    if (b.begin <= a.begin && b.end >= a.end)
        return 1;

    return 0;    
}

int doesOverlap(const Set &a, const Set &b)
{
    if (a.begin < b.begin && a.end < b.begin)
        return 0;
    if (b.begin < a.begin && b.end < a.begin)
        return 0;

    return 1;
}

int main()
{
    std::ifstream input("input4.txt", std::ios::in);

    if (input.good())
    {
        std::string line;
        Set one, two;
        int sum = 0;
        while (!input.eof())
        {
            std::getline(input, line);

            one.begin = convertAndErase(line, '-');
            one.end = convertAndErase(line, ',');
            two.begin = convertAndErase(line, '-');
            two.end = convertAndErase(line, '\0');


            sum += doesOverlap(one, two);
            line = "";            
        }
        std::cout << sum << std::endl; 
    }

    input.close();

    return 0;
}