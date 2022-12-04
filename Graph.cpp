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
    cout << "\nStarting Destination: " << destination->distanceFromStart << endl;
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

void Graph::DijkstrasTest(int start, int end)
{
    // regex

    fstream file;
    file.open("friends.txt", ios::in);
    stringstream buffer;
    buffer << file.rdbuf();
    string content = buffer.str();

    regex nodestobe("([0-9]+)[:]");
    smatch match;
    int i = 0;
    // Node *node = new Node(2500);
    Node **node = new Node *[2500];

    while (regex_search(content, match, nodestobe))
    {
        string id = match.str(0);
        regex removal("[:]");
        id = regex_replace(id, removal, "");
        // cout << endl
        //  << id << ":";

        if (i == 0)
        {
            node[i] = new Node(stoi(id));
            nodes.push_back(node[i]);
        }
        else
        {
            node[i] = new Node(stoi(id));
            nodes.push_back(node[i]);
        }
        i++;

        // smatch sedge;
        // regex redge("([0-9]+)[ ]");
        // auto start = match.suffix().first;
        // auto end = match.suffix().second;
        // string edge = string(start, end);

        // // check end of line

        // smatch endline;
        // regex reendl("[\\n]");
        // regex_search(edge, endline, reendl);
        // if (endline.size() > 0)
        // {
        //     edge = edge.substr(0, endline.position());
        // }

        // while (regex_search(edge, sedge, redge) /* && sedge.size() > 0 */)
        // {
        //     string id2 = sedge.str(0);
        //     regex removal2("[ ]");
        //     id2 = regex_replace(id2, removal2, "");
        //     // cout << id2 << " ";

        //     edge = sedge.suffix();
        // }

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

    Edge **e = new Edge *[1500500];
    // Edge *ee = new Edge(node[0], node[0], 0);

    while (regex_search(content1, match1, nodestobe1))
    {
        int counting = 0;

        string id = match1.str(0);
        regex removal("[:]");
        id = regex_replace(id, removal, "");
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
            // cout<<id_1%1000<<" ";

            e[k] = new Edge(node[j], node[(id_1 % 1000) - 1], 1);
            edges.push_back(e[k]);

            // e[k] = new Edge(node[j], node[id_1], 1);
            // edges.push_back(e[k]);

            // e[j] = new Edge(node[j], node[stoi(id2)-1], 1);
            // edges.push_back(e[j]);
            k++;
            counting++;

            edge = sedge.suffix();
        }
        node[j]->count = counting;
        j++;
        content1 = match1.suffix().str();
    }

    // e[0] = new Edge(node[0], node[1], 1);

    // Node *a = new Node(11);
    // Node *b = new Node(22);
    // Node *c = new Node(33);
    // Node *d = new Node(44);
    // Node *e = new Node(55);
    // Node *f = new Node(66);
    // Node *g = new Node(77);

    // Edge *e1 = new Edge(a, c, 1);
    // Edge *e2 = new Edge(a, d, 2);
    // Edge *e3 = new Edge(b, c, 2);
    // Edge *e4 = new Edge(c, d, 1);
    // Edge *e5 = new Edge(b, f, 3);
    // Edge *e6 = new Edge(c, e, 3);
    // Edge *e7 = new Edge(e, f, 2);
    // Edge *e8 = new Edge(d, g, 1);
    // Edge *e9 = new Edge(g, f, 1);

    // a->distanceFromStart = 0; // set start node

    // node->distanceFromStart = 0; // set start node
    // cout<<"\nbaba"<<nodes[0]->id<<endl;

    // node->distanceFromStart = 0; // set start node
    node[(start % 1000) - 1]->distanceFromStart = 0; // set start node

    Dijkstras();
    // cout << "\nbla" << node[0]->id << endl;
    // cout << "\nbla" << node[340]->id << endl;
    // cout << "\nebla" << e[0]->node1->id << endl;
    // printNode(nodes);

    PrintShortestRouteTo(node[(end % 1000) - 1]);
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
    cout << "Maximum Friends are " << max << " of node " << node[maxid%1000-1]->id << endl;

    file1.close();

    fstream file2;
    file2.open("friends.txt", ios::in);
    stringstream buffer2;
    buffer2 << file2.rdbuf();
    string content2 = buffer2.str();

    regex nodestobe2("([0-9]+)[:]");
    smatch match2;
    int j1 = 0;
    // int k = 0;

    while (regex_search(content2, match2, nodestobe2))
    {
        int counting = 0;
        int friendscount = 0;

        string id = match2.str(0);
        regex removal("[:]");
        id = regex_replace(id, removal, "");
        // cout << endl
        //  << id << ":";

        smatch sedge;
        regex redge("([0-9]+)[ ]");
        auto start = match2.suffix().first;
        auto end = match2.suffix().second;
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
            node[j1]->friends += node[(id_1 % 1000) - 1]->count;
            k++;

            edge = sedge.suffix();
        }
        j1++;
        content2 = match2.suffix().str();
    }

    cout<<"Biggest Friends Circle is ";
    int max2 = 0;
    int maxid2 = 0;

    for (int i = 0; i < 500; i++)
    {
        if (node[i]->friends > max2)
        {
            // max = node[i]->distanceFromStart;
            max2 = node[i]->friends;
            // cout << node[i]->count << " " << max << endl;
            maxid2 = node[i]->id;
        }
    }
    cout<<max2<<" of node "<<node[maxid2%1000-1]->id<<endl;    
    
    

}


int main()
{
    Graph *graph = new Graph();
    int start = 0;
    int end = 0;
    cout << "Enter the friend start node: ";
    cin >> start;
    cout << "Enter the related friend node: ";
    cin >> end;
    graph->DijkstrasTest(start, end);
    // graph->BiggestPath();
    return 0;
}
