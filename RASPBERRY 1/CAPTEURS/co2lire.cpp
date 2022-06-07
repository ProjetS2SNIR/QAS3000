#include <iostream>
#include <string>
#include <fstream>


using namespace std;
string contenu;

int main()
{
        ifstream fichier("co2.txt",ios::in);

                if(fichier)
                {
                fichier.seekg(31, ios::beg);
                getline(fichier, contenu);
                {
                        cout << "La qualité de Co2: "<< contenu << endl;
                }
                }
                else 
                        cout << " Impossible  d'ouvrir le fichier!" << endl;
                return 0 ;
                }


