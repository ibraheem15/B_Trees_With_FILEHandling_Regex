/***********************
 **  Ibraheem Rehman  **
 **  SE-Q    21i-1102 **
 ***********************/

#include "Graph.hxx"
#include <iostream>
#include <fstream>
#include <string>
#include <regex>

using namespace std;

#define INT_MAX 10000000

Vector<Edge *> edges;
Vector<Node *> nodes;

Node::Node(char id)
{
    this->id = id;
    distanceFromStart = INT_MAX;
    next = NULL;
    nodes.push_back(this);
}

char Node::getId()
{
    return id;
}

int Node::getDistanceFromStart()
{
    return distanceFromStart;
}

void Node::setDistanceFromStart(int distanceFromStart)
{
    this->distanceFromStart = distanceFromStart;
}

Node *Node::getPrevious()
{
    return next;
}

void Node::setPrevious(Node *next)
{
    this->next = next;
}

Edge::Edge(Node *node1, Node *node2, int distance)
{
    this->node1 = node1;
    this->node2 = node2;
    this->distance = distance;
    next = NULL;
    edges.push_back(this);
}

bool Edge::Connects(Node *node1, Node *node2)
{
    return (
        (node1 == this->node1 &&
         node2 == this->node2) ||
        (node1 == this->node2 &&
         node2 == this->node1));
}

Node *Edge::getOtherNode(Node *node)
{
    if (node == node1)
        return node2;
    else if (node == node2)
        return node1;
    else
        return NULL;
}

int Edge::getDistance()
{
    return distance;
}

Edge *Edge::getNext()
{
    return next;
}

void Edge::setNext(Edge *next)
{
    this->next = next;
}

Graph::Graph()
{
}

Node *Graph::ExtractSmallest(Vector<Node *> &nodes)
{
    int size = nodes.getSize();
    if (size == 0)
        return NULL;
    int smallestPosition = 0;
    // Node *smallest = nodes.at(0);
    Node *smallest = nodes[0];
    for (int i = 1; i < size; ++i)
    {
        // Node *current = nodes.at(i);
        Node *current = nodes[i];
        if (current->distanceFromStart <
            smallest->distanceFromStart)
        {
            smallest = current;
            smallestPosition = i;
        }
    }
    nodes.erase(smallestPosition);
    return smallest;
}

bool Graph::Contains(Vector<Node *> &nodes, Node *node)
{
    // const int size = nodes.size();
    const int size = nodes.getSize();
    for (int i = 0; i < size; ++i)
    {
        // if (node == nodes.at(i))
        if (node->id == nodes[i]->id)
        {
            return true;
        }
    }
    return false;
}

Vector<Node *> *Graph::AdjacentRemainingNodes(Node *node)
{
    Vector<Node *> *adjacentNodes = new Vector<Node *>();

    const int size = edges.getSize();
    for (int i = 0; i < size; ++i)
    {
        // Edge *edge = edges.at(i);
        Edge *edge = edges[i];
        Node *adjacent = NULL;
        // if (edge->node1 == node)
        if (edge->node1->id == node->id)
        {
            adjacent = edge->node2;
        }
        // else if (edge->node2 == node)
        else if (edge->node2->id == node->id)
        {
            adjacent = edge->node1;
        }
        if (adjacent != NULL && Contains(nodes, adjacent))
        {
            adjacentNodes->push_back(adjacent);
        }
    }
    return adjacentNodes;
}

void Graph::PrintShortestRouteTo(Node *destination)
{
    Node *next = destination;
    cout << "Starting Destination: " << destination->distanceFromStart << endl;
    while (next)
    {
        cout << next->id << " ";
        next = next->next;
    }
    cout << endl;
}

int Graph::Distance(Node *node1, Node *node2)
{
    // const int size = edges.size();
    const int size = edges.getSize();
    for (int i = 0; i < size; ++i)
    {
        // Edge *edge = edges.at(i);
        Edge *edge = edges[i];
        if (edge->Connects(node1, node2))
        {
            return edge->distance;
        }
    }
    return -1; // should never happen
}

Vector<Edge *> *Graph::AdjacentEdges(Vector<Edge *> &edges, Node *node)
{
    Vector<Edge *> *adjacentEdges = new Vector<Edge *>();

    const int size = edges.getSize();
    for (int i = 0; i < size; ++i)
    {
        // Edge *edge = edges.at(i);
        Edge *edge = edges[i];
        if (edge->node1 == node)
        {
            cout << "adjacent: " << edge->node2->id << endl;
            adjacentEdges->push_back(edge);
        }
        else if (edge->node2 == node)
        {
            cout << "adjacent: " << edge->node1->id << endl;
            adjacentEdges->push_back(edge);
        }
    }
    return adjacentEdges;
}

void Graph::RemoveEdge(Vector<Edge *> &edges, Edge *edge)
{

    // get root
    Edge *root = edges.getroot();
    // iterate
    while (root != NULL)
    {
        if (edge->node1->id == root->node1->id && edge->node2->id == root->node2->id)
        {
            edges.erase(root);
            return;
        }
        root = root->next;
    }
}

void Graph::Dijkstras()
{
    while (nodes.getSize() > 0)
    {
        Node *smallest = ExtractSmallest(nodes);
        Vector<Node *> *adjacentNodes =
            AdjacentRemainingNodes(smallest);

        const int size = adjacentNodes->getSize();
        for (int i = 0; i < size; ++i)
        {
            Node *adjacent = (*adjacentNodes)[i];
            int distance = Distance(smallest, adjacent) +
                           smallest->distanceFromStart;

            if (distance < adjacent->distanceFromStart)
            {
                adjacent->distanceFromStart = distance;
                adjacent->next = smallest;
            }
        }
        delete adjacentNodes;
    }
}
void Graph::DijkstrasTest()
{
    Node *a = new Node('a');
    Node *b = new Node('b');
    Node *c = new Node('c');
    Node *d = new Node('d');
    Node *e = new Node('e');
    Node *f = new Node('f');
    Node *g = new Node('g');

    Edge *e1 = new Edge(a, c, 1);
    Edge *e2 = new Edge(a, d, 2);
    Edge *e3 = new Edge(b, c, 2);
    Edge *e4 = new Edge(c, d, 1);
    Edge *e5 = new Edge(b, f, 3);
    Edge *e6 = new Edge(c, e, 3);
    Edge *e7 = new Edge(e, f, 2);
    Edge *e8 = new Edge(d, g, 1);
    Edge *e9 = new Edge(g, f, 1);

    a->distanceFromStart = 0; // set start node
    Dijkstras();
    PrintShortestRouteTo(f);
}

int main()
{
    Graph *graph = new Graph();
    graph->DijkstrasTest();
    return 0;
}
