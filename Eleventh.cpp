#include "includes.hpp"
#include <functional>

class Monkey
{
private:
    std::function<long long (long long)> operation;
    int divisble;
    int trueMonkey, falseMonkey;
public:
    void itemOperation(vector<long long>::iterator itemIter);
    vector<long long> worriedItems;
    int inspectedItems = 0;
    int GetDivisible() {return divisble;}
    Monkey() = default;
    Monkey(vector<long long> items, std::function<long long (long long)> funcOperation, int test, int trueMonkey, int negMonkey) :
        worriedItems(items), operation(funcOperation), divisble(test), trueMonkey(trueMonkey), falseMonkey(negMonkey) {}
    ~Monkey() = default;
};

const int MONKEY_COUNT = 8;
Monkey monkeys[MONKEY_COUNT];
static int allDivisible = 1;

void Monkey::itemOperation(vector<long long>::iterator itemIter)
{
    *itemIter = operation(*itemIter);
    // part 1
    // *itemIter /= 3;
    // part 2
    *itemIter %= allDivisible;

    int correctMonkey = (*itemIter % divisble == 0) ? trueMonkey : falseMonkey; 

    monkeys[correctMonkey].worriedItems.push_back(*itemIter);
    inspectedItems++;
}

int main()
{

    monkeys[0] = Monkey({63, 57}, [](long long old) { return old * 11; }, 7, 6, 2);
    monkeys[1] = Monkey({82, 66, 87, 78, 77, 92, 83}, [](long long old) { return old + 1; }, 11, 5, 0);
    monkeys[2] = Monkey({97, 53, 53, 85, 58, 54}, [](long long old) { return old * 7; }, 13, 4, 3);
    monkeys[3] = Monkey({50}, [](long long old) { return old + 3; }, 3, 1, 7);
    monkeys[4] = Monkey({64, 69, 52, 65, 73}, [](long long old) { return old + 6; }, 17, 3, 7);
    monkeys[5] = Monkey({57, 91, 65}, [](long long old) { return old + 5; }, 2, 0, 6);
    monkeys[6] = Monkey({67, 91, 84, 78, 60, 69, 99, 83}, [](long long old) { return old * old; }, 5, 2, 4);
    monkeys[7] = Monkey({58, 78, 69, 65}, [](long long old) { return old + 7; }, 19, 5, 1);
    for (int i = 0; i < MONKEY_COUNT; i++)
    {
        allDivisible *= monkeys[i].GetDivisible();
    }

    for (int round = 0; round < 10000; round++)
    {
        for (int i = 0; i < MONKEY_COUNT; i++)
        {
            for (auto item = monkeys[i].worriedItems.begin(); item != monkeys[i].worriedItems.end(); item++)
            {
                monkeys[i].itemOperation(item);
            }
            monkeys[i].worriedItems.clear();
        }
    }

    for (int i = 0; i < MONKEY_COUNT; i++)
    {
        cout << "Monkey " << i << ": " << monkeys[i].inspectedItems << endl;
    }

    return 0;
}