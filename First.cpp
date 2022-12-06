#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

int top3FattestElves(std::vector<int> elfCalories)
{
    std::sort(elfCalories.begin(), elfCalories.end());

    auto end = elfCalories.end();

    return  *(end - 1) + *(end - 2) + *(end - 3);
}

int fattestElfCalories(std::vector<int> &elfCalories)
{
    std::sort(elfCalories.begin(), elfCalories.end());

    auto fattestElf = elfCalories.end();

    return *(fattestElf - 1);
} 

// Biggest sum 
int main(int, char**) 
{
    std::ifstream input;
    std::string line;
    std::vector<int> elfsCalories = {0}; 
    int elf = 0;

    input.open("input1.txt", std::ios::in);

    if (input.good())
    {
        while (!input.eof())
        {
            std::getline(input, line);
            
            if (line == "") 
            {
                elf++;
                elfsCalories.push_back(0);
            }
            else
                elfsCalories[elf] += std::stoi(line);

            line = "";
        }
        
        std::cout << fattestElfCalories(elfsCalories) << std::endl;
        std::cout << top3FattestElves(elfsCalories) << std::endl;
    }

    input.close();
    return 0;
}
