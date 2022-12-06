#include <iostream>
#include <fstream>

using namespace std;

int calculatePriority(string text)
{
    int index = 0;
    int halfLength = text.length() / 2; 
    bool found = false;

    for (; index < halfLength && !found; index++)
    {
        for (int i = halfLength; i < text.length(); i++)
        {
            if (text[i] == text[index])
            {
                found = true;
                break;
            }
        }
        if (found)
            break;
    }

    if (text[index] > 'Z')
        return text[index] - 'a' + 1;

    return text[index] - 'A' + 27; 
} 

int calcualteBadge(string &one, string &two, string &three)
{
    int i = 0;
    bool found = false;

    for (; i < one.length(); i++)
    {
        for (int j = 0; j < two.length(); j++)
        {
            for (int k = 0; k < three.length(); k++)
            {
                if (one[i] == two[j] && two[j] == three[k])
                {
                    found = true;
                    break;
                }
            }
            if (found)
                break;
        }
        if (found)
            break;
    }
    
    if (one[i] > 'Z')
        return one[i] - 'a' + 1;

    return one[i] - 'A' + 27; 
}

int main()
{
    ifstream input("input3.txt", ios::in);

    if (input.good())
    {
        string one, two, three;
        int sum = 0;
        while (!input.eof())
        {
            input >> one >> two >> three;
            sum += calcualteBadge(one, two, three);
            cout << one << endl << two << endl << three<< endl;
            one = two = three = "";
        }
        cout << sum << endl;
    }

    input.close();
    return 0;
}