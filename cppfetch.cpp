#include <iostream>
#include <ios>
#include <fstream>
#include <string>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


using namespace std;




int main() {

    string name;
    string os;
    string cpu;
    string gpu;
    string memory;
    string drive;

    system("touch /tmp/fetchuser.txt");
    system("echo $USER > /tmp/fetchuser.txt");

    string fetchuser;
    fstream readfile;
    readfile.open("/tmp/fetchuser.txt");
    readfile >> fetchuser;
    cout << "user: " << fetchuser << endl;
    readfile.close();
    system("rm /tmp/fetchuser.txt");


    long int membytes = sysconf(_SC_PHYS_PAGES) * sysconf(_SC_PAGESIZE);

    //int memgb = membytes / 1073741824;
    //int memmb = membytes / 1048576;

    

    system("touch /tmp/cppfetchtempshell.txt");
    system("echo $SHELL > /tmp/cppfetchtempshell.txt");
    

    string fetchshell;
    fstream rfile;
    rfile.open("/tmp/cppfetchtempshell.txt", ios::in| ios::out);
    rfile>> fetchshell;
    cout << "shell: " << fetchshell << endl;
    rfile.close(); 
    system("rm -f /tmp/cppfetchtempshell.txt");
   

    //cout << "memory: " << memmb << "MB" << endl;


ifstream inFile;
string cpumodel;

inFile.open("/proc/cpuinfo");

size_t pos;
while(inFile.good())
  {
      getline(inFile,cpumodel); // get line from file
      pos=cpumodel.find("model name"); // search
      if(pos!=string::npos) // string::npos is returned if string is not found
        {
            //cout << line << endl;
            break;
        }
  }

    cpumodel.replace(0,12,"cpu model:");
    cout << cpumodel << endl;
    
ifstream memfile;
string memtotal;

memfile.open("/proc/meminfo");

while(memfile.good())
  {
      getline(memfile,memtotal);
      pos=memtotal.find("MemTotal");
      if(pos!=string::npos) 
        {
          break;
        }
  }

    //cout << memtotal << endl;

  size_t i = 0;
  for ( ; i < memtotal.length(); i++){ if ( isdigit(memtotal[i]) ) break; }

  memtotal = memtotal.substr(i, memtotal.length() - i);

  int memtotalint = atoi(memtotal.c_str());

  //cout << memtotalint << endl;

  int memtotalmb = memtotalint / 1024;

  //cout << memtotalmb << endl;

  
ifstream memavfile;
string memavail;

memavfile.open("/proc/meminfo");

while(memavfile.good())
  {
      getline(memavfile,memavail);
      pos=memavail.find("MemAvailable");
      if(pos!=string::npos) 
        {
          break;
        }
  }

    //cout << memavail << endl;

  size_t o = 0;
  for ( ; o < memavail.length(); o++){ if ( isdigit(memavail[o]) ) break; }

  memavail = memavail.substr(o, memavail.length() - o);

  int memavailint = atoi(memavail.c_str());

  //cout << memavailint << endl;

  int memavailmb = memavailint / 1024;

  //cout << memavailmb << endl;

  int memusedmb = memtotalmb - memavailmb;

  //cout << memusedmb << endl;

  cout << "memory: " << memusedmb << "MB" << "/" << memtotalmb << "MB" << endl;

    return 0;

    
}
