#include "includes.hpp"

class Container
{
public:
    string name;
    int size;
    Container(string name, int size, Container* parent) : 
        name(name), size(size), parent(parent) {}
    Container* parent;
    vector<Container*> children;
};

Container* root;

int sumSize(Container* node, int sum, int &totalSum)
{
    if (node->children.size() == 0)
        return node->size;

    for (auto child : node->children)
    {
        sum += sumSize(child, 0, totalSum);
    }

    if (node->size == 0)
    {
        cout << node->name << " " << sum << endl;
        totalSum += sum;
    }
    
    return sum;    
}

int toDelete(Container* node, int sum, int &rootSize, int &minimum)
{
    if (node->children.size() == 0)
        return node->size;

    for (auto child : node->children)
    {
        sum += toDelete(child, 0, rootSize, minimum);
    }

    if (node->size == 0)
    {
        if (rootSize - sum <= 40000000)
        {
            cout << "Candidate: " << node->name << ": " << sum << endl;
            if (sum < minimum)
            {
                cout << "Change Min to: " << node->name << ": " << sum << endl;
                minimum = sum;
            }
        }
    }
    
    return sum;    
}

Container* findChild(const string &childName, Container *parent)
{
    for (auto child : parent->children)
    {
        if (child->name == childName)
            return child;
    }

    return nullptr;
}

Container* cdCommand(const string &line, Container *node)
{
    string dirName = line.substr(line.find_last_of(" ") + 1);

    if (dirName == "/")
        return root;
    if (dirName == "..")
        return node->parent;

    return findChild(dirName, node);
}

void addChildren(const string &line, Container* parent)
{
    auto namePos = line.find("dir");

    if (namePos != string::npos) //it's a directory
    {
        string name = line.substr(line.find(" ") + 1);
        Container* child = new Container(name, 0, parent);
        parent->children.push_back(child);
    }
    else //it's a file
    {
        auto spacePos = line.find(' '); 
        int size = std::stoi(line.substr(0, spacePos));
        string name = line.substr(spacePos + 1);
        Container* child = new Container(name, size, parent);
        parent->children.push_back(child);
    }
}

int switchCommand(const string &line)
{
    auto condition = line.find("cd ");

    if (condition != string::npos)
        return 1;
    
    return 3;
}

int main()
{
    std::ifstream input("input7.txt", std::ios::in);

    if (input.good())
    {
        string line;
        root = new Container("/", 0, nullptr);
        Container* pointer = root;
        int option = 0;
        int sum = 0;
        while (!input.eof())
        {
            std::getline(input, line);

            if (line == "")
                continue;

            if (line[0] == '$')
                option = switchCommand(line);
            if (option == 1)
                pointer = cdCommand(line, pointer);
            if (option == 2)
                addChildren(line, pointer);
            if (option == 3)
                option--;           

            line = "";            
        }
        int min = 999999999;
        int rootSize = 45174025;
        toDelete(root, 0, rootSize, min);
        cout << "Min: " << min;

    }

    input.close();

    return 0;
}