/***********************
 **  Ibraheem Rehman  **
 **  SE-Q    21i-1102 **
 ***********************/

#include <iostream>
#include <fstream>
#include <string>
#include <regex>
using namespace std;

struct ID
{
    int id;
    string reference;
};

// struct Name{
//     string name;
//     string refrence;
// };

// struct DOB{
//     string dob;
//     string refrence;
// };

// struct Gender{
//     string gender;
//     string refrence;
// };

// struct DOJ{
//     string doj;
//     string refrence;
// };

// struct Address{
//     string address;
//     string refrence;
// };

// struct Qualification{
//     string qualification;
//     string refrence;
// };

struct Student
{
    ID id;
    // Name name;
    // DOB dob;
    // Gender gender;
    // DOJ doj;
    // Address address;
    // Qualification qualification;
};

class File1
{
private:
    string filename;
    Student *data;

public:
    File1(string filename)
    {
        this->filename = filename;
        data = new Student[10];
    }
    void read()
    {
        cout<<filename<<endl;
        fstream file;
        file.open(filename, ios::in);
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
            //remove file from string
            regex removalf("File0");
            fnum = regex_replace(fnum, removalf, "");


            smatch sid;
            regex rid("([0-9]+)");
            regex_search(str, sid, rid);
            int Id = stoi(sid.str(0));

            data[count].id.id = Id;
            data[count].id.reference = fname+fnum+"L"+to_string(Id);

            cout<<"REF: "<<data[count].id.reference<<endl;

            smatch sname;
            regex rname("([A-Za-z]+)( )([A-Za-z]+)|([A-Za-z]+)( )([A-Za-z]+)( )([A-Za-z]+)");
            // (^(.*?)[0-9]+)
            regex_search(str, sname, rname);
            string Name = sname.str(0);
            // cout << "Name: " << Name << endl;

            smatch sdob;
            regex rdob("([0-9]+)(-)([A-Za-z]+)(-)([0-9]+)");
            regex_search(str, sdob, rdob);
            string Dob = sdob.str(0);
            // cout << "DOB: " << Dob << endl;

            smatch sgender;
            regex rgender("(\t)([A-Za-z])(\t)");
            regex_search(str, sgender, rgender);
            regex removall("\t"); // Removing tab space from the string
            string Gender = sgender.str(0);
            Gender = regex_replace(Gender, removall, "");
            // cout << "Gender: " << Gender << endl;

            smatch sdoj;
            regex rdoj("(M|F)(\t)([0-9]+)(-)([A-Za-z]+)(-)([0-9]+)");
            regex_search(str, sdoj, rdoj);
            regex removall2("M|F"); // Removing Gender from the string
            string Doj = sdoj.str(0);
            Doj = regex_replace(Doj, removall2, "");
            regex removall2_2("\t"); // Removing tab space from the string
            Doj = regex_replace(Doj, removall2_2, "");
            // cout << "DOJ: " << Doj << endl;

            smatch saddress;
            // House No. 31                                                                                                                 h no.875
            regex raddress("(\t)([A-Za-z0-9][#]+).*|([A-Za-z]+[.]( )[#]+).*|(\t)([A-Za-z]+( )[A-Za-z]+[.]( )[0-9]+).*|([A-Za-z][.]+)( )([A-Za-z][.]+).*|([A-Za-z]+[.]( )[A-Za-z]+[.]( )+).*|([A-Za-z]( )[A-Za-z]+[.]+).*");
            // regex raddress("(\t)([A-Za-z0-9][#]+).*");
            regex_search(str, saddress, raddress);
            string Address = saddress.str(0);
            regex removal("FSc|A-Level|Fsc|F.Sc.|HSSC");
            Address = regex_replace(Address, removal, "");
            regex removall3("\t"); // Removing tab space from the string
            Address = regex_replace(Address, removall3, "");
            // cout << "Address: " << Address << endl;

            smatch squalification;
            regex rqualification("(\t)([A-Za-z]+)(-Level)|(FSc)|(Fsc)|(F.Sc.)|(HSSC)|( )([A-Za-z]+)(-Level)|(FSc)|(Fsc)|(F.Sc.)|(HSSC)|( )([A-Za-z]+)(-Level)|(FSc)|(Fsc)|(F.Sc.)|(HSSC)");
            regex_search(str, squalification, rqualification);
            string Qualification = squalification.str(0);
            // cout << "Qualification: " << Qualification << endl;

            cout << endl;
            str = match.suffix().str();
            count++;
        }
    }

    void print()
    {
    }
};

struct Node
{
    int *keys;
    int order;
    int Min_Keys;
    Node **child;
    int key_count;
    bool is_leaf;
    int Max_Keys;

    Node(int order, bool is_leaf)
    {
        this->order = order;
        this->is_leaf = is_leaf;
        this->keys = new int[2 * order / 2 - 1];
        this->child = new Node *[2 * order / 2 + 1];
        this->key_count = 0;
        this->Min_Keys = order / 2;
        this->Max_Keys = order - 1;
    }

    void traverse()
    {
        int i;
        for (i = 0; i < this->key_count; i++)
        {
            if (this->is_leaf == false)
                this->child[i]->traverse();
            cout << " " << this->keys[i];
        }
        if (this->is_leaf == false)
            this->child[i]->traverse();
    }

    Node *search(int key)
    {
        int i = 0;
        while (i < this->key_count && key > this->keys[i])
            i++;
        if (this->keys[i] == key)
            return this;
        if (this->is_leaf == true)
            return NULL;
        return this->child[i]->search(key);
    }

    void insert_non_full(int key)
    {
        int i = this->key_count - 1;
        if (this->is_leaf == true)
        {
            while (i >= 0 && this->keys[i] > key)
            {
                this->keys[i + 1] = this->keys[i];
                i--;
            }
            this->keys[i + 1] = key;
            this->key_count = this->key_count + 1;
        }
        else
        {
            while (i >= 0 && this->keys[i] > key)
                i--;
            if (this->child[i + 1]->key_count == this->Max_Keys)
            {
                this->split_child(i + 1, this->child[i + 1]);
                if (this->keys[i + 1] < key)
                    i++;
            }
            this->child[i + 1]->insert_non_full(key);
        }
    }

    void split_child(int i, Node *y)
    {
        Node *z = new Node(y->order, y->is_leaf);
        z->key_count = this->Min_Keys - 1;
        for (int j = 0; j < this->Min_Keys - 1; j++)
            z->keys[j] = y->keys[j + this->Min_Keys];
        if (y->is_leaf == false)
        {
            for (int j = 0; j < this->Min_Keys; j++)
                z->child[j] = y->child[j + this->Min_Keys];
        }
        y->key_count = this->Min_Keys - 1;
        for (int j = this->key_count; j >= i + 1; j--)
            this->child[j + 1] = this->child[j];
        this->child[i + 1] = z;
        for (int j = this->key_count - 1; j >= i; j--)
            this->keys[j + 1] = this->keys[j];
        this->keys[i] = y->keys[this->Min_Keys - 1];
        this->key_count = this->key_count + 1;
    }

    void remove(int key)
    {
        int index = this->find_key(key);
        if (index < this->key_count && this->keys[index] == key)
        {
            if (this->is_leaf)
                this->remove_from_leaf(index);
            else
                this->remove_from_non_leaf(index);
        }
        else
        {
            if (this->is_leaf)
            {
                cout << "The key " << key << " is does not exist in the tree " << endl;
                return;
            }
            bool flag = ((index == this->key_count) ? true : false);
            if (this->child[index]->key_count < this->Min_Keys)
                this->fill(index);
            if (flag && index > this->key_count)
                this->child[index - 1]->remove(key);
            else
                this->child[index]->remove(key);
        }
        return;
    }

    void remove_from_leaf(int index)
    {
        for (int i = index + 1; i < this->key_count; ++i)
            this->keys[i - 1] = this->keys[i];
        this->key_count--;
        return;
    }

    void remove_from_non_leaf(int index)
    {
        int key = this->keys[index];
        if (this->child[index]->key_count >= this->Min_Keys)
        {
            int pred = this->get_pred(index);
            this->keys[index] = pred;
            this->child[index]->remove(pred);
        }
        else if (this->child[index + 1]->key_count >= this->Min_Keys)
        {
            int succ = this->get_succ(index);
            this->keys[index] = succ;
            this->child[index + 1]->remove(succ);
        }
        else
        {
            this->merge(index);
            this->child[index]->remove(key);
        }
        return;
    }

    int find_key(int key)
    {
        int index = 0;
        while (index < this->key_count && this->keys[index] < key)
            ++index;
        return index;
    }

    int get_pred(int index)
    {
        Node *cur = this->child[index];
        while (!cur->is_leaf)
            cur = cur->child[cur->key_count];
        return cur->keys[cur->key_count - 1];
    }

    int get_succ(int index)
    {
        Node *cur = this->child[index + 1];
        while (!cur->is_leaf)
            cur = cur->child[0];
        return cur->keys[0];
    }

    void fill(int index)
    {
        if (index != 0 && this->child[index - 1]->key_count >= this->Min_Keys)
            this->borrow_from_prev(index);
        else if (index != this->key_count && this->child[index + 1]->key_count >= this->Min_Keys)
            this->borrow_from_next(index);
        else
        {
            if (index != this->key_count)
                this->merge(index);
            else
                this->merge(index - 1);
        }
        return;
    }

    void borrow_from_prev(int index)
    {
        Node *child = this->child[index];
        Node *sibling = this->child[index - 1];
        for (int i = child->key_count - 1; i >= 0; --i)
            child->keys[i + 1] = child->keys[i];
        if (!child->is_leaf)
        {
            for (int i = child->key_count; i >= 0; --i)
                child->child[i + 1] = child->child[i];
        }
        child->keys[0] = this->keys[index - 1];
        if (!child->is_leaf)
            child->child[0] = sibling->child[sibling->key_count];
        this->keys[index - 1] = sibling->keys[sibling->key_count - 1];
        child->key_count += 1;
        sibling->key_count -= 1;
        return;
    }

    void borrow_from_next(int index)
    {
        Node *child = this->child[index];
        Node *sibling = this->child[index + 1];
        child->keys[(child->key_count)] = this->keys[index];
        if (!(child->is_leaf))
            child->child[(child->key_count) + 1] = sibling->child[0];
        this->keys[index] = sibling->keys[0];
        for (int i = 1; i < sibling->key_count; ++i)
            sibling->keys[i - 1] = sibling->keys[i];
        if (!sibling->is_leaf)
        {
            for (int i = 1; i <= sibling->key_count; ++i)
                sibling->child[i - 1] = sibling->child[i];
        }
        child->key_count += 1;
        sibling->key_count -= 1;
        return;
    }

    void merge(int index)
    {
        Node *child = this->child[index];
        Node *sibling = this->child[index + 1];
        child->keys[this->Min_Keys - 1] = this->keys[index];
        for (int i = 0; i < sibling->key_count; ++i)
            child->keys[i + this->Min_Keys] = sibling->keys[i];
        if (!child->is_leaf)
        {
            for (int i = 0; i <= sibling->key_count; ++i)
                child->child[i + this->Min_Keys] = sibling->child[i];
        }
        for (int i = index + 1; i < this->key_count; ++i)
            this->keys[i - 1] = this->keys[i];
        for (int i = index + 2; i <= this->key_count; ++i)
            this->child[i - 1] = this->child[i];
        child->key_count += sibling->key_count + 1;
        this->key_count--;
        delete (sibling);
        return;
    }

    friend class BTree;
};

class BTree
{
    Node *root;
    int order;

public:
    BTree(int order)
    {
        this->root = NULL;
        this->order = order;
    }

    void traverse()
    {
        if (this->root != NULL)
            this->root->traverse();
    }

    Node *search(int key)
    {
        return (this->root == NULL) ? NULL : this->root->search(key);
    }

    void insert(int key)
    {
        if (this->root == NULL)
        {
            this->root = new Node(this->order, true);
            this->root->keys[0] = key;
            this->root->key_count = 1;
        }
        else
        {
            if (this->root->key_count == this->order - 1)
            {
                Node *new_root = new Node(this->order, false);
                new_root->child[0] = this->root;
                new_root->split_child(0, this->root);
                int i = 0;
                if (new_root->keys[0] < key)
                    i++;
                new_root->child[i]->insert_non_full(key);
                this->root = new_root;
            }
            else
                this->root->insert_non_full(key);
        }
    }

    void remove(int key)
    {
        if (!this->root)
        {
            cout << "The tree is empty " << endl;
            return;
        }
        this->root->remove(key);
        if (this->root->key_count == 0)
        {
            Node *tmp = this->root;
            if (this->root->is_leaf)
                this->root = NULL;
            else
                this->root = this->root->child[0];
            delete tmp;
        }
        return;
    }
};

int main()
{
    File1 f1("Fall2022DSDataFile001.txt");
    f1.read();
}

// int main()
// {
//     BTree t(6); // A B-Tree with minimum degree 3

//     t.insert(1);
//     t.insert(3);
//     t.insert(7);
//     t.insert(10);
//     t.insert(11);
//     t.insert(13);
//     t.insert(14);
//     t.insert(15);
//     t.insert(18);
//     t.insert(16);
//     t.insert(19);
//     t.insert(24);
//     t.insert(25);
//     t.insert(26);
//     t.insert(21);
//     t.insert(4);
//     t.insert(5);
//     t.insert(20);
//     t.insert(22);
//     t.insert(2);
//     t.insert(17);
//     t.insert(12);
//     t.insert(6);

//     cout << "Traversal of tree constructed is\n";
//     t.traverse();
//     cout << endl;

//     t.remove(6);
//     cout << "Traversal of tree after removing 6\n";
//     t.traverse();
//     cout << endl;

//     t.remove(13);
//     cout << "Traversal of tree after removing 13\n";
//     t.traverse();
//     cout << endl;

//     t.remove(7);
//     cout << "Traversal of tree after removing 7\n";
//     t.traverse();
//     cout << endl;

//     t.remove(4);
//     cout << "Traversal of tree after removing 4\n";
//     t.traverse();
//     cout << endl;

//     t.remove(2);
//     cout << "Traversal of tree after removing 2\n";
//     t.traverse();
//     cout << endl;

//     t.remove(16);
//     cout << "Traversal of tree after removing 16\n";
//     t.traverse();
//     cout << endl;

//     return 0;
// }