/*
 * Fahrzeug.h
 *
 *  Created on: 10.10.2024
 *      Author: SABINA
 */

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

#ifndef FAHRZEUG_H_
#define FAHRZEUG_H_

class Fahrzeug {
public:
    // Standard-Konstruktor
    Fahrzeug(string sName);

    // Konstruktor- Name, max. Geschwindigkeit
    Fahrzeug(string sName, const double dGeschwindigkeit);

    // Standard-Destruktor
    virtual ~Fahrzeug();

    //Ausgabe Fahrzeugdaten
    virtual void vAusgeben(ostream& o) const;
    static void vKopf();
    virtual void vSimulieren(double dGlobaleZeit);
    virtual double dGeschwindigkeit();
    double dGetGesamtstrecke() const;

    Fahrzeug& operator=(const Fahrzeug& fahrzeug);

protected:
    string p_sName = "";
	const int p_iID = 0;
	double p_dMaxGeschwindigkeit = 0;
	double p_dGesamtStrecke = 0;
	double p_dGesamtZeit = 0;
	double p_dZeit = 0;

private:
    static int p_iMaxID;   // Static member

};
ostream& operator<<(ostream& o, const Fahrzeug& fahrzeug);
bool operator<(Fahrzeug f1, Fahrzeug f2);

#endif /* FAHRZEUG_H_ */
