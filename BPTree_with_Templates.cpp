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
int MAX = 3;

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

public:
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

    BPTree()
    {
        root = NULL;
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
                // cout<<"check"<<endl;
                // cout<<x;//<<" "<<cursor->key[i].name<<endl;

                T virtualNode[MAX + 1];

                for (int i = 0; i < MAX; i++)
                {
                    virtualNode[i].name = cursor->key[i].name;
                    virtualNode[i].reference = cursor->key[i].reference;
                    // virtualNode[i] = cursor->key[i].name;
                    // virtualNode[i] = cursor->key[i].reference;
                }
                // cout<<"check"<<endl;
                int i = 0, j;
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
                    virtualNode[j] = virtualNode[j - 1]; // segmentatio fault
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
        int count = 0;
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
            int Id = stoi(sid.str(0));

            string reference = fname + fnum + "L" + to_string(Id);
            // insert(Id, reference);

            if (type == "Name")
            {
                smatch sname;
                regex rname("([A-Za-z]+)( )([A-Za-z]+)|([A-Za-z]+)( )([A-Za-z]+)( )([A-Za-z]+)");
                // (^(.*?)[0-9]+)
                regex_search(str, sname, rname);
                string Name = sname.str(0);

                insert(Name, reference);
            }

            // cout << "Name: " << Name << endl;

            if (type == "Dob")
            {
                smatch sdob;
                regex rdob("([0-9]+)(-)([A-Za-z]+)(-)([0-9]+)");
                regex_search(str, sdob, rdob);
                string Dob = sdob.str(0);

                insert(Dob, reference);
            }
            // cout << "DOB: " << Dob << endl;

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

            // cout << "Gender: " << Gender << endl;

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
            // cout << "DOJ: " << Doj << endl;

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
            // cout << "Address: " << Address << endl;

            if (type == "Qualification")
            {
                smatch squalification;
                regex rqualification("(\t)([A-Za-z]+)(-Level)|(FSc)|(Fsc)|(F.Sc.)|(HSSC)|( )([A-Za-z]+)(-Level)|(FSc)|(Fsc)|(F.Sc.)|(HSSC)|( )([A-Za-z]+)(-Level)|(FSc)|(Fsc)|(F.Sc.)|(HSSC)");
                regex_search(str, squalification, rqualification);
                string Qualification = squalification.str(0);

                insert(Qualification, reference);
            }
            // cout << "Qualification: " << Qualification << endl;

            // cout << endl;
            str = match.suffix().str();
            count++;
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
            file.open("Fall2022DSDataFile001.txt", ios::in);
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
                cout << cursor->key[i].name << " " << cursor->key[i].reference << " ";
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
};

int main()
{
    BPTree<Dob> btree;
    btree.populate_from_file("Fall2022DSDataFile001.txt");
    cout << "\n\nDisplaying the tree: " << endl;
    btree.display(btree.getRoot());
    btree.search("25-Apr-74");
}