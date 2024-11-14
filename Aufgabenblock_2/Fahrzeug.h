/*
 * Fahrzeug.h
 *
 *  Created on: 10.10.2024
 *      Author: SABINA
 */

#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
#include <memory>
using namespace std;

#ifndef FAHRZEUG_H_
#define FAHRZEUG_H_
#include "Simulationsobjekt.h"
#include "SimuClient.h"

class Verhalten;
class Weg;

extern double dGlobaleZeit;

class Fahrzeug : public Simulationsobjekt {
public:
    // Standard-Konstruktor
	Fahrzeug();
    Fahrzeug(string sName);

    // Konstruktor- Name, max. Geschwindigkeit
    Fahrzeug(string sName, const double dGeschwindigkeit);

    Fahrzeug(Weg& rWeg);

    // Standard-Destruktor
    virtual ~Fahrzeug();

    //Ausgabe Fahrzeugdaten
    virtual void vAusgeben(ostream& o) const override;
    static void vKopf();
    virtual void vSimulieren() override;
    virtual double dTanken(double dMenge = std::numeric_limits<double>::infinity());
    virtual double dGeschwindigkeit() const;
    double dGetGeschwindigkeit() const;
    double dGetGesamtstrecke() const;
    double dGetAbschnittStrecke() const;
    void vNeueStrecke(Weg& rWeg);
    void vNeueStrecke(Weg& rWeg, double dStartzeit);
    virtual void vZeichnen(const Weg& rWeg) const;

    Fahrzeug(const Fahrzeug&) = delete;
    Fahrzeug& operator=(const Fahrzeug& fahrzeug);

protected:
	double p_dMaxGeschwindigkeit = 0;
	double p_dGesamtStrecke = 0;
	double p_dGesamtZeit = 0;
	unique_ptr<Verhalten> p_pVerhalten;
	double p_dAbschnittStrecke = 0; //auf dem aktuellen Weg zurückgelegte Strecke

private:

};
ostream& operator<<(ostream& o, const Fahrzeug& fahrzeug);
bool operator<(Fahrzeug f1, Fahrzeug f2);

#endif /* FAHRZEUG_H_ */
