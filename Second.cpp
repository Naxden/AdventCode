#include <iostream>
#include <fstream>


int evalMoves(char opponent, char player)
{
    int opNum = opponent - 'A';
    int plNum = player - 'X';

    if (opNum == plNum)
        return 3 + plNum + 1;
    else if ((opNum + 1) % 3 == plNum)
        return 6 + plNum + 1;
    
    return plNum + 1;
}

int secretEvalMoves(char opponent, char tactic)
{
    char option = tactic - 'X';
    char player;

    if (option == 0)
    {
        player = ((opponent - 'A') + 2) % 3 + 'X';
    }
    else if (option == 1)
    {
        player = opponent + 23;
    }
    else
    {
        player = ((opponent - 'A') + 1) % 3 + 'X';
    }
        
    return evalMoves(opponent, player);
}

int main(int arc, char *argv[])
{
    std::ifstream input;
    char opponent, player;
    int sumScore = 0;
    int score;
    input.open("input2.txt", std::ios::in);

    if (input.good())
    {
        while (!input.eof())
        {
            input >> opponent >> player;
            
            score = secretEvalMoves(opponent, player);
            sumScore += secretEvalMoves(opponent, player);

            std::cout << opponent << " " << player << " : " << score << std::endl;
        }
        sumScore -= score;
        std::cout << sumScore << std::endl;
    }
    input.close();
    return 0;
}