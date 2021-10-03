#include <iostream>
#include <vector>
#include <string>
#include <memory>

using namespace std;

struct Resource
{
    Resource(char *byte) : byte_(byte) {}
    char *byte() const { return byte_; }
    virtual string name() const = 0;
    virtual ~Resource() { delete byte_; }

protected:
    char *byte_ = nullptr;
};

struct ResourceA : virtual public Resource
{
    ResourceA(char *byte) : Resource(byte) {}
    string name() const override
    {
        auto result = string("ResourceA ");
        string b{*byte()};
        return result.append(b);
    }
};

struct ResourceB : virtual public Resource
{
    ResourceB(char *byte) : Resource(byte) {}
    string name() const override
    {
        auto result = string("ResourceB ");
        string b{*byte()};
        return result.append(b);
    }
};

struct ResourceFactory
{
    shared_ptr<Resource> makeResourceA(char *byte) { return make_shared<ResourceA>(byte); } //fix by share_ptr
    shared_ptr<Resource> makeResourceB(char *byte) { return make_shared<ResourceB>(byte); }
};

struct ResourceCollection
{
    void add(std::shared_ptr<Resource> r) { resources.push_back(r); }
    void clear()
    {
        resources.clear();
    }
    shared_ptr<Resource> operator[](int index) { return resources.at(index); } //change to at, to throw, need protect either
    void printAll()
    {
        for (const auto &res : resources)
        {
            cout << res->name() << endl;
        }
    }

private:
    vector<shared_ptr<Resource>> resources;
};

int main()
{
    ResourceCollection collection;
    ResourceFactory rf;
    collection.add(rf.makeResourceA(new char{0x01})); //może ktoś podać wskaźnik do zasobu który później zostanie skasowany. np: char * x = new char{0x01}
    collection.add(rf.makeResourceB(new char{0x02}));
    collection.printAll();

    //tak nie powinno się dać zrobić, zwracam wskaźnik i mogę teraz podmienić wartość np: firstByte = new char (3);
    unique_ptr<char> firstByte = make_unique<char>(*collection[0]->byte()); //hamuje wyciek
    firstByte = make_unique<char>(0x67);                                    //podmieniam wartość
    cout << *collection[0]->byte() << endl;

    collection.clear();

    return 0;
}
