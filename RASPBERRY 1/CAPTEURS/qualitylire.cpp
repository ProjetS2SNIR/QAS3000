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
string contenu;


sql::Statement* connexion()
{
  cout << endl;
  cout << "Premier test du connecteur C++ Mysql" << endl;
  // La gestion d'erreur se fait proprement avec les exceptions
  // sinon retirer le try...catch
  try {
    // Les variables nécessaires à notre programme
    sql::Driver* driver;
    sql::Connection* con;
    sql::Statement* stmt;
    sql::ResultSet* res;

    // Etape 1 : créer une connexion à la BDD
    driver = get_driver_instance();
    // on note les paramètres classiques: adresse ip du serveur et port, login, mot de passe
    con = driver->connect("tcp://127.0.0.1:3306", "simon", "projet2022");

    // Etape 2 : connexion à la base choisie, ici QAS3000
    con->setSchema("QAS3000");

    // Etape 3 : création d'un objet qui permet d'effectuer des requêtes sur la base
    stmt = con->createStatement();
    return stmt;
  }

  catch (sql::SQLException &e) {
  // Gestion des execeptions pour déboggage
      cout << "# ERR: " << e.what();
      cout << " (code erreur MySQL: " << e.getErrorCode();
      cout << ", EtatSQL: " << e.getSQLState() << " )" << endl;
  }
}


string getco2(){ //Fonction getco2() permet de prelever des données dans le fichier co2.txt
		system("sudo python3 co2.py > co2.txt");
		ifstream fichier("co2.txt",ios::in);
                if(fichier)
                {
                fichier.seekg(30, ios::beg);
                getline(fichier, contenu);
                contenu = contenu.substr(0, 4);
                }
		return contenu;
}

string getairquality(){ //Fonction getairquality() permet de prelever des données dans le fichier airquality.txt
		system("python3 airquality.py 0 > airquality.txt");
		string valeuraq;
		ifstream fichier("airquality.txt",ios::in);

                if(fichier)
                {
                        fichier.seekg(32, ios::beg);
                	      getline(fichier, valeuraq);
                        valeuraq = valeuraq.substr(0, 4);
                }
		return valeuraq;
}

string gettemp()  //Fonction gettemp() permet de prelever des données dans le fichier dht.txt
{
		system("python3 dht.py > dht.txt");
		string temp;
		ifstream fichier("dht.txt",ios::in);

                if(fichier)
                {
                  fichier.seekg(5, ios::beg);
                  getline(fichier, temp);
                  temp = temp.substr(0, 4);
                }
		return temp;
}

string gethum(){ //Fonction gethum() permet de prelever des données dans le fichier dht.txt
		string humidite;
		ifstream fichier("dht.txt",ios::in);

                if(fichier)
                {
                  fichier.seekg(23, ios::beg);
                	getline(fichier, humidite);
                  humidite = humidite.substr(0, 4);
                }
		return humidite;
}

void insertion(string req, sql::Statement* stmt)
{
    // Etape 4 : exécution d'une requete : ici on insere un enregistrement
    // dans la table des capteurs 
     
    int result = stmt->executeUpdate(req);
    cout << "Resultat INSERT: " << result << endl;

  cout << endl;

  // on sort en indiquant que tout c'est bien passé
  //return EXIT_SUCCESS;
}


string requete(string airquality, string co2, string temp, string hum, sql::Statement* stmt)
{
    string reqco2 =  "INSERT INTO `CO2`(`DATEC`, `CO2`) VALUES (NOW(),'"+ co2 + "');"; //Insert la date et la valeur de co2 dans la table 'DATEC' et 'CO2'
    int result1 = stmt->executeUpdate(reqco2); 
    cout << "Resultat INSERT 1: " << result1 << endl; // Exécution de la requête, on obtient un 1 si la valeur est bien saisie dans la base de données

    string reqtemp =  "INSERT INTO `Temperature`(`DATET`, `TEMPT`) VALUES (NOW(),'"+temp + "');"; 
    int result2 = stmt->executeUpdate(reqtemp);
    cout << "Resultat INSERT 2: " << result2 << endl;

    string reqquality =  "INSERT INTO `QualiteAir`(`DATEQ`, `QUALITYQ`) VALUES (NOW(),'"+ airquality + "');";
    int result3 = stmt->executeUpdate(reqquality);
    cout << "Resultat INSERT 3: " << result3 << endl;

    string reqhumi =  "INSERT INTO `Humidite`(`DATE_H`, `HUMI_H`) VALUES (NOW(),'"+ hum + "');";
    int result4 = stmt->executeUpdate(reqhumi);
    cout << "Resultat INSERT 4: " << result4 << endl;

    string res = "\n OK";
    return res;
}

int main()
{
  string airquality;
  string co2;
  string temp;
  string hum;
  int i=0;
  


  //system("python3 chauffeco2.py");
  sql::Statement* stmt = connexion();
  while(1){
	  //ACQUISITION DES VALEURS
	  airquality = getairquality();
	  co2 = getco2();
	  temp = gettemp();
 	  hum = gethum();

    // AFFICHAGE
    cout << "La qualité de l'air: "<< airquality << " S.U." << endl; //Afficher la valeur de la qualité de l'air 
    cout << "La qualité de Co2: "<< co2 << " ppm" << endl;
    cout << "La température: "<< temp << "°C" << endl;
    cout << "L'humidité: "<< hum << "%" << endl;
  
  
    // PREPARATION DE LA REQUETE SQL
    string res = requete(airquality, co2, temp, hum, stmt);
    cout << res << endl;
    
    // ENVOI DE LA REQUETE
    sleep(2);
    i++;
  }
  
}


 
