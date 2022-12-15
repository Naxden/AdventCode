#include "includes.hpp"

int signalStrength = 0;

int SignalStrength(const int& cycle, const int& registerV)
{
    signalStrength += cycle * registerV;
    return cycle * registerV;
}

void nextCycle(int& cycle, int& registerV)
{
    cycle++;
    if ((cycle - 20) % 40 == 0)
        cout << cycle << " :" << SignalStrength(cycle, registerV) << endl;
}

void processorTick(const string& line, int& cycle, int& registerV)
{
    bool mode = line.find("noop") == string::npos;

    if (mode)
    {
        nextCycle(cycle, registerV);
        nextCycle(cycle, registerV);
        registerV += std::stoi(line.substr(5));
    }
    else
        nextCycle(cycle, registerV);
}

void drawPixel(const int index,const int& registerV)
{
    if (abs(index - registerV) <= 1)
        cout << '#';
    else
        cout << '.';
}

void nextCycleCRT(int& cycle, int& registerV)
{
    cycle++;
    drawPixel((cycle - 1) % 40, registerV);
    if (cycle % 40 == 0)
    {
        cout << endl;
    }
}

void processorTickCRT(const string& line, int& cycle, int& registerV)
{
    bool mode = line.find("noop") == string::npos;

    if (mode)
    {
        nextCycleCRT(cycle, registerV);
        nextCycleCRT(cycle, registerV);
        registerV += std::stoi(line.substr(5));
    }
    else
        nextCycleCRT(cycle, registerV);
}

int main()
{
    ifstream input("input10.txt", std::ios::in);
    string line;
    int cycle = 0;
    int registerV = 1;

    if (input.good())
    {
        while (!input.eof())
        {
            getline(input, line);

            // processorTick(line, cycle, registerV);
            processorTickCRT(line, cycle, registerV);
        }
        cout << "signalSum: " << signalStrength << endl;
        input.close();
    }


    return 0;
}