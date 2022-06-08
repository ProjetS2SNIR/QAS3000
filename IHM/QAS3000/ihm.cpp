// Include des fichiers .h dont on a besoin pour définir les méthodes, car on a seulement des méthodes déclarées et des attributs

#include "ihm.h"
#include "ui_ihm.h"

// Ajout du namespace std pour ne pas répeter à chaque fois std:: sur la bibliothèque <iostream>

using namespace std;

// Définition du constructeur de l'interface, généré automatiquement par QT. Elle permet la création de l'application à la création de l'objet IHM.

IHM::IHM(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::IHM)
{
    ui->setupUi(this);
}

// On définit ici tout les setters qui modifie les valeurs dans l'interface. On récupére les infos de ui_ihm.h et on modifie les valeurs avec setText qui est une action de SLOT et des getters
// C'est avec les SLOTS et les SIGNAUX qu'on va effectuer des actions à travers notre interface.

void IHM::codeCache_valueChanged()
{
    ui->codeCache->setText(getCodeCache());
}

void IHM::valeurCO2_valueChanged()
{
    ui->valeurCO2->setText(QString::number(getCO2()));
}

void IHM::valeurTemperature_valueChanged()
{
    ui->valeurTemperature->setText(QString::number(getTemperature()));
}

void IHM::valeurHumidite_valueChanged()
{
    ui->valeurHumidite->setText(QString::number(getHumidite()));
}

void IHM::valeurpm25_valueChanged()
{
    ui->valeurpm25->setText(QString::number(getQA()));
}

void IHM::valeurHeure_valueChanged()
{
    ui->heure->setText(getHeure());
}

void IHM::valeurDate_valueChanged()
{
    ui->date->setText(getDate());
}

void IHM::dateHeure_valueChanged()
{
    ui->dateHeure->setText(getDateHeure());
}

// Desctructeur de la classe IHM qui permet de libérer l'espace mémoire après que l'objet ne soit plus utilisé

IHM::~IHM()
{
    delete ui;
}

// Méthode qui permet de nous connecter à la base de données et en extraire les informations qui nous intéresse.
// On va aussi insérer des valeurs dans la base de données pour la partie bouton de l'interface, afin de donner des insctructions aux programmes

int IHM::connexion()
{
    dbQAS3000 = QSqlDatabase::addDatabase("QMYSQL"); // Connexion via QMYSQL, un outil de QT qui permet de spécifier qu'on utilise une BD base de données MYSQL
    dbQAS3000.setHostName("192.168.2.128"); // On spécifie l'IP d'où est situé la base de données
    dbQAS3000.setDatabaseName("QAS3000"); // On indique le nom de la base de données dans laquel on veut entrer
    dbQAS3000.setUserName("mathieu"); // On indique un nom d'utilisateur pour se connecter
    dbQAS3000.setPassword("projet2022"); // On indique le mot de passe correponsdant au nom d'utilisateur
    dbQAS3000.setPort(3306); // On indique le port correspondant à la connexion

    if (dbQAS3000.open()) // On ouvre la base de données, si il y a un problème, on passera dans le else qui enverra un message d'erreur
    {
        qDebug() << "Ouverture de la base de donnée";
        
        QSqlQuery requete; // Variable qui va contenir la requête
        
        // On lance ici, une grande requête SQL qui va chercher les valeurs dont nous avons besoin. On prend la dernière valeur entrée dans la base de données
        
        if(requete.exec("SELECT CO2, TEMPT, HUMI_H, QUALITYQ FROM CO2, Temperature, Humidite, QualiteAir WHERE ID_CO2 = (SELECT COUNT(ID_CO2) + 2 FROM CO2) AND ID_TEMP = (SELECT COUNT(ID_TEMP) - 1 FROM Temperature) AND ID_HUMI = (SELECT COUNT(ID_HUMI) - 1 FROM Humidite) AND ID_QA = (SELECT COUNT(ID_QA) - 1 FROM QualiteAir)")) //,`QualiteAir`,`Humidite`
        {
            qDebug() << "Requête ok";
            if(requete.next()){
                    // On spécifie quels valeurs on récupère et on les converties avec toInt et toFloat selon la valeur récupérées. On les ranges dans les attribtus correspondants
                     CO2 = requete.value("CO2").toInt();
                     Temp = requete.value("TEMPT").toFloat();
                     Hum = requete.value("HUMI_H").toInt();
                     QA = requete.value("QUALITYQ").toInt();
            }
        }
        else
        {
            qDebug() << "Erreur requête \n" << requete.lastError(); // L'erreur est récupéré avec lastError et est affiché avec qDebug
        }
        
        // On lance ici, une autre requête SQL permettant l'insertion des valeurs correspondant aux boutons auto et on/off dans la base de données
        
         if(requete.exec("INSERT INTO `Etat`(`AUTO`,`ETAT`)"" VALUES(" + QString::number(automatic) + ','+ QString::number(etat) +')')) //"+ automatic +""+ etat +"
         {
             cout << automatic << "et" << etat << endl;
            qDebug() << "Requête ok";
         }
         else
         {
            qDebug() << "Erreur requête \n" << requete.lastError();
         }
        // Quand la méthode est terminée, on ferme la base de données
        dbQAS3000.close();
    }
    else
    {
        qDebug() << "Echec ouverture de la BDD";
        qDebug() << dbQAS3000;
    }
    return 0;
}

// On définit ici des getters pour nos attributs, on s'en servira dans les méthodes définits plus tôt permettant l'affichage des valeurs

int IHM::getCO2()
{
    return CO2;
}

float IHM::getTemperature()
{
    return Temp;
}

int IHM::getHumidite()
{
    return Hum;
}

int IHM::getQA()
{
    return QA;
}

// Les méthodes suivantes sont également des getters, mais les valeurs ne sont pas récupérées dans la base de données, on les récupères avec la méthode de QT currentDateTIme.
// On convertis les variables en string avec toString avant de les inclure dans les variables correspondantes

QString IHM::getHeure()
{
    QString Heure = QDateTime::currentDateTime().toString("HH:mm");
    return Heure;
}

QString IHM::getDate()
{
    QString Date = QDateTime::currentDateTime().toString("dd / MM / yyyy");
    return Date;
}

QString IHM::getDateHeure()
{
    QString DateHeure = QDateTime::currentDateTime().toString("HH : mm | dd / MM / yyyy");
    return DateHeure;
}

QString IHM::getCodeCache()
{
    return CodeCache;
}

// On définit ici, les méthodes correspondantes aux boutons de l'IHM, si une action sur une variable est effectué alors on le précise ici

// Les valeurs des trois méthodes suivantes servent uniquement au changement d'état de la fenêtre. Ces informations sont envoyées avec le insert into dans la méthode connexion

void IHM::on_boutonAutoOff_clicked()
{
    automatic = 1;
}

void IHM::on_boutonAutoOn_clicked()
{
    automatic = 0;
}

void IHM::on_boutonActive_clicked()
{
    if(etat == 1)
    {
        etat = 0;
    }
    else
    {
        etat = 1;
    }
}

// Cette méthode permet après vérification de la variavle Code si le mot de passe est bon. Dans le cas ou c'est juste, avec les signaux et les slots on va cacher les parties qu'on ne veut plus voir. 

void IHM::on_boutonValider_clicked()
{
    if(Code == "3000")
    {
        QObject::connect(ui->boutonValider,SIGNAL(clicked()), ui->menuVerrouillerPIN, SLOT(hide()));
        QObject::connect(ui->boutonValider,SIGNAL(clicked()), ui->menuVerrouillerHeure, SLOT(hide()));
    }
    else
    {
        Code = "";
        CodeCache = "";
    }
}

// On définit ici, les actions à l'appuis de chaque boutons sur le digicode qui va effectuer une action sur les chaînes de carractères Code (qui permet la vérification) et CodeCache (qui permet un affichage visuel à l'utisalteur)
void IHM::on_bouton1_clicked()
{
    Code += "1";
    CodeCache += "*";
}

void IHM::on_bouton3_clicked()
{
    Code += "3";
    CodeCache += "*";
}

void IHM::on_bouton0_clicked()
{
    Code += "0";
    CodeCache += "*";
}

void IHM::on_bouton2_clicked()
{
    Code += "2";
    CodeCache += "*";
}



void IHM::on_bouton4_clicked()
{
    Code += "4";
    CodeCache += "*";
}

void IHM::on_bouton5_clicked()
{
    Code += "5";
    CodeCache += "*";
}

void IHM::on_bouton6_clicked()
{
    Code += "6";
    CodeCache += "*";
}

void IHM::on_bouton7_clicked()
{
    Code += "7";
    CodeCache += "*";
}

void IHM::on_bouton8_clicked()
{
    Code += "8";
    CodeCache += "*";
}



void IHM::on_bouton9_clicked()
{
    Code += "9";
    CodeCache += "*";
}

void IHM::on_boutonEffacer_clicked()
{
    Code = "";
    CodeCache = "";
}

void IHM::on_boutonDeco_clicked()
{
    qApp->quit();
    QProcess::startDetached(qApp->arguments()[0], qApp->arguments());

}
