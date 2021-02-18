#include <iostream>
#include <boost/lockfree/queue.hpp>

class Node
{
public:
    Node(int _data):data(_data) { std::cout << "Node created" <<std::endl; }
    int getValue() { return data; }
private:
    int data;
};

int main()
{
    boost::lockfree::queue<Node*> myQueue{10};

    for (int i = 0; i < 10; i++)
    {
        Node *node = new Node(11*i);
        if (!myQueue.push(node))
        {
            std::cout << "Push not successful" << std::endl;
        }
        else
        {
            std::cout << "Push successful" << std::endl;
        }
    }
    
    return 0;
}
