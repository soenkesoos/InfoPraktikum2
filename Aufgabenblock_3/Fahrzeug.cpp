/*
 * Fahrzeug.cpp
 *
 *  Created on: 10.10.2024
 *      Author: SABINA
 */

#include "Fahrzeug.h"
#include "Verhalten.h"
#include "Fahren.h"
#include "Parken.h"
using namespace std;


Fahrzeug::Fahrzeug()
	: Simulationsobjekt()
{
}

Fahrzeug::Fahrzeug(string sName)
	: Simulationsobjekt(sName)
{
	//cout << "Fahrzeug wurde konstruiert" << endl;
	//cout << "Name: " << p_sName << endl;
	//cout << "ID: " << p_iID << endl << endl;
}

Fahrzeug::Fahrzeug(string sName, const double dGeschwindigkeit)
	: Simulationsobjekt(sName),
	  p_dMaxGeschwindigkeit(dGeschwindigkeit > 0 ? dGeschwindigkeit : 0)
{
	//cout << "Fahrzeug wurde konstruiert" << endl;
	//cout << "Name: " << p_sName << endl;
	//cout << "Maximale Geschwindigkeit " << p_dMaxGeschwindigkeit << endl << endl;
}

Fahrzeug::Fahrzeug(Weg& rWeg)
    : Simulationsobjekt(), p_pVerhalten(make_unique<Verhalten>(rWeg))
{
    p_dAbschnittStrecke = 0.0;  // Setzt die Abschnittsstrecke auf 0
}

Fahrzeug::~Fahrzeug() {
	//cout << "Fahrzeug wurde gelöscht" <<endl;
	//cout << "Name: " << p_sName << endl;
	//cout << "ID: " << p_iID << endl << endl;
}

void Fahrzeug::vAusgeben(ostream& o) const
{
	Simulationsobjekt::vAusgeben(o);
	cout << setw(22) << p_dMaxGeschwindigkeit
		 << setw(16) << p_dGesamtStrecke
		 << setw(22) << p_dAbschnittStrecke;
}

void Fahrzeug::vKopf()
{
	cout << setw(7) << setfill(' ') << resetiosflags(ios::right) << setiosflags(ios::left) << "ID"
		 << setw(10) << "Name"
		 << setw(24) << "MaxGeschwindigkeit"
		 << setw(19) << "Gesamtstrecke"
		 << setw(22) << "Abschnittstrecke"
		 << setw(20) << "Gesamtverbrauch"
		 << setw(10) << "Tankinhalt"
		 << setw(115) << setfill('-') << "\n" << "\n";
}

void Fahrzeug::vSimulieren()
{
	if(p_dZeit >= dGlobaleZeit) //gucken, ob Fahrzeug in einem Zeitschritt schon bearbeitet wurde
	{
		return;
	}

	double dZeitdifferenz = dGlobaleZeit - p_dZeit;
	double dStreckenabschnitt = p_pVerhalten->dStrecke(*this, dZeitdifferenz);
	p_dGesamtStrecke += dStreckenabschnitt;
	p_dAbschnittStrecke += dStreckenabschnitt;
	p_dGesamtZeit += p_dZeit;
	p_dZeit = dGlobaleZeit;
}

double Fahrzeug::dTanken(double dMenge)
{
	return 0.0;
}

double Fahrzeug::dGeschwindigkeit() const
{
	return p_dMaxGeschwindigkeit;
}

double Fahrzeug::dGetGeschwindigkeit() const
{
	return p_dMaxGeschwindigkeit;
}

double Fahrzeug::dGetGesamtstrecke() const
{
	return p_dGesamtStrecke;
}

ostream& operator<<(ostream& o, const Fahrzeug& fahrzeug)
{
	fahrzeug.vAusgeben(o);
	return o;
}

bool operator<(Fahrzeug f1, Fahrzeug f2)
{
	if(f1.dGetGesamtstrecke() < f2.dGetGesamtstrecke())
	{
		return true;
	}

	else
	{
		return false;
	}
}

Fahrzeug& Fahrzeug::operator=(const Fahrzeug& fahrzeug)
{
	p_sName = fahrzeug.p_sName + "_copy";
	p_dMaxGeschwindigkeit = fahrzeug.p_dMaxGeschwindigkeit;

	return *this;
}

double Fahrzeug::dGetAbschnittStrecke() const
{
	return p_dAbschnittStrecke;
}

void Fahrzeug::vNeueStrecke(Weg& rWeg)
{
	p_pVerhalten = make_unique<Fahren>(rWeg); //unique Pointer bewirkt, dass alte Instanze gelöscht werden
	p_dAbschnittStrecke = 0.0;
}

void Fahrzeug::vNeueStrecke(Weg& rWeg, double Startzeit)
{
	p_pVerhalten = make_unique<Parken>(rWeg, Startzeit); //unique Pointer bewirkt, dass alte Instanze gelöscht werden
	p_dAbschnittStrecke = 0.0;
}

void Fahrzeug::vZeichnen(const Weg& rWeg) const
{

}

double Fahrzeug::dGetTankinhalt() const
{
	return 0;
}
