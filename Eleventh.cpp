#include "includes.hpp"
#include <functional>
#include <bignum.h>



class Monkey
{
private:
    std::function<bignum (bignum)> operation;
    bignum divisble;
    int trueMonkey, falseMonkey;
public:
    void itemOperation(vector<bignum>::iterator itemIter);
    vector<bignum> worriedItems;
    unsigned int inspectedItems = 0;
    
    Monkey() = default;
    Monkey(vector<bignum> items, std::function<bignum (bignum)> funcOperation, bignum test, int trueMonkey, int negMonkey) :
        worriedItems(items), operation(funcOperation), divisble(test), trueMonkey(trueMonkey), falseMonkey(negMonkey) {}
    ~Monkey() = default;
};

Monkey monkeys[4];

void Monkey::itemOperation(vector<bignum>::iterator itemIter)
{
    *itemIter = operation(*itemIter);

    // *itemIter /= 3;

    int correctMonkey = (*itemIter % divisble == 0) ? trueMonkey : falseMonkey; 

    monkeys[correctMonkey].worriedItems.push_back(*itemIter);
    inspectedItems++;
}

int main()
{

    monkeys[0] = Monkey({79, 98}, [](bignum old) { return old * 19; }, 23, 2, 3);
    monkeys[1] = Monkey({54, 65, 75, 74}, [](bignum old) { return old + 6; }, 19, 2, 0);
    monkeys[2] = Monkey({79, 60, 97}, [](bignum old) { return old * old; }, 13, 1, 3);
    monkeys[3] = Monkey({74}, [](bignum old) { return old + 3; }, 17, 0, 1);

    for (int round = 0; round < 20; round++)
    {
        for (int i = 0; i < 4; i++)
        {
            for (auto item = monkeys[i].worriedItems.begin(); item != monkeys[i].worriedItems.end(); item++)
            {
                monkeys[i].itemOperation(item);
            }
            monkeys[i].worriedItems.clear();
        }
        // cout << "After round " << round + 1 << ", the monkeys are holding items with these worry levels:" << endl;
        // for (int i = 0; i < 4; i++)
        // {
        //     cout << "Monkey " << i << ": ";
        //     for (auto item : monkeys[i].worriedItems)
        //     {
        //         cout << item.to_string() << ", ";
        //     }
        //     cout << endl;
        // }
    }

    for (int i = 0; i < 4; i++)
    {
        cout << "Monkey " << i << ": " << monkeys[i].inspectedItems << endl;
    }

    return 0;
}