
/***********************
 **  Ibraheem Rehman  **
 **  SE-Q    21i-1102 **
 ***********************/

#include <iostream>
#include <fstream>
#include <string>
#include <regex>
using namespace std;



int main()
{
    // string str = "12 Ibraheem Rehman Qazi 5-Jaan-1997 M  ho. # Street No. 1 Lahore Pakistan FSc";
    // string str1;
    // str1 = "1	Shk. Munir Hussaini	13-Dec-74	M	13-Aug-94	H#  169 s#  0 Mutian wala Thata	A-Level";

    fstream file;
    file.open("Fall2022DSDataFile001.txt", ios::in);
    stringstream buffer;
    buffer << file.rdbuf();
    string str = buffer.str();
    // cout << str;

    regex rid("([0-9]+).*");
    smatch match;
    int count=0;	
    while (regex_search(str, match, rid)&&count<4)
    {

        smatch sid;
        regex rid("([0-9]+)");
        regex_search(str, sid, rid);
        int Id = stoi(sid.str(0));
        cout << "ID: " << Id << endl;

        
        smatch sname;
        regex rname("([A-Za-z]+)( )([A-Za-z]+)|([A-Za-z]+)( )([A-Za-z]+)( )([A-Za-z]+)");
        // (^(.*?)[0-9]+)
        regex_search(str, sname, rname);
        string Name = sname.str(0);
        cout << "Name: " << Name << endl;

        smatch sdob;
        regex rdob("([0-9]+)(-)([A-Za-z]+)(-)([0-9]+)");
        regex_search(str, sdob, rdob);
        string Dob = sdob.str(0);
        cout << "DOB: " << Dob << endl;

        smatch sgender;
        regex rgender("(\t)([A-Za-z])(\t)");
        regex_search(str, sgender, rgender);
        regex removall("\t"); // Removing tab space from the string
        string Gender = sgender.str(0);
        Gender = regex_replace(Gender, removall, "");
        cout << "Gender: " << Gender << endl;

        smatch sdoj;
        regex rdoj("(M|F)(\t)([0-9]+)(-)([A-Za-z]+)(-)([0-9]+)");
        regex_search(str, sdoj, rdoj);
        regex removall2("M|F"); // Removing Gender from the string
        string Doj = sdoj.str(0);
        Doj = regex_replace(Doj, removall2, "");
        regex removall2_2("\t"); // Removing tab space from the string
        Doj = regex_replace(Doj, removall2_2, "");
        cout << "DOJ: " << Doj << endl;

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
        cout << "Address: " << Address << endl;

        smatch squalification;
        regex rqualification("(\t)([A-Za-z]+)(-Level)|(FSc)|(Fsc)|(F.Sc.)|(HSSC)|( )([A-Za-z]+)(-Level)|(FSc)|(Fsc)|(F.Sc.)|(HSSC)|( )([A-Za-z]+)(-Level)|(FSc)|(Fsc)|(F.Sc.)|(HSSC)");
        regex_search(str, squalification, rqualification);
        string Qualification = squalification.str(0);
        cout << "Qualification: " << Qualification << endl;

        cout << endl;
        str = match.suffix().str();
        // search next line while file is not empty using regex
        //  str =
        //  (\n|.)*?
    }
}