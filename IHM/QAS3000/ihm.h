#ifndef IHM_H
#define IHM_H

#include <QMainWindow>
#include <string>
#include <QtSql>
#include <iostream>
#include <QApplication>
#include <QPushButton>
#include <QObject>

using namespace std;

namespace Ui {
class IHM;
}

class IHM : public QMainWindow
{
    Q_OBJECT

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

public slots:
    void valeurCO2_valueChanged();
    void valeurTemperature_valueChanged();
    void valeurHumidite_valueChanged();
    void valeurpm25_valueChanged();
    void valeurDate_valueChanged();
    void valeurHeure_valueChanged();
    void dateHeure_valueChanged();
    void codeCache_valueChanged();

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
