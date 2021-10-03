#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Resource
{
    Resource(char *byte) : byte_(byte) {}
    char *byte() const { return byte_; }
    virtual string name() const = 0;
    virtual ~Resource() { delete byte_; } //to powinno być virtualne bo nie zwolni pamięci w destruktorze.

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
    Resource *makeResourceA(char *byte) { return new ResourceA{byte}; } //to tylko tworzy wskaźnik na wpisane dane. Niebezpiecznie dawać to na stercie zwłaszcza że to tylko char.
    Resource *makeResourceB(char *byte) { return new ResourceB{byte}; } 
};

struct ResourceCollection
{
    void add(Resource *r) { resources.push_back(r); }
    void clear() //to kasuje tylko wskaźniki do tych zasobów a nie same zasoby. - trzeba zrobić pętle kasującą.
    {
        for (const auto &res : resources)
        {
            delete res;
        }
        resources.clear();
    }                                                            
    Resource *operator[](int index) { return resources[index]; } //nie ma sprawdzenie czy taki index będzie w dostępnych zasobach.
    void printAll()
    {
        for (const auto &res : resources) 
        {
            cout << res->name() << endl;
        }
    }

private:
    vector<Resource *> resources; //unikałbym wskaźnika skoro to vektor bo może go ktoś usunąć, lepiej kopiować tak małe dane albo dać shared_ptr.
};

int main()
{
    ResourceCollection collection;
    ResourceFactory rf;
    collection.add(rf.makeResourceA(new char{0x01})); //może ktoś podać wskaźnik do zasobu który później zostanie skasowany. np: char * x = new char{0x01}
    collection.add(rf.makeResourceB(new char{0x02}));
    collection.printAll();

    //tak nie powinno się dać zrobić, zwracam wskaźnik i mogę teraz podmienić wartość np: firstByte = new char (3);
    auto firstByte = collection[0]->byte();
    firstByte = new char {0x67}; //podmieniam wartość
    cout << *firstByte << endl;

    collection.clear();

    return 0;
}
