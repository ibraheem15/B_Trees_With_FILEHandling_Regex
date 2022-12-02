/***********************
 **  Ibraheem Rehman  **
 **  SE-Q    21i-1102 **
 ***********************/

#include <iostream>
using namespace std;

template <typename T>
class Vector
{
    T *arr;
    int size;
    int capacity;
    T *next;

public:
    Vector()
    {
        size = 0;
        capacity = 1;
        arr = new T[capacity];
    }
    void push_back(T data)
    {
        if (size == capacity)
        {
            T *temp = new T[2 * capacity];
            for (int i = 0; i < capacity; i++)
            {
                temp[i] = arr[i];
            }
            delete[] arr;
            capacity *= 2;
            arr = temp;
        }
        arr[size] = data;
        size++;
    }
    T operator[](int i)
    {
        return arr[i];
    }
    int getSize()
    {
        return size;
    }
    void pop_back()
    {
        if (size > 0)
        {
            size--;
        }
    }
    T back()
    {
        return arr[size - 1];
    }
    // erase
    void erase(int i)
    {
        for (int j = i; j < size - 1; j++)
        {
            arr[j] = arr[j + 1];
        }
        size--;
    }
    void erase(T data)
    {
        for (int i = 0; i < size; i++)
        {
            if (arr[i] == data)
            {
                erase(i);
                return;
            }
        }
    }
    // begin
    T *begin()
    {
        return arr;
    }
    // getroot
    T getroot()
    {
        return arr[0];
    }
};

class Node
{
public:
    char id;
    int distanceFromStart;
    Node *next;

    Node(char id);
    char getId();
    int getSize();
    int getDistanceFromStart();
    void setDistanceFromStart(int distanceFromStart);
    Node *getPrevious();
    void setPrevious(Node *next);
};

class Edge
{
public:
    Node *node1;
    Node *node2;
    int distance;
    Edge *next;

    Edge(Node *node1, Node *node2, int distance);
    bool Connects(Node *node1, Node *node2);
    int getDistance();
    Node *getOtherNode(Node *node);
    Edge *getNext();
    void setNext(Edge *next);
};

class Graph
{
public:
    // Node *nodes;
    // Vector<Node *> nodes;
    // Vector<Edge *> edges;
    // Edge *edges;
    int size;

    Graph();
    void addNode(char id);
    void addEdge(char id1, char id2, int distance);
    void printGraph();
    void printNodes();
    void printEdges();
    Vector<Edge *> *AdjacentEdges(Vector<Edge *> &edges, Node *node);
    void RemoveEdge(Vector<Edge *> &edges, Edge *edge);
    void Dijkstras();
    void DijkstrasTest();

    void printNode(Node *node);
    void printEdge(Edge *edge);
    Node *getNode(char id);
    Edge *getEdge(char id1, char id2);
    Vector<Node *> *AdjacentRemainingNodes(Node *node);
    Node *ExtractSmallest(Vector<Node *> &nodes);
    int Distance(Node *node1, Node *node2);
    bool Contains(Vector<Node *> &nodes, Node *node);
    void PrintShortestRouteTo(Node *destination);
};