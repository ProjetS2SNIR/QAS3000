#include <iostream>
#include <ctime>
#include <string>
#include "horaires.h"
using namespace std;

horaires::horaires(){
  time_t t = time(0);   // get time now
  struct tm* now = localtime(&t);
  // Initialisation de la date et heure  actuelle
  jour = now->tm_wday;
  n_annee = (now->tm_year + 1900);
  n_jour = now->tm_mday;
  n_mois = (now->tm_mon + 1);
  n_heure = now->tm_hour;
  // Initialisation des instances etat et raison
  etat = "on ne sait toujours pas";
  raison = "";

  // Appel de la m�thode qui permet de v�rifier si l'�tablisement est ouvert ou ferm�
  verification();
}

void horaires::soir(){
  // On vérifie si on est pas le week-end
  if (n_heure >= 18 || n_heure <9)
  {
    raison = "Nous sommes le soir, aujourd'hui l'�tablissement est ferm�e";
    etat = "ferm�";
  }
}

void horaires::weekend(){
  // On vérifie si on est pas le week-end
  if (jour == 0){
    raison = "Nous sommes Dimanche, aujourd'hui l'�tablissement est ferm�e";
    etat = "ferm�";
  } 
  if (jour == 6){
    raison = "Nous sommes Samedi, aujourd'hui l'�tablissement est ferm�e";
    etat = "ferm�";
  }
}

void horaires::ete(){
  if (n_mois == 7 || n_mois == 8){
    raison = "L'�tablissement est ferm�e pendant les vacances d'�t�";
    etat = "ferm�";
}   
}

void horaires::toussaint(){
  // Vacances de la Toussaint du 22 octobre au 7 novembre
  if ((n_mois == 10 && n_jour >= 22) || (n_mois == 11 && n_jour < 7)){
    raison = "L'�tablissement est ferm�e pendant les vacances de la Toussaint";
    etat = "ferm�";
  }  
}

void horaires::noel(){
  // Vacances de Noel du 17 décembre au 3 janvier
  if ((n_mois == 12 && n_jour >= 17) || (n_mois == 1 && n_jour < 3)){
    raison = "L'�tablissement est fermée pendant les vacances de Noel";
    etat = "ferm�";
  }  
}

void horaires::fevrier(){
  // Vacances d'Hiver du 18 février au 6 mars
  if ((n_mois == 2 && n_jour >= 18) || (n_mois == 3 && n_jour < 6)){
    raison = "L'�tablissement est ferm�e pendant les vacances de f�vrier";
    etat = "ferm�";
  }  
}

void horaires::paques(){
  // Vacances de P�ques du 18 f�vrier au 6 mars
  if ((n_mois == 2 && n_jour >= 18) || (n_mois == 3 && n_jour < 6)){
    raison = "L'�tablissement est ferm�e pendant les vacances de f�vrier";
    etat = "ferm�";
  }  
}

void horaires::verification(){
      soir();
      weekend();
      ete();
      toussaint();
      noel();
      fevrier();
      paques();
  // Si les méthodes 
      if (etat == "on ne sait toujours pas"){
        etat = "ouvert";
        raison = "D'apr�s la date et l'heure actuelle, l'�tablissement ne peut pas �tre ferm�e";
      } 
}

bool horaires::state(){
	if(etat == "ouvert")
	{
		return true;
	}
	else
	{
		return false;
	}
}
