#include <iostream>
#include "SmartPointer.h"

class Resource
{
    int size;
    int* value;
public:
    Resource(int size = 0)
        : size{ size },
        value{ new int[size] } 
    {
        std::cout << "Resource CONSTRUCT\n";
    };
        

    Resource(const Resource& other)
        : size{ other.size },
        value{ new int[size] }
    {
        for (int i{}; i < size; i++)
            value[i] = other.value[i];
        std::cout << "Resource COPY CONSTRUCT\n";
    }

    Resource(Resource&& other)
        :size{ other.size },
        value{ other.value }
    {
        other.value = nullptr;
        std::cout << "Resource MOVE CONSTRUCT\n";
    }

    int* Value() const { return value; }
    int Size() const { return size; }
    int& Item(int index) { return value[index]; }

    ~Resource() 
    { 
        delete[] value;
        std::cout << "Resource DESTRUCT\n"; 
    }
};

void print(std::string& message)
{
    std::cout << "l-value: " << message << "\n";
}

void print(std::string&& message)
{
    std::cout << "r-value: " << message << "\n";
}

void ResourceInit(Resource& resource)
{
    for (int i{}; i < resource.Size(); i++)
        resource.Item(i) = rand() % 100;
}

void ResourcePrint(Resource& resource)
{
    for (int i{}; i < resource.Size(); i++)
        std::cout << resource.Item(i) << " ";
    std::cout << "\n";
}

int main()
{
    srand(time(nullptr));

    //Resource resource(10);
    //ResourceInit(resource);
    //ResourcePrint(*(new Resource(5)));

    Resource res1(5);
    ResourceInit(res1);

    std::unique_ptr<Resource> uniq1(&res1);
    std::unique_ptr<Resource> uniq2;
    
    std::shared_ptr<Resource> shared1(&res1);
    std::shared_ptr<Resource> shared2(shared1);
}
