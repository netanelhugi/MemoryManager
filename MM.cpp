// Netanel Hugi, 203553490.

#include <iostream>
#include <new> 
#include "MM.h"
#include "Circle.h"
#include "Triangle.h"

using std::cout;
using std::endl;
using std::set;

// extern object:
MemoryManager mm;

// Default construcetor:
// 1. Assign memory for CirclePool and TrianglePool.
// 2. Fill the sets with blocks numbers(index).
MemoryManager::MemoryManager()
{
    CirclePool = (char *)malloc(POOL_SIZE * sizeof(Circle));
    TrianglePool = (char *)malloc(POOL_SIZE * sizeof(Triangle));

    for (int i = 0; i < POOL_SIZE; i++)
    {
        CircleSet.insert(i);
        TriangleSet.insert(i);
    }
}

// Destructor:
// Free pool's memory.
MemoryManager::~MemoryManager()
{
    std::free(CirclePool);
    // std::free(CirclePool);
    std::free(TrianglePool);
}


// alloc function:
// Argument: 
// 1. t = size of object.
// Return: pointer to block memory address,
// or throw exception if out of memory.
void *MemoryManager::alloc(size_t t)
{
    size_t Csize = sizeof(Circle);
    size_t Tsize = sizeof(Triangle);

    // Circle case:
    if (t == Csize)
    {
        // If there is an available block:
        if (CircleSet.size() > 0)
        {
            set<int>::iterator it = CircleSet.cbegin();
            int index = *it;
            CircleSet.erase(it);

            return &CirclePool[index * Csize];
        }

        else
        {
            cout << "Out of memory! \n";
            throw std::bad_alloc();
        }
    }

    // Triangle case:
    else if (t == Tsize)
    {
        // If there is an available block:
        if (TriangleSet.size() > 0)
        {
            set<int>::iterator it = TriangleSet.cbegin();
            int index = *it;
            TriangleSet.erase(it);

            return &TrianglePool[index * Tsize];
        }

        else
        {
            cout << "Out of memory! \n";
            throw std::bad_alloc();        
        }
    }
}

// free function:
// Argument:
// 1. obj = pointer to object.
// Return: void.
void MemoryManager::free(void *obj)
{

    // If the address of the object is in CirclePool:
    if (&CirclePool[0] <= obj && obj <= &CirclePool[POOL_SIZE * sizeof(Circle)])
    {
        // Find block index for CircleSet:
        unsigned long block = (unsigned long)obj - (unsigned long)CirclePool;
        block /= sizeof(Circle);

        CircleSet.insert(block);
    }

    // If the address of the object is in TrianglePool:
    else if (&TrianglePool[0] <= obj && obj <= &TrianglePool[POOL_SIZE * sizeof(Triangle)])
    {
        // Find block index for TriangleSet:
        unsigned long block = (unsigned long)obj - (unsigned long)TrianglePool;
        block /= sizeof(Triangle);

        TriangleSet.insert(block);
    }

}

// free_circles function:
// Return: Number of available blocks.
int MemoryManager::free_circles()
{
    return CircleSet.size();
}

// free_triangles function:
// Return: Number of available blocks.
int MemoryManager::free_triangles()
{
    return TriangleSet.size();
}
