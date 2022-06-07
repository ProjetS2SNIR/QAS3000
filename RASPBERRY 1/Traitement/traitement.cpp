// Commande permettant le lancement du programme
// sudo g++ traitement.cpp -o traitement -Wall -lmysqlcppconn

// Bibliothèques nécessaires au fonctionnement du programme, les bibliothèques cppconn permettent la connexion à une base de données mysql

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
//////////////////////////////////////////////////////////////////////////////////////////
// L'objectif de ce programme est de décider si oui ou non la fenêtre doit être ouverte //
//////////////////////////////////////////////////////////////////////////////////////////

// On include les fichiers permettant la récépetion d'information néccessaire au traitement de l'information

#include "../SMS/reception_433.cpp"
#include "../SMS/horaires.cpp"
#include "emission.cpp"

// On met un namespace std pour éviter d'écrire std:: à chaque utilisation de la bibliothèque iostream

using namespace std;

// Création de la classe Traitement

class Traitement
{
	// On initialise les attributs privés
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
        
	// On initialise les méthodes en public
	
	public :
                int connexion();
		bool choix();
		bool getAutomatique();
		bool getEtatBouton();
		void setEtatBouton(bool valeur);
};

// Création des getters et setters qui va récupérer les informations sur l'état du bouton demandé par l'IHM

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

// Méthode permettant de choisir si oui ou non la fenêtre doit être fermée

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

// Méthode permettant la connexion et la récupération des valeurs que l'on souhaite dans la base de données

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

		  // Etape 2 : connexion à la base choisie
		  con->setSchema("QAS3000");

		  // Etape 3 : création d'un objet qui permet d'effectuer des requêtes sur la base
		  stmt = con->createStatement();

		  // Etape 4 : exécution d'une requete permettant la récupération de toutes les informations sur les valeurs des capteurs, les seuils, et les états des boutons de l'IHM

		  res = stmt->executeQuery("SELECT CO2,TEMPT,HUMI_H,QUALITYQ,temp_seuil,co2_seuil,qualite_seuil,humi_seuil,ETAT,AUTO FROM CO2,Temperature,Humidite,QualiteAir,Seuil,Etat WHERE ID_CO2 = (SELECT COUNT(ID_CO2) + 2 from CO2) and ID_TEMP = (SELECT COUNT(ID_TEMP) - 1 from Temperature) and ID_HUMI = (SELECT COUNT(ID_HUMI) - 1 from Humidite) and ID_QA = (SELECT COUNT(ID_QA) - 1 from QualiteAir) and ID_HUMI = (SELECT COUNT(ID_HUMI) - 1 from Humidite) and ID_QA = (SELECT COUNT(ID_QA) - 1 from QualiteAir) and ID = (SELECT COUNT(ID) from Seuil) and ID_ETAT = (SELECT COUNT(ID_ETAT) from Etat)");//`CO2`, `Temperature`, `Humidite`, `QualiteAir`

		  // Etape 5 : exploitation du résultat de la requête
		    if(res->next())
			{

			    // Acces par nom du champ de la table, on les convertis avec les méthodes getXXX
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
	} 
	
	catch (sql::SQLException &e) {
		  // Gestion des execeptions pour déboggage
		  cout << "# ERR: " << e.what();
		  cout << " (code erreur MySQL: " << e.getErrorCode();
		  cout << ", EtatSQL: " << e.getSQLState() << " )" << endl;
	}

	cout << endl;

	// on sort en indiquant que tout c'est bien passé
	return EXIT_SUCCESS;
}

// Main du programme 

int main(void)
{
	// On crée un objet ljj de la classe horaires
	
	horaires ljj;
	
	// On entre dans la boucle si ljj.state nous dit que nous sommes entre 8h et 18h
	
	while(ljj.state())
	{
		// Création des objets de classe Traitement, horaires, reception et emission
		
		Traitement instance;
		horaires ljj;
		reception_433 fenetre;
		emission command;
		
		// Récupération des valeurs à l'aide de la méthode connexion
		
		instance.connexion();

		cout << "L'établissement : "<< ljj.state() << endl;
		
		//cout << instance.choix();
	
		// On récupère l'etat de la fenêtre selon le programme de reception
		
		bool etat = fenetre.state();
		
		// On crée la variable ANCIENETATBOUTON qui va récupérer l'etat du bouton avant que le nouvel état change
		
		bool ANCIENETATBOUTON;

		cout << "Etat de la fenetre :" << etat;

		// On crée ici selon les variables récupérées des conditions pour savoir si oui on non la fenêtre doit être fermée ou ouverte
		
		// Mode Manuel
		
		if(instance.getAutomatique() == 0)	// Si on récupère de la base de données, la valeur 0 par l'IHM, on passe en mode manuel
		{
			if(instance.getEtatBouton() != ANCIENETATBOUTON) // On compare l'etat du bouton à l'ancien, si il n'est pas le même on entre
			{
				ANCIENETATBOUTON = instance.getEtatBouton();
				
				// On effectue la commande au changement d'état correspondant
				
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
			if(etat == instance.choix()) // SI on récupère une valeur automatique = 1, on passe en mode automatique
			{
				command.wait(); // Dans le cas ou l'état est déjà le même que celui récupéré on ne fait rien
			}
			else
			{
				// On effectue la commande au changement d'état correspondant demandé par le bouton de l'IHM
				
				if(etat == true)
				{
					command.close();
				}
				else
				{
					command.open();
				}
			}
			sleep(5); // On attends 5 secondes pour pas qu'on envoie à l'infini la même insctrution
		}
	}
}
