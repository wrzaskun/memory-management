#include <iostream>
#include <memory>
using namespace std;

class Node
{
public:
    Node(const int v) : value(v) {}

    shared_ptr<Node> next;
    int value;
};

class List
{
public:
    List(){};

    void add(unique_ptr<Node> node)
    {
        if (first == nullptr)
        {
            first = std::move(node);
        }
        else
        {
            shared_ptr<Node> current = first;
            while (current->next)
            {
                current = (current->next);
            }
            current->next = std::move(node);
        }
    };

    shared_ptr<Node> get(const int value)
    {
        if (!first)
        {
            cout << "List is empty!" << endl;
            return nullptr;
        }
        else
        {
            shared_ptr<Node> current = (first);
            do
            {
                if (current->value == value)
                {
                    cout << "Found value " << current->value << endl;
                    return current;
                }
                else
                {
                    cout << "Going through " << current->value << endl;
                    current = (current->next);
                }
            } while (current);
            cout << "Not found: value " << value << endl;
            return nullptr;
        }
    }

private:
    shared_ptr<Node> first;
};

int main()
{
    List lista;
    auto node4 = make_unique<Node>(4);
    auto node7 = make_unique<Node>(7);

    lista.add(std::move(node4));
    lista.add(make_unique<Node>(2));
    lista.add(std::move(node7));
    lista.add(make_unique<Node>(9));
    auto node = lista.get(1);

    if (node)
        cout << node->value << '\n';

    return 0;
}
