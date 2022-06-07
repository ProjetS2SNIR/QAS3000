#!/bin/bash

############################################
# Application qui permet de configurer le  #
# proxy                                    #
# ######################################## #
# Le programme est à lancer en sudo	   #
############################################

proxy="10.0.0.1"
port="3128"
chemin="/etc/environment"
if [ $(whoami) != "root" ]
then
	echo "Le programme doit être lancé en tant que root"
	exit 1
fi
# Installation de zenity
apt-get install zenity

retour=$(zenity --entry --title="Action à faire" --text="Que voulez vous faire ?" "Installer le proxy" "Supprimer le proxy")

if [ "$retour" == "Installer le proxy" ]
then
	# Recupération du login et mdp etudiant
	identifiant=$(zenity --entry --title="Identifiant Serveur" --text="Saisissez votre login")

	mdp=$(zenity --password --title="Mot de passe Serveur" --text="Saisissez votre mot de passe")

	# Ajout du proxy aux variables d'environnement

	echo "export http_proxy=\"http://$identifiant:$mdp@$proxy:$port\"">>$chemin
	echo "export https_proxy=\"http://$identifiant:$mdp@$proxy:$port\"">>$chemin
	echo "export ftp=\"http://$identifiant:$mdp@$proxy:$port\"">>$chemin
	echo "export no_proxy=\"localhost, 127.0.0.1, 192.168.2.0/24\"">>$chemin
else
	rm -f $chemin	
fi
reboot
