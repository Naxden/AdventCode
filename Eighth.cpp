#include "includes.hpp"

bool seeFromRight(const vector<string>& rows, int targetX, int targetY, int width)
{
    for (int i = width - 1; i > targetX; i--)
        if (rows[targetY][targetX] <= rows[targetY][i])
            return false;

    return true;
}

bool seeFromLeft(const vector<string>& rows, int targetX, int targetY)
{
    for (int i = 0; i < targetX; i++)
        if (rows[targetY][targetX] <= rows[targetY][i])
            return false;

    return true;
}

bool seeFromTop(const vector<string>& rows, int targetX, int targetY)
{
    for (int i = 0; i < targetY; i++)
        if (rows[targetY][targetX] <= rows[i][targetX])
            return false;

    return true;
}

bool seeFromBottom(const vector<string>& rows, int targetX, int targetY, int height)
{
    for (int i = height - 1; i > targetY; i--)
        if (rows[targetY][targetX] <= rows[i][targetX])
            return false;

    return true;
}

void printVisible(const vector<string>& rows)
{
    int heigth = rows.size();
    int width = rows[0].size();

    for (auto row : rows)
        cout << row << endl;

    cout << endl;
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < heigth; y++)
        {
            (seeFromLeft(rows, x, y) ||
             seeFromRight(rows, x, y, width) ||
             seeFromTop(rows, x, y) ||
             seeFromBottom(rows, x, y, heigth)) ?
                cout << '1' :
                cout << '0';
        }
        cout << endl;
    }

}


int countVisible(const vector<string>& rows)
{
    int sum = 0;
    int heigth = rows.size();
    int width = rows[0].size();

    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < heigth; y++)
        {
            sum += (seeFromLeft(rows, x, y) ||
             seeFromRight(rows, x, y, width) ||
             seeFromTop(rows, x, y) ||
             seeFromBottom(rows, x, y, heigth)) ?
                1 :
                0;
        }
    }

    return sum;
}

int seeToRight(const vector<string>& rows, int targetX, int targetY, int width)
{
    int seeLength = 1;
    for (int i = targetX + 1; i < width - 1; i++)
    {
        if (rows[targetY][targetX] <= rows[targetY][i])
            break;
        seeLength++;
    }

    return seeLength;
}

int seeToLeft(const vector<string>& rows, int targetX, int targetY)
{
    int seeLength = 1;
    for (int i = targetX - 1; i > 0; i--)
    {
        if (rows[targetY][targetX] <= rows[targetY][i])
            break;
        seeLength++;
    }

    return seeLength;
}

int seeToBottom(const vector<string>& rows, int targetX, int targetY, int height)
{
    int seeLength = 1;
    for (int i = targetY + 1; i < height - 1; i++)
    {
        if (rows[targetY][targetX] <= rows[i][targetX])
            break;
        seeLength++;
    }

    return seeLength;
}

int seeToTop(const vector<string>& rows, int targetX, int targetY)
{
    int seeLength = 1;
    for (int i = targetY - 1; i > 0; i--)
    {
        if (rows[targetY][targetX] <= rows[i][targetX])
            break;
        seeLength++;
    }

    return seeLength;
}

int printScenic(const vector<string>& rows)
{
    int max = 0;
    int heigth = rows.size();
    int width = rows[0].size();

    for (auto row : rows)
        cout << row << endl;

    cout << endl;
    for (int y = 0; y < heigth; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int scenic = 1;
            scenic *= seeToTop(rows, x, y);
            scenic *= seeToRight(rows, x, y, width);
            scenic *= seeToBottom(rows, x, y, heigth);
            scenic *= seeToLeft(rows, x, y);

            cout << scenic << " ";
            if (scenic > max)
                max = scenic;
        }
        cout << endl;
    }

    return max;
}

int main()
{
    ifstream input("input8.txt", std::ios::in);

    vector<string> rows;
    if (input.good())
    {
        while (!input.eof())
        {
            string line;
            std::getline(input, line);
            rows.push_back(line);
        }

    }
    // printVisible(rows);
    // cout << "Visible: " << countVisible(rows);

    cout << printScenic(rows);
    input.close();
    return 0;
}