// sudo g++ traitement.cpp -o traitement -Wall -lmysqlcppconn

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

#include "/home/pi/TEST/reception_433.cpp"
#include "/home/pi/TEST/horaires.cpp"
#include "emission.cpp"
using namespace std;





class Traitement
{
        private :
		double TEMP;
		int HUMI;
		int QA;
		int CO2;
		int SEUIL_CO2;
		int SEUIL_QA;
		int SEUIL_TEMP;
		int SEUIL_HUMI;
		bool ETATBOUTON;
		bool AUTOMATIQUE;
        public :
                int connexion();
		bool choix();
		bool getAutomatique();
		bool getEtatBouton();
		void setEtatBouton(bool valeur);
};

void Traitement::setEtatBouton(bool valeur)
{
	ETATBOUTON = valeur;
}

bool Traitement::getEtatBouton()
{
	return ETATBOUTON;
}

bool Traitement::getAutomatique()
{ 
        return AUTOMATIQUE;
}


bool Traitement::choix()
{
	if(TEMP > SEUIL_TEMP)
	{
		return true;
	}
	else
	{
		if(QA > SEUIL_QA)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

int Traitement::connexion()
{
try {
  // Les variables nécessaires à notre programme
  sql::Driver* driver;
  sql::Connection* con;
  sql::Statement* stmt;
  sql::ResultSet* res;
 
  // Etape 1 : créer une connexion à la BDD
  driver = get_driver_instance();
  // on note les paramètres classiques: adresse ip du serveur et port, login, mot de passe
  con = driver->connect("192.168.2.128:3306", "mathieu", "projet2022");
 
  // Etape 2 : connexion à la base choisie, ici olivier_db
  con->setSchema("QAS3000");
 
  // Etape 3 : création d'un objet qui permet d'effectuer des requêtes sur la base
  stmt = con->createStatement();
 
  // Etape 4 : exécution d'une requete : ici on sélectionne tous les enregistrements
  // de la table Animal
  res = stmt->executeQuery("SELECT CO2,TEMPT,HUMI_H,QUALITYQ,temp_seuil,co2_seuil,qualite_seuil,humi_seuil,ETAT,AUTO FROM CO2,Temperature,Humidite,QualiteAir,Seuil,Etat WHERE ID_CO2 = (SELECT COUNT(ID_CO2) + 2 from CO2) and ID_TEMP = (SELECT COUNT(ID_TEMP) - 1 from Temperature) and ID_HUMI = (SELECT COUNT(ID_HUMI) - 1 from Humidite) and ID_QA = (SELECT COUNT(ID_QA) - 1 from QualiteAir) and ID_HUMI = (SELECT COUNT(ID_HUMI) - 1 from Humidite) and ID_QA = (SELECT COUNT(ID_QA) - 1 from QualiteAir) and ID = (SELECT COUNT(ID) from Seuil) and ID_ETAT = (SELECT COUNT(ID_ETAT) from Etat)");//`CO2`, `Temperature`, `Humidite`, `QualiteAir`
  
  // Etape 5 : exploitation du résultat de la requête
    if(res->next())
	{
	
    // Acces par non du champ de la table : ici le champ 'id' que l'on recupère au format string
	TEMP = res->getDouble("TEMPT");
	CO2 = res->getInt("CO2");
	HUMI = res->getInt("HUMI_H");
	QA = res->getInt("QUALITYQ");
	SEUIL_TEMP = res->getInt("temp_seuil");
	SEUIL_CO2 = res->getInt("co2_seuil");
	SEUIL_HUMI = res->getInt("humi_seuil");
	SEUIL_QA = res->getInt("qualite_seuil");
	ETATBOUTON = res->getInt("ETAT");
	AUTOMATIQUE = res->getInt("AUTO");
}


  // On nettoie tout avant de sortir : effacement des pointeurs
  // le pointeur sur le Driver sera effacé tout seul
  delete res;
  delete stmt;
  delete con; 
} catch (sql::SQLException &e) {
  // Gestion des execeptions pour déboggage
  cout << "# ERR: " << e.what();
  cout << " (code erreur MySQL: " << e.getErrorCode();
  cout << ", EtatSQL: " << e.getSQLState() << " )" << endl;
}
 
cout << endl;
 
// on sort en indiquant que tout c'est bien passé
return EXIT_SUCCESS;
}

int main(void)
{
	horaires ljj;
	while(ljj.state())
	{
	Traitement instance;
	instance.connexion();
	
	horaires ljj;
	cout << "L'établissement : "<< ljj.state() << endl;
	//	cout << instance.choix();
	
		reception_433 fenetre;
		bool etat = fenetre.state();
		bool ANCIENETATBOUTON;

		cout << "Etat de la fenetre :" << etat;
	
		emission command;

		if(instance.getAutomatique() == 0)
		{

			if(instance.getEtatBouton() != ANCIENETATBOUTON)
			{
				ANCIENETATBOUTON = instance.getEtatBouton();

				if(instance.getEtatBouton() == 0 && etat == 1)
				{
					command.close();
				}
        
				if(instance.getEtatBouton() == 1 && etat == 0)
				{
					command.open();
				}
			}
			sleep(5);
		}
		else
		{
			if(etat == instance.choix())
			{
				command.wait();
			}
			else
			{
				if(etat == true)
				{
					command.close();
				}
				else
				{
					command.open();
				}
			}
			sleep(5);
		}
	}
}
