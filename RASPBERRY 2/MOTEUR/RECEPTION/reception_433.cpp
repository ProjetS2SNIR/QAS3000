//#include "reception_433.h"
#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <bits/stdc++.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <unistd.h>

using namespace std;
class reception_433{
private:
	string fichier = "/home/pi/MOTEUR/command.txt";

public:
        string command();
};


string reception_433::command()
{
    ifstream input_file(fichier);
    if (!input_file.is_open()) {
        cerr << "Could not open the file - '"
             << fichier << "'" << endl;
        exit(EXIT_FAILURE);
    }
    return string((istreambuf_iterator<char>(input_file)), istreambuf_iterator<char>());
}


