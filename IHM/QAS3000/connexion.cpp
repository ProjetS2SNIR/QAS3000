#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <cstring>
#include <bits/stdc++.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <unistd.h>
#include <sstream>


using namespace std;

/*sql::Connection* connexion()
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

    // Etape 1 : créer une connexion à la BDD
    driver = get_driver_instance();

    // on note les paramètres classiques: adresse ip du serveur et port, login, mot de passe
    con = driver->connect("tcp://192.168.2.128:3306", "mathieu", "projet2022");

    // Etape 2 : connexion à la base choisie, ici QAS3000
    con->setSchema("QAS3000");

    // Etape 3 : création d'un objet qui permet d'effectuer des requêtes sur la base
    stmt = con->createStatement();

    return con;
  }

  catch (sql::SQLException &e) {
  // Gestion des execeptions pour déboggage
      cout << "# ERR: " << e.what();
      cout << " (code erreur MySQL: " << e.getErrorCode();
      cout << ", EtatSQL: " << e.getSQLState() << " )" << endl;
  }
}
*/


/* int getCo2(sql::Connection* con){
        string CO2;
        int CO2n;
        sql::PreparedStatement * pstmt;
        sql::ResultSet* res;
        pstmt = con->prepareStatement("SELECT * FROM `CO2` ORDER BY ID_CO2 DESC LIMIT 0,1");

        res = pstmt->executeQuery();
        while (res->previous())
            CO2 = res->getString("CO2");
        stringstream ss;
        ss << CO2;
        ss >> CO2n;
        return CO2n;
}

delete res;
delete stmt;
delete con;

int getAirquality(){
        string AirQ;

        AirQ = 12;
        int AirQn =std::stoi(AirQ);

        return AirQn;
}

float getTemp(){
        string Temp;

        Temp = 15;
        float Tempn = std::stoi(Temp);

        return Tempn;
}

float getHum(){
        string Humidite;

        Humidite = 18;
        float Humiditen = std::stoi(Humidite);

        return Humiditen;
} */

/*int main()
{
    sql::Connection* con = connexion();
    cout << getCo2(con);
}
*/
