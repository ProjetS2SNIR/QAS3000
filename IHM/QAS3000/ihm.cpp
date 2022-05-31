#include "ihm.h"
#include "ui_ihm.h"
#include <QTextEdit>
#include <QTimer>

using namespace std;

IHM::IHM(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::IHM)
{
    ui->setupUi(this);
}

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

IHM::~IHM()
{
    delete ui;
}
int IHM::connexion()
{
    dbQAS3000 = QSqlDatabase::addDatabase("QMYSQL");
    dbQAS3000.setHostName("192.168.2.128");
    dbQAS3000.setDatabaseName("QAS3000");
    dbQAS3000.setUserName("mathieu");
    dbQAS3000.setPassword("projet2022");
    dbQAS3000.setPort(3306);

    if (dbQAS3000.open())
    {
        qDebug() << "Ouverture de la base de donnée";
        QSqlQuery requete;
        if(requete.exec("SELECT CO2, TEMPT, HUMI_H, QUALITYQ FROM CO2, Temperature, Humidite, QualiteAir WHERE ID_CO2 = (SELECT COUNT(ID_CO2) + 2 FROM CO2) AND ID_TEMP = (SELECT COUNT(ID_TEMP) - 1 FROM Temperature) AND ID_HUMI = (SELECT COUNT(ID_HUMI) - 1 FROM Humidite) AND ID_QA = (SELECT COUNT(ID_QA) - 1 FROM QualiteAir)")) //,`QualiteAir`,`Humidite`
        {
            qDebug() << "Requête ok";
            if(requete.next()){
                     CO2 = requete.value("CO2").toInt();
                     Temp = requete.value("TEMPT").toFloat();
                     Hum = requete.value("HUMI_H").toInt();
                     QA = requete.value("QUALITYQ").toInt();
            }
        }
        else
        {
            qDebug() << "Erreur requête \n" << requete.lastError();
        }

         if(requete.exec("INSERT INTO `Etat`(`AUTO`,`ETAT`)"" VALUES(" + QString::number(automatic) + ','+ QString::number(etat) +')')) //"+ automatic +""+ etat +"
         {
             cout << automatic << "et" << etat << endl;
            qDebug() << "Requête ok";
         }
         else
         {
            qDebug() << "Erreur requête \n" << requete.lastError();
         }

        dbQAS3000.close();
    }
    else
    {
        qDebug() << "Echec ouverture de la BDD";
        qDebug() << dbQAS3000;
    }
    return 0;
}

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
