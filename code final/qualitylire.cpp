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

    // Etape 2 : connexion à la base choisie, ici olivier_db
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


string getco2(){
		system("python3 co2.py > co2.txt");
		ifstream fichier("co2.txt",ios::in);
                if(fichier)
                {
                fichier.seekg(15, ios::beg);
                getline(fichier, contenu);
                //contenu = contenu.substr(0, 4);
                }
		return contenu;
}

string getairquality(){
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

string gettemp()
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

string gethum(){
		string humidite;
		ifstream fichier("dht.txt",ios::in);

                if(fichier)
                {
                  fichier.seekg(22, ios::beg);
                	getline(fichier, humidite);
                  humidite = humidite.substr(0, 4);
                }
		return humidite;
}

void insertion(string req, sql::Statement* stmt)
{
    // Etape 4 : exécution d'une requete : ici on insere un enregistrement
    // dans la table Animal
    // string req = "INSERT INTO CAPTEURS VALUES(NULL,'13.6','45', '420', '100', NOW());";  
    int result = stmt->executeUpdate(req);
    cout << "Resultat INSERT: " << result << endl;

  cout << endl;

  // on sort en indiquant que tout c'est bien passé
  //return EXIT_SUCCESS;
}


string requete(string airquality, string co2, string temp, string hum, sql::Statement* stmt)
{
    string reqco2 =  "INSERT INTO `CO2`(`DATEC`, `CO2`) VALUES (NOW(),'"+ co2 + "');";
    int result1 = stmt->executeUpdate(reqco2);
    cout << "Resultat INSERT: " << result1 << endl;

    string reqtemp =  "INSERT INTO `Temperature`(`DATET`, `TEMPT`) VALUES (NOW(),'"+temp + "');";
    int result2 = stmt->executeUpdate(reqtemp);
    cout << "Resultat INSERT: " << result2 << endl;

    string reqquality =  "INSERT INTO `QualiteAir`(`DATEQ`, `QUALITYQ`) VALUES (NOW(),'"+ airquality + "');";
    int result3 = stmt->executeUpdate(reqquality);
    cout << "Resultat INSERT: " << result3 << endl;

    string reqhum =  "INSERT INTO `Humidite`(`DATE_H`, `HUMI_H`) VALUES (NOW(),'"+ hum + "');";
    int result4 = stmt->executeUpdate(reqhum);
    cout << "Resultat INSERT: " << result4 << endl;

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
    cout << "La qualité de l'air: "<< airquality << " S.U." << endl;
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


 
