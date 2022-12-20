#include "includes.hpp"

struct Node
{
    short int height;
    float globalGoal;
    float localGoal;
    bool visited;
    int x;
    int y;
    vector<Node*> neighbours;
    Node* parent;
};

Node* createNode()
{
    Node* temp = new Node;
    temp->globalGoal = INFINITY;
    temp->localGoal = INFINITY;
    temp->visited = false;
    temp->parent = nullptr;

    return temp;
}

Node* map;
Node* start;
Node* end;
int rangeY;
int rangeX;

void updateNeighbours()
{
    for (int y = 0; y < rangeY; y++)
    {
        for (int x = 0; x < rangeX; x++)
        {
            if (y > 0 &&
                map[rangeX * (y - 1) + x].height - map[rangeX * y + x].height <= 1)
                    map[rangeX * y + x].neighbours.push_back(&map[rangeX * (y - 1) + x]);
            if (y < rangeY - 1 &&
                map[rangeX * (y + 1) + x].height - map[rangeX * y + x].height <= 1)
                    map[rangeX * y + x].neighbours.push_back(&map[rangeX * (y + 1) + x]);
            if (x > 0 &&
                map[rangeX * y + (x - 1)].height - map[rangeX * y + x].height <= 1)
                    map[rangeX * y + x].neighbours.push_back(&map[rangeX * y + (x - 1)]);
            if (x < rangeX - 1 &&
                map[rangeX * y + (x + 1)].height - map[rangeX * y + x].height <= 1)
                    map[rangeX * y + x].neighbours.push_back(&map[rangeX * y + (x + 1)]);
            
        }
    }
}

auto distance  = [](Node* a, Node* b)
{
    return sqrtf(pow(a->x - b->x, 2) + pow(a->y - b->y, 2));
};

void aStarPath()
{
    Node* nodeCurrent = start;
    start->localGoal = 0.0f;
    start->globalGoal = distance(start, end);

    list<Node*> listNotTestedNotes;
    listNotTestedNotes.push_back(start);

    while (!listNotTestedNotes.empty())
    {
        listNotTestedNotes.sort([](const Node* a, const Node* b) { return a->globalGoal < b->globalGoal; });

        while (!listNotTestedNotes.empty() && listNotTestedNotes.front()->visited)
            listNotTestedNotes.pop_front();

        if (listNotTestedNotes.empty())
            break;

        nodeCurrent = listNotTestedNotes.front();
        nodeCurrent->visited = true;

        for (auto neighbour : nodeCurrent->neighbours)
        {
            if (!neighbour->visited)
                listNotTestedNotes.push_back(neighbour);

            float possibleLowerGoal = nodeCurrent->localGoal + distance(nodeCurrent, end);

            if (possibleLowerGoal < neighbour->localGoal)
            {
                neighbour->parent = nodeCurrent;
                neighbour->localGoal = possibleLowerGoal;

                neighbour->globalGoal = neighbour->localGoal + distance(neighbour, end);
            }
        }
    }
}

void resetPath()
{
    for (int y = 0; y < rangeY; y++)
    {
        for (int x = 0; x < rangeX; x++)
        {
            map[y * rangeX + x].globalGoal = INFINITY;
            map[y * rangeX + x].localGoal = INFINITY;
            map[y * rangeX + x].parent = nullptr;
            map[y * rangeX + x].visited = false;
        }
    }
}

int countSteps()
{
    Node* temp = end;
    int counter = 0;
    while (temp != start)
    {
        counter++;
        if (temp == nullptr)
        {
            cout << "There is no valid path :/" << endl;
            return 99999;
        }
        temp = temp->parent;
    }

    return counter;
}
    

int main()
{
    int linesCount = 0;
    string line;
    ifstream input("input12.txt", std::ios::in);

    if (input.good())
    {
        while (std::getline(input, line))
        {
            rangeX = line.size();
            rangeY++;
        }
        input.clear();
        input.seekg(0);
        map = new Node[rangeX * rangeY];
        linesCount = 0;

        // addding Nodes
        while (!input.eof())
        {
            input >> line;
            for (int x = 0; x < rangeX; x++)
            {
                Node* temp = createNode();
                temp->x = x;
                temp->y = linesCount;
                temp->height = line[x] - 'a';
                map[linesCount * rangeX + x] = *temp;
                if (line[x] == 'S')
                {
                    start = &map[linesCount * rangeX + x];
                    start->height = 0;
                }
                else if (line[x] == 'E')
                {
                    end = &map[linesCount * rangeX + x];
                    end->height = 25;
                }

            }
            
            linesCount++;
        }

        // Add neighbours
        updateNeighbours();
        
        int minimum = 9999;
        for (int y = 0; y < rangeY; y++)
        {
            for (int x = 0; x < rangeX; x++)
            {
                if (map[rangeX * y + x].height == 0)
                {
                    start = &map[rangeX * y + x];
                    resetPath();
                    aStarPath();
                    cout << "start: " << start->x << " " << start->y << endl;
                    int steps = countSteps(); 
                    if (steps < minimum)
                        minimum = steps;
                }
            }
        }

        cout << minimum;
        // aStarPath();

        // for (int y = 0; y < rangeY; y++)
        // {
        //     cout << y << '\t';
        //     for (int x = 0; x < rangeX; x++)
        //     {
        //         if (map[rangeX * y + x].visited)
        //             cout << "O";
        //         else
        //             cout << ".";
        //     }
        //     cout << endl;
        // }

        delete[] map;
        input.close();
    }

    return 0;
}