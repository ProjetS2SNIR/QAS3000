#ifndef IHM_H
#define IHM_H

// Ajout de bibliothèques néccessaire à la construction du programme. Les bibliothèques commençant par Q sont issues de QT et facilite la création des programmes 

#include <QMainWindow>
#include <string>
#include <QtSql>
#include <iostream>
#include <QApplication>
#include <QPushButton>
#include <QObject>
#include <QWidget>
#include <time.h>
#include <unistd.h>
#include <QTimer>

using namespace std;

// Constructeur de la classe, QT lui donne le namespace Ui

namespace Ui {
class IHM;
}

// La classe IHM qui hérite à la création par QT de la classe QMainWindow

class IHM : public QMainWindow
{
    Q_OBJECT

// Définition des méthodes publics

public:
    explicit IHM(QWidget *parent = nullptr);
    int getCO2();
    float getTemperature();
    int getHumidite();
    int getQA();
    QString getHeure();
    QString getDate();
    QString getDateHeure();
    QString getCodeCache();

    ~IHM();
    int connexion();

// Définition des attributs, en private selon les règles de la POO

private:
    Ui::IHM *ui; 
    QSqlDatabase dbQAS3000;
    int CO2;
    int QA;
    int Hum;
    float Temp;
    bool etat = 0;
    bool automatic = 0;
    QString Heure;
    QString Date;
    QString DateHeure;
    string Code;
    QString CodeCache;

// Définition des méthodes public slots qui permet d'éffectuer des actions sur l'IHM

public slots:
    void valeurCO2_valueChanged();
    void valeurTemperature_valueChanged();
    void valeurHumidite_valueChanged();
    void valeurpm25_valueChanged();
    void valeurDate_valueChanged();
    void valeurHeure_valueChanged();
    void dateHeure_valueChanged();
    void codeCache_valueChanged();

// Définition des méthodes privées slots qui permet d'éffectuer des actions sur l'IHM

private slots:
    void on_boutonAutoOff_clicked();
    void on_boutonAutoOn_clicked();
    void on_boutonActive_clicked();
    void on_boutonValider_clicked();
    void on_bouton1_clicked();
    void on_bouton3_clicked();
    void on_bouton0_clicked();
    void on_bouton2_clicked();
    void on_bouton4_clicked();
    void on_bouton5_clicked();
    void on_bouton6_clicked();
    void on_bouton7_clicked();
    void on_bouton8_clicked();
    void on_bouton9_clicked();
    void on_boutonEffacer_clicked();
};

#endif // IHM_H
