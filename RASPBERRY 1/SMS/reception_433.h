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


class reception_433{
private:
  string fichier = "etat.txt";

public:
	string etat_fenetre();
};
