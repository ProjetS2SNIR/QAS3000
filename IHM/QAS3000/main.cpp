#include "ihm.h"
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <time.h>
#include <unistd.h>
#include <QTimer>

int main(int argc, char *argv[])
{
    // Création de la l'application, de la fenêtre et affichage

    QApplication a(argc, argv);
    IHM w;
    w.showFullScreen();

    // Connexion à la BDD

    w.connexion();
    
    // Récupération et affichage des valeurs

        w.valeurCO2_valueChanged();
        w.valeurpm25_valueChanged();
        w.valeurTemperature_valueChanged();
        w.valeurHumidite_valueChanged();

        // Récupération et affichage de l'heure et la date

        w.valeurHeure_valueChanged( );
        w.valeurDate_valueChanged();
        w.dateHeure_valueChanged();

        // Actualisation de la chaîne de caractère ****

        QTimer *timer2 = new QTimer(&w);

        QObject::connect(timer2, &QTimer::timeout, &w, QOverload<>::of(&IHM::codeCache_valueChanged));

        timer2->start(500);

        // Actualisation toutes les 30 secondes avec QTimer (threads de QT)

        QTimer *timer = new QTimer(&w);

        QObject::connect(timer, &QTimer::timeout, &w, QOverload<>::of(&IHM::valeurHeure_valueChanged));
        QObject::connect(timer, &QTimer::timeout, &w, QOverload<>::of(&IHM::valeurDate_valueChanged));
        QObject::connect(timer, &QTimer::timeout, &w, QOverload<>::of(&IHM::dateHeure_valueChanged));
        QObject::connect(timer, &QTimer::timeout, &w, QOverload<>::of(&IHM::connexion));
        QObject::connect(timer, &QTimer::timeout, &w, QOverload<>::of(&IHM::valeurTemperature_valueChanged));
        QObject::connect(timer, &QTimer::timeout, &w, QOverload<>::of(&IHM::valeurHumidite_valueChanged));
        QObject::connect(timer, &QTimer::timeout, &w, QOverload<>::of(&IHM::valeurpm25_valueChanged));
        QObject::connect(timer, &QTimer::timeout, &w, QOverload<>::of(&IHM::valeurCO2_valueChanged));

        timer->start(10000);

        return a.exec();
}
