/***********************
 **  Ibraheem Rehman  **
 **  SE-Q    21i-1102 **
 ***********************/

#include <climits>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <regex>
using namespace std;
int MAX = 4;
int MIN = 2;

string FILENAME;

struct Id
{
    string name;
    string reference;
};
struct Name
{
    string name;
    string reference;
};

struct Dob
{
    string name;
    string reference;
};

struct Gender
{
    string name;
    string reference;
};

struct Doj
{
    string name;
    string reference;
};

struct Address
{
    string name;
    string reference;
};

struct Qualification
{
    string name;
    string reference;
};

// B+ Tree Node
template <typename T>
class Node
{
    bool IS_LEAF;
    T *key;
    int size;
    Node **ptr;

public:
    Node()
    {
        key = new T[MAX];
        ptr = new Node<T> *[MAX + 1];
    }
    template <typename U>
    friend class BPTree;
};

// BP tree
template <class T>
class BPTree
{
    Node<T> *root;
    int nodecount;

public:
    BPTree()
    {
        root = NULL;
        nodecount = 0;
    }
    void insertInternal(string x, string ref, Node<T> *cursor, Node<T> *child)
    {

        if (cursor->size < MAX)
        {
            int i = 0;
            // while (x > cursor->key[i] && i < cursor->size)
            while (x.compare(cursor->key[i].name) > 0 && i < cursor->size)
                i++;
            for (int j = cursor->size; j > i; j--)
            {
                cursor->key[j] = cursor->key[j - 1];
            }
            for (int j = cursor->size + 1; j > i + 1; j--)
            {
                cursor->ptr[j] = cursor->ptr[j - 1];
            }
            // cursor->key[i] = x;
            cursor->key[i].name = x;
            cursor->key[i].reference = ref;
            cursor->size++;
            cursor->ptr[i + 1] = child;
        }
        else
        {
            Node<T> *newInternal = new Node<T>;
            T virtualNode[MAX + 1];
            Node<T> *virtualPtr[MAX + 2];
            for (int i = 0; i < MAX; i++)
            {
                virtualNode[i] = cursor->key[i];
            }
            for (int i = 0; i < MAX + 1; i++)
            {
                virtualPtr[i] = cursor->ptr[i];
            }
            int i = 0, j;
            // while (x > virtualNode[i] && i < MAX)
            while (x.compare(virtualNode[i].name) > 0 && i < MAX)
                i++;
            for (int j = MAX; j > i; j--)
            {
                virtualNode[j] = virtualNode[j - 1];
            }

            // virtualKey[i] = x;
            virtualNode[i].name = x;
            virtualNode[i].reference = ref;
            for (int j = MAX + 1; j > i + 1; j--)
            {
                virtualPtr[j] = virtualPtr[j - 1];
            }
            virtualPtr[i + 1] = child;
            newInternal->IS_LEAF = false;
            cursor->size = (MAX + 1) / 2;
            newInternal->size = MAX - (MAX + 1) / 2;
            for (i = 0, j = cursor->size + 1; i < newInternal->size; i++, j++)
            {
                newInternal->key[i] = virtualNode[j];
            }
            for (i = 0, j = cursor->size + 1; i < newInternal->size + 1; i++, j++)
            {
                newInternal->ptr[i] = virtualPtr[j];
            }
            if (cursor == root)
            {
                Node<T> *newRoot = new Node<T>;
                newRoot->key[0] = cursor->key[cursor->size];
                newRoot->ptr[0] = cursor;
                newRoot->ptr[1] = newInternal;
                newRoot->IS_LEAF = false;
                newRoot->size = 1;
                root = newRoot;
            }
            else
            {
                insertInternal(cursor->key[cursor->size].name, cursor->key[cursor->size].reference, findParent(root, cursor), newInternal);
            }
        }
    }

    Node<T> *findParent(Node<T> *cursor, Node<T> *child)
    {
        Node<T> *parent;
        if (cursor->IS_LEAF || (cursor->ptr[0])->IS_LEAF)
        {
            return NULL;
        }
        for (int i = 0; i < cursor->size + 1; i++)
        {
            if (cursor->ptr[i] == child)
            {
                parent = cursor;
                return parent;
            }
            else
            {
                parent = findParent(cursor->ptr[i], child);
                if (parent != NULL)
                    return parent;
            }
        }
        return parent;
    }

    void insert(string x, string reference)
    {
        cout << x << " " << reference << endl;
        if (root == NULL)
        {
            root = new Node<T>;
            root->key[0].name = x;
            root->key[0].reference = reference;
            root->IS_LEAF = true;
            root->size = 1;
        }
        else
        {
            Node<T> *cursor = root;
            Node<T> *parent;
            while (cursor->IS_LEAF == false)
            {
                // cout << "check" << endl;
                parent = cursor;
                for (int i = 0; i < cursor->size; i++)
                {
                    // if (x < cursor->key[i])

                    if (x.compare(cursor->key[i].name) < 0)
                    {
                        cursor = cursor->ptr[i];
                        break;
                    }
                    if (i == cursor->size - 1)
                    {
                        cursor = cursor->ptr[i + 1];
                        break;
                    }
                }
            }
            if (cursor->size < MAX)
            {
                int i = 0;
                // while (x > cursor->key[i] && i < cursor->size)
                // cout<<x<<" "<<cursor->key[i].name<<endl;
                // cout<<"check"<<endl;
                while (x.compare(cursor->key[i].name) > 0 && i < cursor->size)
                    i++;
                for (int j = cursor->size; j > i; j--)
                {
                    cursor->key[j] = cursor->key[j - 1];
                }
                cursor->key[i].name = x;
                cursor->key[i].reference = reference;
                cursor->size++;
                cursor->ptr[cursor->size] = cursor->ptr[cursor->size - 1];
                cursor->ptr[cursor->size - 1] = NULL;
            }
            else
            {
                Node<T> *newLeaf = new Node<T>;

                T virtualNode[MAX + 1];

                for (int i = 0; i < MAX; i++)
                {
                    virtualNode[i].name = cursor->key[i].name;
                    virtualNode[i].reference = cursor->key[i].reference;
                    // virtualNode[i] = cursor->key[i].name;
                    // virtualNode[i] = cursor->key[i].reference;
                }
                // cout<<"check"<<endl;
                int i = 0;
                int j;
                // while (x > virtualNode[i] && i < MAX)
                while (x.compare(virtualNode[i].name) > 0 && i < MAX)
                {
                    i++;
                    // cout << "check" << endl;
                }

                // for (int j = MAX + 1; j > i; j--)
                for (int j = MAX; j > i; j--)
                {
                    // cout << "check" << endl;
                    virtualNode[j] = virtualNode[j - 1];
                }
                // virtualNode[i] = x;
                virtualNode[i].name = x;
                virtualNode[i].reference = reference;
                newLeaf->IS_LEAF = true;
                cursor->size = (MAX + 1) / 2;
                newLeaf->size = MAX + 1 - (MAX + 1) / 2;
                cursor->ptr[cursor->size] = newLeaf;
                newLeaf->ptr[newLeaf->size] = cursor->ptr[MAX];
                cursor->ptr[MAX] = NULL;
                for (i = 0; i < cursor->size; i++)
                {
                    cursor->key[i] = virtualNode[i];
                    // cursor->key[i].name = virtualNode[i];
                }
                for (i = 0, j = cursor->size; i < newLeaf->size; i++, j++)
                {
                    // newLeaf->key[i].name = virtualNode[j];
                    newLeaf->key[i] = virtualNode[j];
                }
                if (cursor == root)
                {
                    // cout << "check" << endl;
                    Node<T> *newRoot = new Node<T>;

                    newRoot->key[0].name = newLeaf->key[0].name;
                    newRoot->key[0].reference = newLeaf->key[0].reference;
                    newRoot->ptr[0] = cursor;
                    newRoot->ptr[1] = newLeaf;
                    newRoot->IS_LEAF = false;
                    newRoot->size = 1;
                    root = newRoot;
                }
                else
                {
                    // insertInternal(newLeaf->key[0].reference, parent, newLeaf);
                    insertInternal(newLeaf->key[0].name, newLeaf->key[0].reference, parent, newLeaf);
                }
            }
        }
    }

    void deleteInternal(string x, Node<T> *cursor)
    {
        int i = 0;
        // while (x > cursor->key[i].name && i < cursor->size)
        while (x.compare(cursor->key[i].name) > 0 && i < cursor->size)
        {
            i++;
        }
        if (x == cursor->key[i].name)
        {
            if (cursor->IS_LEAF)
            {
                for (int j = i; j < cursor->size - 1; j++)
                {
                    cursor->key[j] = cursor->key[j + 1];
                }
                cursor->size--;
                return;
            }
            else
            {
                Node<T> *left = cursor->ptr[i];
                Node<T> *right = cursor->ptr[i + 1];
                if (left->size > MIN)
                {
                    Node<T> *temp = left;
                    while (temp->IS_LEAF == false)
                    {
                        temp = temp->ptr[temp->size];
                    }
                    cursor->key[i] = temp->key[temp->size - 1];
                    deleteInternal(temp->key[temp->size - 1].name, temp);
                }
                else if (right->size > MIN)
                {
                    Node<T> *temp = right;
                    while (temp->IS_LEAF == false)
                    {
                        temp = temp->ptr[0];
                    }
                    cursor->key[i] = temp->key[0];
                    deleteInternal(temp->key[0].name, temp);
                }
                else
                {
                    for (int j = i; j < cursor->size - 1; j++)
                    {
                        cursor->key[j] = cursor->key[j + 1];
                    }
                    for (int j = i + 1; j < cursor->size; j++)
                    {
                        cursor->ptr[j] = cursor->ptr[j + 1];
                    }
                    cursor->size--;
                    left->key[left->size] = cursor->key[i];
                    left->size++;
                    for (int j = 0; j < right->size; j++)
                    {
                        left->key[left->size] = right->key[j];
                        left->size++;
                    }
                    for (int j = 0; j < right->size + 1; j++)
                    {
                        left->ptr[left->size] = right->ptr[j];
                        left->size++;
                    }
                    delete right;
                    deleteInternal(cursor->key[i].name, cursor);
                }
            }
        }
        else
        {
            if (cursor->IS_LEAF)
            {
                cout << "NOT FOUND" << endl;
                return;
            }
            bool flag = ((i == cursor->size) ? true : false);
            Node<T> *child = cursor->ptr[i];
            if (child->size == MIN)
            {
                if (i != cursor->size && cursor->ptr[i + 1]->size > MIN)
                {
                    Node<T> *sibling = cursor->ptr[i + 1];
                    child->key[child->size] = cursor->key[i];
                    child->size++;
                    cursor->key[i] = sibling->key[0];
                    for (int j = 0; j < sibling->size - 1; j++)
                    {
                        sibling->key[j] = sibling->key[j + 1];
                    }
                    if (sibling->IS_LEAF == false)
                    {
                        child->ptr[child->size] = sibling->ptr[0];
                        for (int j = 0; j < sibling->size; j++)
                        {
                            sibling->ptr[j] = sibling->ptr[j + 1];
                        }
                    }
                    sibling->size--;
                }
                else if (i != 0 && cursor->ptr[i - 1]->size > MIN)
                {
                    Node<T> *sibling = cursor->ptr[i - 1];
                    for (int j = child->size - 1; j >= 0; j--)
                    {
                        child->key[j + 1] = child->key[j];
                    }
                    if (child->IS_LEAF == false)
                    {
                        for (int j = child->size; j >= 0; j--)
                        {
                            child->ptr[j + 1] = child->ptr[j];
                        }
                    }
                    child->key[0] = cursor->key[i - 1];
                    if (child->IS_LEAF == false)
                    {
                        child->ptr[0] = sibling->ptr[sibling->size];
                    }
                    cursor->key[i - 1] = sibling->key[sibling->size - 1];
                    child->size++;
                    sibling->size--;
                }
                else
                {
                    if (i != cursor->size)
                    {
                        Node<T> *sibling = cursor->ptr[i + 1];
                        child->key[child->size] = cursor->key[i];
                        for (int j = 0; j < sibling->size; j++)
                        {
                            child->key[child->size + 1 + j] = sibling->key[j];
                        }
                        if (child->IS_LEAF == false)
                        {
                            for (int j = 0; j <= sibling->size; j++)
                            {
                                child->ptr[child->size + 1 + j] = sibling->ptr[j];
                            }
                        }
                        child->size += sibling->size + 1;
                        for (int j = i + 1; j < cursor->size; j++)
                        {
                            cursor->key[j - 1] = cursor->key[j];
                        }
                        for (int j = i + 2; j <= cursor->size; j++)
                        {
                            cursor->ptr[j - 1] = cursor->ptr[j];
                        }
                        cursor->size--;
                        delete sibling;
                    }
                    else
                    {
                        Node<T> *sibling = cursor->ptr[i - 1];
                        for (int j = 0; j < child->size; j++)
                        {
                            sibling->key[sibling->size + 1 + j] = child->key[j];
                        }
                        if (child->IS_LEAF == false)
                        {
                            for (int j = 0; j <= child->size; j++)
                            {
                                sibling->ptr[sibling->size + 1 + j] = child->ptr[j];
                            }
                        }
                        sibling->size += child->size + 1;
                        cursor->size--;
                        delete child;
                    }
                }
            }
            deleteInternal(x, cursor->ptr[i]);
        }
    }

    void deletee(string x)
    {
        Node<T> *cursor = root;
        Node<T> *parent;
        int i;
        while (cursor->IS_LEAF == false)
        {
            parent = cursor;
            for (i = 0; i < cursor->size; i++)
            {
                if (x < cursor->key[i].name)
                {
                    cursor = cursor->ptr[i];
                    break;
                }
                if (i == cursor->size - 1)
                {
                    cursor = cursor->ptr[i + 1];
                    break;
                }
            }
        }
        for (i = 0; i < cursor->size; i++)
        {
            if (x == cursor->key[i].name)
            {
                break;
            }
        }
        if (i == cursor->size)
        {
            cout << "Not found" << endl;
            return;
        }
        for (int j = i; j < cursor->size - 1; j++)
        {
            cursor->key[j] = cursor->key[j + 1];
        }
        cursor->size--;
        if (cursor->size >= (MAX + 1) / 2)
        {
            return;
        }
        else
        {
            if (cursor == root)
            {
                if (cursor->size == 0)
                {
                    root = cursor->ptr[0];
                }
                return;
            }
            int flag = 0;
            for (i = 0; i < parent->size + 1; i++)
            {
                if (parent->ptr[i] == cursor)
                {
                    flag = 1;
                    break;
                }
            }
            if (flag == 0)
            {
                i--;
            }
            if (i != 0)
            {
                Node<T> *leftSibling = parent->ptr[i - 1];
                if (leftSibling->size >= (MAX + 1) / 2 + 1)
                {
                    for (int j = cursor->size; j > 0; j--)
                    {
                        cursor->key[j] = cursor->key[j - 1];
                    }
                    cursor->key[0] = leftSibling->key[leftSibling->size - 1];
                    cursor->size++;
                    leftSibling->size--;
                    parent->key[i - 1] = cursor->key[0];
                    return;
                }
            }
            if (i != parent->size)
            {
                Node<T> *rightSibling = parent->ptr[i + 1];
                if (rightSibling->size >= (MAX + 1) / 2 + 1)
                {
                    cursor->key[cursor->size] = rightSibling->key[0];
                    cursor->size++;
                    rightSibling->size--;
                    for (int j = 0; j < rightSibling->size; j++)
                    {
                        rightSibling->key[j] = rightSibling->key[j + 1];
                    }
                    parent->key[i] = rightSibling->key[0];
                    return;
                }
            }
            if (i != 0)
            {
                Node<T> *leftSibling = parent->ptr[i - 1];
                leftSibling->key[leftSibling->size] = parent->key[i - 1];
                leftSibling->size++;
                for (int j = 0; j < cursor->size; j++)
                {
                    leftSibling->key[leftSibling->size] = cursor->key[j];
                    leftSibling->size++;
                }
                leftSibling->ptr[leftSibling->size] = cursor->ptr[cursor->size];
                for (int j = i - 1; j < parent->size - 1; j++)
                {
                    parent->key[j] = parent->key[j + 1];
                    parent->ptr[j + 1] = parent->ptr[j + 2];
                }
                parent->size--;
                if (parent->size >= (MAX + 1) / 2)
                {
                    return;
                }
                else
                {
                    deleteInternal(parent->key[0].name, parent);
                }
            }
            if (i != parent->size)
            {
                Node<T> *rightSibling = parent->ptr[i + 1];
                cursor->key[cursor->size] = parent->key[i];
                cursor->size++;
                for (int j = 0; j < rightSibling->size; j++)
                {
                    cursor->key[cursor->size] = rightSibling->key[j];
                    cursor->size++;
                }
                cursor->ptr[cursor->size] = rightSibling->ptr[rightSibling->size];
                for (int j = i; j < parent->size - 1; j++)
                {
                    parent->key[j] = parent->key[j + 1];
                    parent->ptr[j + 1] = parent->ptr[j + 2];
                }
                parent->size--;
                if (parent->size >= (MAX + 1) / 2)
                {
                    return;
                }
                else
                {
                    deleteInternal(parent->key[0].name, parent);
                }
            }
        }
    }

    void populate_from_file(string filename)
    {

        string type = typeid(T).name();
        // regex for type
        smatch stype;
        regex type_regex("([a-zA-Z]+)");
        regex_search(type, stype, type_regex);
        type = stype.str(0);
        // cout<<type<<endl;

        fstream file;
        file.open(filename, ios::in);
        if (!file)
        {
            cout << "File not found" << endl;
            return;
        }
        stringstream buffer;
        buffer << file.rdbuf();
        string str = buffer.str();
        // cout << str;

        regex rid("([0-9]+).*");
        smatch match;
        int count = 1;
        nodecount = 1;
        cout << "check1" << nodecount << endl;

        while (regex_search(str, match, rid))
        {

            smatch sfname;
            regex rfname("([A-Z])");
            regex_search(filename, sfname, rfname);
            string fname = sfname.str(0);

            smatch sfnum;
            regex rfnum("File([0-9]+)");
            regex_search(filename, sfnum, rfnum);
            string fnum = sfnum.str(0);
            // remove file from string
            regex removalf("File0");
            fnum = regex_replace(fnum, removalf, "");

            smatch sid;
            regex rid("([0-9]+)");
            regex_search(str, sid, rid);
            string Id = sid.str(0);

            // string reference = fname + fnum + "L" + to_string(Id);
            string reference = fname + fnum + "L" + to_string(count);
            // insert(Id, reference);

            if (type == "Id")
            {
                insert(Id, reference);
            }

            else if (type == "Name")
            {
                smatch sname;
                regex rname("(\t)((.+)(?=(\t)([0-9]{1,2}(-|/)[A-Z]{1}[a-z]{2}(-|/)([0-9]{2}))(\t)(M|F)))");
                regex_search(str, sname, rname);
                regex removal("(\t)");
                string Name = regex_replace(sname.str(0), removal, "");
                // string Name = sname.str(0);

                insert(Name, reference);
            }

            if (type == "Dob")
            {
                smatch sdob;
                regex rdob("([0-9]+)(-|/)([A-Za-z]+)(-|/)([0-9]+)");
                regex_search(str, sdob, rdob);
                string Dob = sdob.str(0);

                insert(Dob, reference);
            }

            if (type == "Gender")
            {
                smatch sgender;
                regex rgender("(\t)([A-Za-z])(\t)");
                regex_search(str, sgender, rgender);
                regex removall("\t"); // Removing tab space from the string
                string Gender = sgender.str(0);
                Gender = regex_replace(Gender, removall, "");

                insert(Gender, reference);
            }

            if (type == "Doj")
            {

                smatch sdoj;
                regex rdoj("(M|F)(\t)([0-9]+)(-)([A-Za-z]+)(-)([0-9]+)");
                regex_search(str, sdoj, rdoj);
                regex removall2("M|F"); // Removing Gender from the string
                string Doj = sdoj.str(0);
                Doj = regex_replace(Doj, removall2, "");
                regex removall2_2("\t"); // Removing tab space from the string
                Doj = regex_replace(Doj, removall2_2, "");

                insert(Doj, reference);
            }

            if (type == "Address")
            {
                smatch saddress;
                regex raddress("(\t)([A-Za-z0-9][#]+).*|([A-Za-z]+[.]( )[#]+).*|(\t)([A-Za-z]+( )[A-Za-z]+[.]( )[0-9]+).*|([A-Za-z][.]+)( )([A-Za-z][.]+).*|([A-Za-z]+[.]( )[A-Za-z]+[.]( )+).*|([A-Za-z]( )[A-Za-z]+[.]+).*");
                regex_search(str, saddress, raddress);
                string Address = saddress.str(0);
                regex removal("FSc|A-Level|Fsc|F.Sc.|HSSC");
                Address = regex_replace(Address, removal, "");
                regex removall3("\t"); // Removing tab space from the string
                Address = regex_replace(Address, removall3, "");
                insert(Address, reference);
            }

            if (type == "Qualification")
            {
                smatch squalification;
                regex rqualification("(\t)([A-Za-z]+)(-Level)|(FSc)|(Fsc)|(F.Sc.)|(HSSC)|( )([A-Za-z]+)(-Level)|(FSc)|(Fsc)|(F.Sc.)|(HSSC)|( )([A-Za-z]+)(-Level)|(FSc)|(Fsc)|(F.Sc.)|(HSSC)|( )([A-Za-z]+)(-Level)|(FSc)|(Fsc)|(F.Sc.)|(HSSC)|([A])([ ]([level]+))");
                regex_search(str, squalification, rqualification);
                string Qualification = squalification.str(0);

                insert(Qualification, reference);
            }
            str = match.suffix().str();
            count++;
            nodecount = count;
        }
    }

    Node<T> *getRoot()
    {
        return root;
    }
    void search(string x)
    {
        if (root == NULL)
        {
            cout << "Tree is empty\n";
        }
        else
        {
            int i = 0;
            fstream file;
            file.open(FILENAME, ios::in);
            string ss;
            Node<T> *cursor = root;
            while (cursor->IS_LEAF == false)
            {
                for (int i = 0; i < cursor->size; i++)
                {
                    // if (x < cursor->key[i].name) {
                    // cout<<x<<" "<<cursor->key[i].name<<endl;
                    if (x.compare(cursor->key[i].name) < 0)
                    {
                        cursor = cursor->ptr[i];
                        break;
                    }
                    if (i == cursor->size - 1)
                    {
                        cursor = cursor->ptr[i + 1];
                        break;
                    }
                }
            }
            for (int i = 0; i < cursor->size; i++)
            {
                if (cursor->key[i].name == x)
                {
                    // cout << "Found\n";

                    string str;
                    // cout << "bla" << i << endl;
                    cout << "\n--------Data found--------" << endl;
                    cout << "Key to be searched: ";
                    cout << cursor->key[i].name << " ";
                    cout << cursor->key[i].reference << endl;

                    string line = cursor->key[i].reference;

                    smatch sfnum;
                    regex rfnum("L([0-9]+)");
                    regex_search(line, sfnum, rfnum);
                    regex removal("L");
                    string line_actual = sfnum.str(0);
                    line_actual = regex_replace(line_actual, removal, "");
                    int intline = stoi(line_actual);

                    GotoLine(file, intline + 1);
                    getline(file, str);
                    cout << str << endl;
                    return;
                }
            }
            cout << "Not found\n";
        }
    }

    void search2(string x, Node<T> *current)
    {
        fstream file;
        file.open(FILENAME, ios::in);
        string ss;
        if (root == NULL)
        {
            cout << "Tree is empty\n";
        }
        else
        {
            if (current->IS_LEAF == false)
            {
                for (int i = 0; i <= current->size; i++)
                {
                    search2(x, current->ptr[i]);
                }
            }
            else
            {
                for (int i = 0; i < current->size; i++)
                {
                    if (current->key[i].name == x)
                    {
                        cout << "--------Data found--------\n";
                        // cout << current->key[i].name << " " << current->key[i].reference << endl;

                        string str;
                        string line = current->key[i].reference;

                        smatch sfnum;
                        regex rfnum("L([0-9]+)");
                        regex_search(line, sfnum, rfnum);
                        regex removal("L");
                        string line_actual = sfnum.str(0);
                        line_actual = regex_replace(line_actual, removal, "");
                        int intline = stoi(line_actual);

                        GotoLine(file, intline);
                        getline(file, str);
                        cout << str << endl;
                    }
                }

                return;
            }
        }
        cout << endl;
    }

    void RangedSearch(string x, int gt, Node<T> *current)
    {
        fstream file;
        file.open(FILENAME, ios::in);
        string ss;
        if (root == NULL)
        {
            cout << "Tree is empty\n";
        }
        else
        {
            if (current->IS_LEAF == false)
            {
                for (int i = 0; i <= current->size; i++)
                {
                    RangedSearch(x, gt, current->ptr[i]);
                }
            }
            else
            {
                for (int i = 0; i < current->size; i++)
                {
                    if (gt)
                    {
                        if (current->key[i].name >= x)
                        {
                            cout << "--------Data found--------\n";
                            // cout << current->key[i].name << " " << current->key[i].reference << endl;

                            string str;
                            string line = current->key[i].reference;

                            smatch sfnum;
                            regex rfnum("L([0-9]+)");
                            regex_search(line, sfnum, rfnum);
                            regex removal("L");
                            string line_actual = sfnum.str(0);
                            line_actual = regex_replace(line_actual, removal, "");
                            int intline = stoi(line_actual);

                            GotoLine(file, intline);
                            getline(file, str);
                            cout << str << endl;
                        }
                    }
                    else
                    {
                        if (current->key[i].name.compare(x) <= 0)
                        {
                            cout << "--------Data found--------\n";
                            // cout << current->key[i].name << " " << current->key[i].reference << endl;

                            string str;
                            string line = current->key[i].reference;

                            smatch sfnum;
                            regex rfnum("L([0-9]+)");
                            regex_search(line, sfnum, rfnum);
                            regex removal("L");
                            string line_actual = sfnum.str(0);
                            line_actual = regex_replace(line_actual, removal, "");
                            int intline = stoi(line_actual);

                            GotoLine(file, intline);
                            getline(file, str);
                            cout << str << endl;
                        }
                    }
                }

                return;
            }
        }
        cout << endl;
    }

    fstream &GotoLine(std::fstream &file, unsigned int num)
    {
        file.seekg(std::ios::beg);
        for (int i = 0; i < num - 1; ++i)
        {
            file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        return file;
    }
    void display(Node<T> *cursor)
    {
        if (cursor != NULL)
        {
            for (int i = 0; i < cursor->size; i++)
            {
                cout << cursor->key[i].name << " " << cursor->key[i].reference << " \n";
            }
            cout << "\n";
            if (cursor->IS_LEAF != true)
            {
                for (int i = 0; i < cursor->size + 1; i++)
                {
                    display(cursor->ptr[i]);
                }
            }
        }
    }

    void insert_in_file(string filename, int id, string name, string dob, string gender, string doj, string adderess, string qualifi)
    {
        fstream file;
        file.open(filename, ios::app);
        // for reference
        smatch sfname;
        regex rfname("([A-Z])");
        regex_search(filename, sfname, rfname);
        string fname = sfname.str(0);

        smatch sfnum;
        regex rfnum("File([0-9]+)");
        regex_search(filename, sfnum, rfnum);
        string fnum = sfnum.str(0);
        // remove file from string
        regex removalf("File0");
        fnum = regex_replace(fnum, removalf, "");

        file << (nodecount - 1) << "\t" << name << "\t" << dob << "\t" << gender << "\t" << doj << "\t" << adderess << "\t" << qualifi << endl;

        string reference = fname + fnum + "L" + to_string(nodecount);
        string type = typeid(T).name();
        // regex for type
        smatch stype;
        regex type_regex("([a-zA-Z]+)");
        regex_search(type, stype, type_regex);
        type = stype.str(0);
        if (type == "Id")
            insert(to_string(nodecount + 1), reference);
        else if (type == "Name")
        {
            insert(name, reference);
        }
        else if (type == "Dob")
        {
            insert(dob, reference);
        }
        else if (type == "Gender")
            insert(gender, reference);
        else if (type == "Doj")
            insert(doj, reference);
        else if (type == "Address")
            insert(adderess, reference);
        else if (type == "Qualification")
            insert(qualifi, reference);
        file.close();
    }

    void delete_from_file(string deleteid)
    {
        deletee(deleteid);
        string deleteline;
        string line;
        fstream file;
        file.open(FILENAME, ios::in);
        fstream temp;
        temp.open("temp.txt", ios::out);
        while (getline(file, line))
        {
            line.find(deleteid);
            if (line.find(deleteid) == string::npos)
            {
                temp << line << endl;
            }
        }
        file.close();
        temp.close();
        remove("Fall2022DSDataFile004.txt");
        rename("temp.txt", "Fall2022DSDataFile004.txt");
    }
    int getnodecount()
    {
        return nodecount;
    }
};

int main()
{
    // BPTree<Id> btree;
    std::cout << "Enter the filenumber: ";
    int filenumber;
    std::cin >> filenumber;
    FILENAME = "Fall2022DSDataFile00" + to_string(filenumber) + ".txt";
    // cout << FILENAME << endl;
    // btree.populate_from_file(FILENAME);

    while (1)
    {
        cout << "Choose B Tree Type: ";
        cout << "\n1. Id";
        cout << "\n2. Name";
        cout << "\n3. Date of Birth";
        cout << "\n4. Gender";
        cout << "\n5. Date of Joining";
        cout << "\n6. Address";
        cout << "\n7. Qualification";
        cout << "\n8. Exit";

        int choice;
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            BPTree<Id> btree;
            btree.populate_from_file(FILENAME);
            while (1)
            {
                cout << "\n1. Insert";
                cout << "\n2. Delete";
                cout << "\n3. Search";
                cout << "\n4. Ranged Search";
                cout << "\n5. Display";
                cout << "\n6. Exit";
                int choice;
                cin >> choice;
                switch (choice)
                {
                case 1:
                {
                    cout << "Enter the id: ";
                    int id;
                    cin >> id;
                    cout << "Enter the name: ";
                    string name;
                    cin >> name;
                    cout << "Enter the dob: ";
                    string dob;
                    cin >> dob;
                    cout << "Enter the Gender: ";
                    string gender;
                    cin >> gender;
                    cout << "Enter the doj: ";
                    string doj;
                    cin >> doj;
                    cout << "Enter the address: ";
                    string address;
                    cin >> address;
                    cout << "Enter the qualification: ";
                    string qualifi;
                    cin >> qualifi;
                    btree.insert_in_file(FILENAME, id, name, dob, gender, doj, address, qualifi);
                    break;
                }
                case 2:
                {
                    string nama;
                    char ch[100];

                    cout << "Enter the string to search: \n";
                    scanf(" %[^\n]s", ch);
                    // cin.getline(ch, 100);
                    btree.delete_from_file(ch);
                    break;
                }
                case 3:
                {
                    cout << "Enter the string to search: ";
                    string id;
                    cin >> id;
                    btree.search2(id, btree.getRoot());
                    break;
                }
                case 4:
                {
                    cout << "Greater than: 0/1";
                    int gt;
                    cin >> gt;
                    cout << "Enter the string to search: ";
                    string id;
                    cin >> id;

                    btree.RangedSearch(id, gt, btree.getRoot());
                    break;
                }
                case 5:
                {
                    btree.display(btree.getRoot());
                    break;
                }
                case 6:
                {
                    exit(0);
                    break;
                }
                default:
                    break;
                }
            }
            break;
        }
        case 2:
        {
            BPTree<Name> btree;
            btree.populate_from_file(FILENAME);
            while (1)
            {
                cout << "\n1. Insert";
                cout << "\n2. Delete";
                cout << "\n3. Search";
                cout << "\n4. Display";
                cout << "\n5. Exit";
                int choice;
                cin >> choice;
                switch (choice)
                {
                case 1:
                {
                    cout << "Enter the id: ";
                    int id;
                    cin >> id;
                    cout << "Enter the name: ";
                    string name;
                    cin >> name;
                    cout << "Enter the dob: ";
                    string dob;
                    cin >> dob;
                    cout << "Enter the Gender: ";
                    string gender;
                    cin >> gender;
                    cout << "Enter the doj: ";
                    string doj;
                    cin >> doj;
                    cout << "Enter the address: ";
                    string address;
                    cin >> address;
                    cout << "Enter the qualification: ";
                    string qualifi;
                    cin >> qualifi;
                    btree.insert_in_file(FILENAME, id, name, dob, gender, doj, address, qualifi);
                    break;
                }
                case 2:
                {
                    string nama;
                    char ch[100];

                    cout << "Enter the string to search: \n";
                    scanf(" %[^\n]s", ch);
                    // cin.getline(ch, 100);
                    btree.delete_from_file(ch);
                    break;
                }
                case 3:
                {
                    string nama;
                    char ch[100];

                    cout << "Enter the string to search: \n";
                    scanf(" %[^\n]s", ch);
                    // cin.getline(ch, 100);
                    btree.search2(ch, btree.getRoot());
                    break;
                }
                case 4:
                {
                    btree.display(btree.getRoot());
                    break;
                }
                case 5:
                {
                    exit(0);
                    break;
                }
                default:
                    break;
                }
            }
            break;
        }
        case 3:
        {
            BPTree<Dob> btree;
            btree.populate_from_file(FILENAME);
            while (1)
            {
                cout << "\n1. Insert";
                cout << "\n2. Delete";
                cout << "\n3. Search";
                cout << "\n4. Display";
                cout << "\n5. Exit";
                int choice;
                cin >> choice;
                switch (choice)
                {
                case 1:
                {
                    cout << "Enter the id: ";
                    int id;
                    cin >> id;
                    cout << "Enter the name: ";
                    string name;
                    cin >> name;
                    cout << "Enter the dob: ";
                    string dob;
                    cin >> dob;
                    cout << "Enter the Gender: ";
                    string gender;
                    cin >> gender;
                    cout << "Enter the doj: ";
                    string doj;
                    cin >> doj;
                    cout << "Enter the address: ";
                    string address;
                    cin >> address;
                    cout << "Enter the qualification: ";
                    string qualifi;
                    cin >> qualifi;
                    btree.insert_in_file(FILENAME, id, name, dob, gender, doj, address, qualifi);
                    break;
                }
                case 2:
                {
                    string nama;
                    char ch[100];

                    cout << "Enter the string to search: \n";
                    scanf(" %[^\n]s", ch);
                    // cin.getline(ch, 100);
                    btree.delete_from_file(ch);
                    break;
                }
                case 3:
                {
                    string nama;
                    char ch[100];

                    cout << "Enter the string to search: \n";
                    scanf(" %[^\n]s", ch);
                    // cin.getline(ch, 100);
                    btree.search2(ch, btree.getRoot());
                    break;
                }
                case 4:
                {
                    btree.display(btree.getRoot());
                    break;
                }
                case 5:
                {
                    exit(0);
                    break;
                }
                default:
                    break;
                }
            }
            break;
        }
        case 4:
        {
            BPTree<Gender> btree;
            btree.populate_from_file(FILENAME);
            while (1)
            {
                cout << "\n1. Insert";
                cout << "\n2. Delete";
                cout << "\n3. Search";
                cout << "\n4. Display";
                cout << "\n5. Exit";
                int choice;
                cin >> choice;
                switch (choice)
                {
                case 1:
                {
                    cout << "Enter the id: ";
                    int id;
                    cin >> id;
                    cout << "Enter the name: ";
                    string name;
                    cin >> name;
                    cout << "Enter the dob: ";
                    string dob;
                    cin >> dob;
                    cout << "Enter the Gender: ";
                    string gender;
                    cin >> gender;
                    cout << "Enter the doj: ";
                    string doj;
                    cin >> doj;
                    cout << "Enter the address: ";
                    string address;
                    cin >> address;
                    cout << "Enter the qualification: ";
                    string qualifi;
                    cin >> qualifi;
                    btree.insert_in_file(FILENAME, id, name, dob, gender, doj, address, qualifi);
                    break;
                }
                case 2:
                {
                    string nama;
                    char ch[100];

                    cout << "Enter the string to search: \n";
                    scanf(" %[^\n]s", ch);
                    // cin.getline(ch, 100);
                    btree.delete_from_file(ch);
                    break;
                }
                case 3:
                {
                    string nama;
                    char ch[100];

                    cout << "Enter the string to search: \n";
                    scanf(" %[^\n]s", ch);
                    // cin.getline(ch, 100);
                    btree.search2(ch, btree.getRoot());
                    break;
                }
                case 4:
                {
                    btree.display(btree.getRoot());
                    break;
                }
                case 5:
                {
                    exit(0);
                    break;
                }
                default:
                    break;
                }
            }
            break;
        }
        case 5:
        {
            BPTree<Doj> btree;
            btree.populate_from_file(FILENAME);
            while (1)
            {
                cout << "\n1. Insert";
                cout << "\n2. Delete";
                cout << "\n3. Search";
                cout << "\n4. Display";
                cout << "\n5. Exit";
                int choice;
                cin >> choice;
                switch (choice)
                {
                case 1:
                {
                    cout << "Enter the id: ";
                    int id;
                    cin >> id;
                    cout << "Enter the name: ";
                    string name;
                    cin >> name;
                    cout << "Enter the dob: ";
                    string dob;
                    cin >> dob;
                    cout << "Enter the Gender: ";
                    string gender;
                    cin >> gender;
                    cout << "Enter the doj: ";
                    string doj;
                    cin >> doj;
                    cout << "Enter the address: ";
                    string address;
                    cin >> address;
                    cout << "Enter the qualification: ";
                    string qualifi;
                    cin >> qualifi;
                    btree.insert_in_file(FILENAME, id, name, dob, gender, doj, address, qualifi);
                    break;
                }
                case 2:
                {
                    string nama;
                    char ch[100];

                    cout << "Enter the string to search: \n";
                    scanf(" %[^\n]s", ch);
                    // cin.getline(ch, 100);
                    btree.delete_from_file(ch);
                    break;
                }
                case 3:
                {
                    string nama;
                    char ch[100];

                    cout << "Enter the string to search: \n";
                    scanf(" %[^\n]s", ch);
                    // cin.getline(ch, 100);
                    btree.search2(ch, btree.getRoot());
                    break;
                }
                case 4:
                {
                    btree.display(btree.getRoot());
                    break;
                }
                case 5:
                {
                    exit(0);
                    break;
                }
                default:
                    break;
                }
            }
            break;
        }
        case 6:
        {
            BPTree<Address> btree;
            btree.populate_from_file(FILENAME);
            while (1)
            {
                cout << "\n1. Insert";
                cout << "\n2. Delete";
                cout << "\n3. Search";
                cout << "\n4. Display";
                cout << "\n5. Exit";
                int choice;
                cin >> choice;
                switch (choice)
                {
                case 1:
                {
                    cout << "Enter the id: ";
                    int id;
                    cin >> id;
                    cout << "Enter the name: ";
                    string name;
                    cin >> name;
                    cout << "Enter the dob: ";
                    string dob;
                    cin >> dob;
                    cout << "Enter the Gender: ";
                    string gender;
                    cin >> gender;
                    cout << "Enter the doj: ";
                    string doj;
                    cin >> doj;
                    cout << "Enter the address: ";
                    string address;
                    cin >> address;
                    cout << "Enter the qualification: ";
                    string qualifi;
                    cin >> qualifi;
                    btree.insert_in_file(FILENAME, id, name, dob, gender, doj, address, qualifi);
                    break;
                }
                case 2:
                {
                    string nama;
                    char ch[100];

                    cout << "Enter the string to search: \n";
                    scanf(" %[^\n]s", ch);
                    // cin.getline(ch, 100);
                    btree.delete_from_file(ch);
                    break;
                }
                case 3:
                {
                    string nama;
                    char ch[100];

                    cout << "Enter the string to search: \n";
                    scanf(" %[^\n]s", ch);
                    // cin.getline(ch, 100);
                    btree.search2(ch, btree.getRoot());
                    break;
                }
                case 4:
                {
                    btree.display(btree.getRoot());
                    break;
                }
                case 5:
                {
                    exit(0);
                    break;
                }
                default:
                    break;
                }
            }
            break;
        }
        case 7:
        {
            BPTree<Qualification> btree;
            btree.populate_from_file(FILENAME);
            while (1)
            {
                cout << "\n1. Insert";
                cout << "\n2. Delete";
                cout << "\n3. Search";
                cout << "\n4. Display";
                cout << "\n5. Exit";
                int choice;
                cin >> choice;
                switch (choice)
                {
                case 1:
                {
                    cout << "Enter the id: ";
                    int id;
                    cin >> id;
                    cout << "Enter the name: ";
                    string name;
                    cin >> name;
                    cout << "Enter the dob: ";
                    string dob;
                    cin >> dob;
                    cout << "Enter the Gender: ";
                    string gender;
                    cin >> gender;
                    cout << "Enter the doj: ";
                    string doj;
                    cin >> doj;
                    cout << "Enter the address: ";
                    string address;
                    cin >> address;
                    cout << "Enter the qualification: ";
                    string qualifi;
                    cin >> qualifi;
                    btree.insert_in_file(FILENAME, id, name, dob, gender, doj, address, qualifi);
                    break;
                }
                case 2:
                {
                    string nama;
                    char ch[100];

                    cout << "Enter the string to search: \n";
                    scanf(" %[^\n]s", ch);
                    // cin.getline(ch, 100);
                    btree.delete_from_file(ch);
                    break;
                }
                case 3:
                {
                    string nama;
                    char ch[100];

                    cout << "Enter the string to search: \n";
                    scanf(" %[^\n]s", ch);
                    // cin.getline(ch, 100);
                    btree.search2(ch, btree.getRoot());
                    break;
                }
                case 4:
                {
                    btree.display(btree.getRoot());
                    break;
                }
                case 5:
                {
                    exit(0);
                    break;
                }
                default:
                    break;
                }
            }
            break;
        }
        case 8:
        {
            exit(0);
        }
        default:
        {
            cout << "Invalid Choice";
        }
        }
    }

    // cout << "\n\nDisplaying the tree: " << endl;
    // btree.display(btree.getRoot());
    // btree.search2("Sheikh Shakir Qureshi", btree.getRoot());
    // btree.deletee("25-Apr-74");
    // btree.display(btree.getRoot());
    // int id;
    // btree.getnodecount();
    // cout << "bla" << id << endl;
    // btree.insert_in_file(FILENAME, 12, "hassan bukhari", "25-Apr-74", "G", "25-Apr-74", "karachi", "FSc");
    // cout << endl
    //      << endl;
    // cout << "Displaying the tree again: " << endl;
    // btree.display(btree.getRoot());
    // btree.delete_from_file("hassan bukhari");
    // // btree.populate_from_file(FILENAME);
    // cout << endl
    //      << endl;
    // cout << "Displaying the tree again part 2: " << endl;

    // btree.display(btree.getRoot());
}