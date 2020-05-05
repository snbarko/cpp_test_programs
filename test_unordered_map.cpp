#include <iostream>
#include <boost/unordered_map.hpp>

class Node
{
public:
    Node(int _vba, int _data)
    {
        vba = _vba;
        data = _data;
    }

    int getData()
    {
        return data;
    }
private:
    int vba;
    int data;
};

int main()
{
    int maxelements = 4;
    int vba = 11;
    int data = 110;

    boost::unordered_map<int, Node&> myMap;

    for(int i = 0; i < maxelements; i++)
    {
        Node *node = new Node(vba, data);

        myMap.insert(boost::unordered_map<int, Node&>::value_type(vba, *node));
        vba += 11;
        data += 110;
    }

    vba = 0;

    for (int i = 0; i < maxelements + 1; i++)
    {
        boost::unordered_map<int, Node&>::iterator it(myMap.find(vba));
        if (it == myMap.end())
        {
            std::cout << "Entry not found" << std::endl;
        }
        else
        {
            Node &node = it->second;
            std::cout << "Entry found. Data " << node.getData() << std::endl;
        }
        vba += 11;
    }

    return 0;
}
