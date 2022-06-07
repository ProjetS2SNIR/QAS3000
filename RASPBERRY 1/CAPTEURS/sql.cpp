// Test connecteur C++ MySQL
// O. Dartois, Juin 2017

//#include <stdlib.h>
#include <iostream>

// Les includes strictement n�cessaire pour cet exemple
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

using namespace std;

int main(void)
{
  cout << endl;
  cout << "Premier test du connecteur C++ Mysql" << endl;

  // La gestion d'erreur se fait proprement avec les exceptions
  // sinon retirer le try...catch

  try {
    // Les variables n�cessaires � notre programme
    sql::Driver* driver;
    sql::Connection* con;
    sql::Statement* stmt;
    sql::ResultSet* res;

    // Etape 1 : cr�er une connexion � la BDD
    driver = get_driver_instance();
    // on note les param�tres classiques: adresse ip du serveur et port, login, mot de passe
    con = driver->connect("tcp://127.0.0.1:3306", "simon", "projet2022");

    // Etape 2 : connexion � la base choisie, ici olivier_db
    con->setSchema("QAS3000");

    // Etape 3 : cr�ation d'un objet qui permet d'effectuer des requ�tes sur la base
    stmt = con->createStatement();

    // Etape 4 : ex�cution d'une requete : ici on insere un enregistrement
    // dans la table Animal
    string req = "INSERT INTO CAPTEURS VALUES(NULL,'13.6','45', '420', '100', NOW());";  
    int result = stmt->executeUpdate(req);
    cout << "Resultat INSERT: " << result << endl;

  }
   
  catch (sql::SQLException &e) {
    // Gestion des execeptions pour d�boggage
    cout << "# ERR: " << e.what();
    cout << " (code erreur MySQL: " << e.getErrorCode();
    cout << ", EtatSQL: " << e.getSQLState() << " )" << endl;
  }

  cout << endl;

  // on sort en indiquant que tout c'est bien pass�
  return EXIT_SUCCESS;
}