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

template <typename T>
struct ADJNode
{
    T data;
    ADJNode<T> *next;
    ADJNode(T data)
    {
        this->data = data;
        next = NULL;
    }
};

template <typename T>
class LinkedList
{
    ADJNode<T> *head;
    int size;

public:
    LinkedList()
    {
        head = NULL;
        size = 0;
    }
    void insert(T data, int pos)
    {
        if (pos < 0 || pos > size)
        {
            return;
        }
        ADJNode<T> *newNode = new ADJNode<T>(data);
        if (pos == 0)
        {
            newNode->next = head;
            head = newNode;
            size++;
            return;
        }
        ADJNode<T> *temp = head;
        for (int i = 0; i < pos - 1; i++)
        {
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
        size++;
    }
    void erase(int pos)
    {
        if (pos < 0 || pos >= size)
        {
            return;
        }
        if (pos == 0)
        {
            ADJNode<T> *temp = head;
            head = head->next;
            delete temp;
            size--;
            return;
        }
        ADJNode<T> *temp = head;
        for (int i = 0; i < pos - 1; i++)
        {
            temp = temp->next;
        }
        ADJNode<T> *toDelete = temp->next;
        temp->next = temp->next->next;
        delete toDelete;
        size--;
    }
    void push_back(T data)
    {
        insert(data, size);
    }
    void pop_back()
    {
        erase(size - 1);
    }
    T operator[](int i)
    {
        ADJNode<T> *temp = head;
        for (int j = 0; j < i; j++)
        {
            temp = temp->next;
        }
        return temp->data;
    }
    int getSize()
    {
        return size;
    }
    T back()
    {
        return (*this)[size - 1];
    }
    void print()
    {
        ADJNode<T> *temp = head;
        while (temp != NULL)
        {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

Vector<Edge *> edges;
Vector<Node *> nodes;

Node::Node(int id)
{
    this->id = id;
    this->count = 0;
    this->friends = 0;
    distanceFromStart = INT_MAX;
    next = NULL;
    nodes.push_back(this);
}

int Node::getId()
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
    visited = false;
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
    // cout << "\nStarting Destination: " << destination[1] << endl;
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

void Graph::printNode(Vector<Node *> &nodes)
{
    Node *root = nodes.getroot();
    while (root != NULL)
    {
        cout << root->id << " ";
        root = root->next;
    }
    cout << endl;
}

Node **node = new Node *[2500];
Edge **e = new Edge *[122500];
LinkedList<LinkedList<int> *> list;

void Graph::PopulateNodes()
{
    fstream file;
    file.open("friends.txt", ios::in);
    stringstream buffer;
    buffer << file.rdbuf();
    string content = buffer.str();

    regex nodestobe("([0-9]+)[:]");
    smatch match;
    int i = 0;

    while (regex_search(content, match, nodestobe))
    {
        int counting = 0;
        string id = match.str(0);
        regex removal("[:]");
        id = regex_replace(id, removal, "");
        // cout << endl
        //  << id << ":";

        node[i] = new Node(stoi(id));
        nodes.push_back(node[i]);

        i++;

        content = match.suffix().str();
    }

    file.close();

    fstream file1;
    file1.open("friends.txt", ios::in);
    stringstream buffer1;
    buffer1 << file1.rdbuf();
    string content1 = buffer1.str();

    regex nodestobe1("([0-9]+)[:]");
    smatch match1;
    int j = 0;
    int k = 0;

    // Edge *ee = new Edge(node[0], node[0], 0);

    while (regex_search(content1, match1, nodestobe1))
    {
        int counting = 0;

        string id = match1.str(0);
        regex removal("[:]");
        id = regex_replace(id, removal, "");
        int id1 = stoi(id);

        LinkedList<int> *ADJnode = new LinkedList<int>();
        ADJnode->push_back(id1);

        // cout << endl
        //  << id << ":";

        smatch sedge;
        regex redge("([0-9]+)[ ]");
        auto start = match1.suffix().first;
        auto end = match1.suffix().second;
        string edge = string(start, end);

        // check end of line

        smatch endline;
        regex reendl("[\\n]");
        regex_search(edge, endline, reendl);
        if (endline.size() > 0)
        {
            edge = edge.substr(0, endline.position());
        }

        while (regex_search(edge, sedge, redge) /* && sedge.size() > 0 */)
        {
            string id2 = sedge.str(0);
            regex removal2("[ ]");
            id2 = regex_replace(id2, removal2, "");
            // cout << stoi(id2) << " ";
            int id_1 = stoi(id2);
            ADJnode->push_back(id_1);
            // cout<<id_1%1000<<" ";

            e[k] = new Edge(node[j], node[(id_1 % 1000) - 1], 1);
            edges.push_back(e[k]);
            k++;
            counting++;

            edge = sedge.suffix();
        }
        list.push_back(ADJnode);
        node[j]->count = counting;
        j++;
        content1 = match1.suffix().str();
    }
}

void Graph::FIndPAth(int start, int end)
{
    cout<<"Shortest Path: "<<start<<endl;
    node[(start % 1000) - 1]->distanceFromStart = 0; // set start node

    Dijkstras();
    PrintShortestRouteTo(node[(end % 1000) - 1]);
  
}

void Graph::commonFriends(int start, int end)
{
    int index1 = start % 1000 - 1;
    int index2 = end % 1000 - 1;
    // find the common values of both indexes
    // and print them
    cout << endl;
    cout << "Common friends are:\n";
    for (int i = 0; i < list[index1]->getSize(); i++)
    {
        for (int j = 0; j < list[index2]->getSize(); j++)
        {
            if (list[index1]->operator[](i) == list[index2]->operator[](j))
            {
                cout << list[index1]->operator[](i) << " ";
            }
        }
    }
    cout << endl;
    cout << endl;
}

void Graph::maxFriends()
{
    int max = 0;
    int maxid = 0;
    for (int i = 0; i < 500; i++)
    {
        if (node[i]->count > max)
        {
            max = node[i]->count;
            maxid = node[i]->id;
        }
    }
    cout << "Maximum Friends are " << max << " of node " << node[maxid % 1000 - 1]->id << endl
         << endl;
}

int main()
{
    Graph *graph = new Graph();
    graph->PopulateNodes();

    cout << "--------Graph Implementation--------\n";
    cout << "--------Dijkstra's Algorithm--------\n";
    cout << "--------Friend Recommendation--------\n";

    while (1)
    {
        cout << "\n\nEnter 1 to find the shortest path between two friends\n";
        cout << "Enter 2 to find the common friends between two friends\n";
        cout << "Enter 3 to find the friend with the most friends\n";
        cout << "Enter 4 to exit\n";
        int choice;
        cin >> choice;

        if (choice == 1)
        {
            int start, end;
            cout << "Enter the friend start node: ";
            cin >> start;
            cout << "Enter the related friend node: ";
            cin >> end;
            graph->FIndPAth(start, end);
        }
        else if (choice == 2)
        {
            int start, end, common1, common2;
            cout << "Enter the common friend node: ";
            cin >> common1;
            cout << "Enter the common friend node: ";
            cin >> common2;
            graph->commonFriends(common1, common2);
        }
        else if (choice == 3)
        {
            graph->maxFriends();
        }
        else if (choice == 4)
        {
            break;
        }
        else
        {
            cout << "Invalid choice\n";
        }
    }

  
    return 0;
}
