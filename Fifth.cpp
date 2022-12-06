#include <iostream>
#include <fstream>
#include <string>

using std::cout;
using std::endl;
using std::string;

string line, one = "", two = "", three = "", fourth = "", 
        fifth = "", sixth = "", seventh = "", eighth = "", nineth = "";
string stacks[] = {one, two, three, fourth, fifth, sixth, seventh, eighth, nineth};

bool readStack(const string &input, char FROM)
{
    size_t beg = input.find_first_of(FROM, 0);
    int index = beg / 4;
    
    if (beg == std::string::npos)
        return false;
    
    while (beg != std::string::npos)
    {
        stacks[index].insert(0, 1, input[beg + 1]);
        beg = input.find_first_of(FROM, beg + 1);
        index = beg / 4;
    }

    return true;
}

bool readOperation(const string &input)
{
    size_t beg = input.find("move ");
    size_t end = input.find(" from");

    if (beg == std::string::npos)
        return false;

    int howMany = std::stoi(input.substr(beg + 4, end));
    
    beg = input.find("from ");
    end = input.find(" to");
    int source = std::stoi(input.substr(beg + 5, end));

    beg = input.find("to ");
    int destination = std::stoi(input.substr(beg + 3));

    for (int i = 0; i < howMany; i++)
    {
        stacks[destination - 1].push_back(
            stacks[source - 1].back()
        );
        stacks[source - 1].pop_back();
    }

    return true;
}

bool upgradeOperation(const string &input)
{
    size_t beg = input.find("move ");
    size_t end = input.find(" from");

    if (beg == std::string::npos)
        return false;

    int howMany = std::stoi(input.substr(beg + 4, end));
    
    beg = input.find("from ");
    end = input.find(" to");
    int source = std::stoi(input.substr(beg + 5, end));

    beg = input.find("to ");
    int destination = std::stoi(input.substr(beg + 3));

    int length = stacks[source - 1].length();
    stacks[destination - 1].append(
        stacks[source - 1].substr( length - howMany)
    );
    stacks[source - 1].erase(length - howMany);

    return true;
}

int main()
{   
    std::ifstream input("input5.txt", std::ios::in);

    if (input.good())
    {
        while (!input.eof())
        {
            std::getline(input, line);

            if (!readStack(line, '['))
                upgradeOperation(line);
         
            line = "";
        }

        for (int i = 0; i < 9; i++)
            cout << stacks[i].back();
    }


    input.close();
    return 0;
}