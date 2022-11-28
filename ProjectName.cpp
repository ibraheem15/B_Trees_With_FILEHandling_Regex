/***********************
 **  Ibraheem Rehman  **
 **  SE-Q    21i-1102 **
 ***********************/

#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <sstream>
#include <limits>
using namespace std;

// struct ID
// {
//     int id;
//     string reference;
// };

struct Name
{
    string name;
    string refrence;
};

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
    // ID id;
    Name name;
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
        cout << filename << endl;
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
            // remove file from string
            regex removalf("File0");
            fnum = regex_replace(fnum, removalf, "");

            smatch sid;
            regex rid("([0-9]+)");
            regex_search(str, sid, rid);
            int Id = stoi(sid.str(0));

            // data[count].id.id = Id;
            // data[count].id.reference = fname + fnum + "L" + to_string(Id);

            // cout << "REF: " << data[count].id.reference << endl;

            smatch sname;
            regex rname("([A-Za-z]+)( )([A-Za-z]+)|([A-Za-z]+)( )([A-Za-z]+)( )([A-Za-z]+)");
            // (^(.*?)[0-9]+)
            regex_search(str, sname, rname);
            string Name = sname.str(0);

            data[count].name.name = Name;
            data[count].name.refrence = fname + fnum + "L" + to_string(Id);
            // data[count].name.length = Name.length();

            // cout << "REF: " << data[count].name.refrence << endl;
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
    Student *keys;
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
        this->keys = new Student[2 * order / 2 - 1];
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
            cout << " " << this->keys[i].name.name << " " << this->keys[i].name.refrence << endl; // << " " << this->keys[i].name.length << endl;
            // cout << " ID:" << this->keys[i].id.id << " REF:" << this->keys[i].id.reference << endl;
        }
        if (this->is_leaf == false)
            this->child[i]->traverse();
    }

    std::fstream &GotoLine(std::fstream &file, unsigned int num)
    {
        file.seekg(std::ios::beg);
        for (int i = 0; i < num - 1; ++i)
        {
            file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        return file;
    }

    // Node *search_with_ID(int key)
    // {
    //     int i = 0;
    //     fstream file;
    //     file.open("Fall2022DSDataFile001.txt", ios::in);
    //     string ss;

    //     while (i < this->key_count && key > this->keys[i].id.id)
    //     {
    //         getline(file, ss);
    //         i++;
    //     }
    //     if (this->keys[i].id.id == key)
    //     {
    //         string str;
    //         GotoLine(file, key);
    //         getline(file, str);
    //         cout << str << endl;
    //         return this;
    //     }
    //     // return this;
    //     if (this->is_leaf == true)
    //         return NULL;
    //     return this->child[i]->search_with_ID(key);
    // }

    Node *search_with_Name(string key)
    {
        int i = 0;
        fstream file;
        file.open("Fall2022DSDataFile001.txt", ios::in);
        string ss;

        while (i < this->key_count && (key.compare(this->keys[i].name.name) > 0)) // key.length() > this->keys[i].name.length)
        {
            getline(file, ss);
            cout<<ss<<endl;
            i++;
        }
        // if (this->keys[i].name.name.length() == key.length())
        if (this->keys[i].name.name.compare(key) == 0)
        {
            string str;
            cout << "bla" << i << endl;
            cout<<this->keys[i].name.name<<endl;
            // GotoLine(file, this->keys[i].name.refrence);
            string line = this->keys[i].name.refrence;

            smatch sfnum;
            regex rfnum("L([0-9])");
            regex_search(line, sfnum, rfnum);
            regex removal("L");
            string line_actual = sfnum.str(0);
            line_actual = regex_replace(line_actual, removal, "");
            int intline = stoi(line_actual);
            
            GotoLine(file, intline+1);
            getline(file, str);
            cout << str << endl;
            return this;
        }
        if (this->is_leaf == true)
            return NULL;
        return this->child[i]->search_with_Name(key);
    }

    void insert_non_full(string key, string reference)
    {
        int i = this->key_count - 1;
        if (this->is_leaf == true)
        {
            while (i >= 0 && (key.compare(this->keys[i].name.name) < 0))
            {
                this->keys[i + 1].name.name = this->keys[i].name.name;
                this->keys[i + 1].name.refrence = this->keys[i].name.refrence;
                // this->keys[i + 1].name.length = this->keys[i].name.length;
                i--;
            }
            this->keys[i + 1].name.name = key;
            this->keys[i + 1].name.refrence = reference;
            // this->keys[i + 1].name.length = key.length();
            this->key_count = this->key_count + 1;
        }
        else
        {
            while (i >= 0 && (key.compare(this->keys[i].name.name) < 0))
                i--;
            if (this->child[i + 1]->key_count == this->Max_Keys)
            {
                this->split_child(i + 1, this->child[i + 1]);
                if ((key.compare(this->keys[i+1].name.name) < 0))
                    i++;
            }
            this->child[i + 1]->insert_non_full(key, reference);
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
        {
            this->keys[j + 1].name.name = this->keys[j].name.name;
            this->keys[j + 1].name.refrence = this->keys[j].name.refrence;
            // this->keys[j + 1].name.length = this->keys[j].name.length;
        }
        this->keys[i].name.name = y->keys[this->Min_Keys - 1].name.name;
        this->keys[i].name.refrence = y->keys[this->Min_Keys - 1].name.refrence;
        // this->keys[i].name.length = y->keys[this->Min_Keys - 1].name.length;
        this->key_count = this->key_count + 1;
    }

    void remove(string key)
    {
        int index = this->find_key(key);
        if (index < this->key_count && this->keys[index].name.name == key)
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
        {
            this->keys[i - 1].name.name = this->keys[i].name.name;
            this->keys[i - 1].name.refrence = this->keys[i].name.refrence;
            // this->keys[i - 1].name.length = this->keys[i].name.length;
        }
        this->key_count--;
        return;
    }
    void remove_from_non_leaf(int index)
    {
        string key = this->keys[index].name.name;
        if (this->child[index]->key_count >= this->Min_Keys)
        {
            string pred = this->get_pred(index);
            this->keys[index].name.name = pred;
            this->child[index]->remove(pred);
        }
        else if (this->child[index + 1]->key_count >= this->Min_Keys)
        {
            string succ = this->get_succ(index);
            this->keys[index].name.name = succ;
            this->child[index + 1]->remove(succ);
        }
        else
        {
            this->merge(index);
            this->child[index]->remove(key);
        }
        return;
    }

    int find_key(string key)
    {
        int index = 0;
        while (index < this->key_count && (key.compare(this->keys[index].name.name) < 0))
            ++index;
        return index;
    }

  
    string get_pred(int index)
    {
        Node *cur = this->child[index];
        while (!cur->is_leaf)
            cur = cur->child[cur->key_count];
        return cur->keys[cur->key_count - 1].name.name;
    }

   
    string get_succ(int index)
    {
        Node *cur = this->child[index + 1];
        while (!cur->is_leaf)
            cur = cur->child[0];
        return cur->keys[0].name.name; // can be lenght as well lets see
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

    void populate()
    {
    }

    void traverse()
    {
        if (this->root != NULL)
            this->root->traverse();
    }


    Node *search_with_name(string key)
    {
        return (this->root == NULL) ? NULL : this->root->search_with_Name(key);
    }

    void populate_from_file(string filename)
    {
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
            // remove file from string
            regex removalf("File0");
            fnum = regex_replace(fnum, removalf, "");

            smatch sid;
            regex rid("([0-9]+)");
            regex_search(str, sid, rid);
            int Id = stoi(sid.str(0));

            string reference = fname + fnum + "L" + to_string(Id);
            // insert(Id, reference);
            // keys[count].id.id = Id;
            // keys[count].id.reference = fname+fnum+"L"+to_string(Id);

            // cout<<"REF: "<<keys[count].id.reference<<endl;

            smatch sname;
            regex rname("([A-Za-z]+)( )([A-Za-z]+)|([A-Za-z]+)( )([A-Za-z]+)( )([A-Za-z]+)");
            // (^(.*?)[0-9]+)
            regex_search(str, sname, rname);
            string Name = sname.str(0);

            insert(Name, reference);
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

            // cout << endl;
            str = match.suffix().str();
            count++;
        }
    }

 
    void insert(string key, string reference)
    {
        if (this->root == NULL)
        {
            this->root = new Node(this->order, true);
            this->root->keys[0].name.name = key;
            this->root->keys[0].name.refrence = reference;
            // this->root->keys[0].name.length = key.length();
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

                if (new_root->keys[0].name.name.compare(key) < 0)
                    i++;
                new_root->child[i]->insert_non_full(key, reference);
                this->root = new_root;
            }
            else
                this->root->insert_non_full(key, reference);
        }
    }

    void remove(string key)
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
    BTree t(5);
    t.populate_from_file("Fall2022DSDataFile001.txt");
    t.traverse();
    // t.search_with_ID(2);
    t.search_with_name("Abdur Raziq");
    // t.remove("Abdur Raziq");
    // t.traverse();
}
