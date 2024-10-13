/*
 * Fahrzeug.cpp
 *
 *  Created on: 10.10.2024
 *      Author: SABINA
 */

#include "Fahrzeug.h"

int Fahrzeug::p_iMaxID = 0;

Fahrzeug::Fahrzeug(string sName)
	: p_sName(sName),
	  p_iID(++p_iMaxID)
{
	//cout << "Fahrzeug wurde konstruiert" << endl;
	//cout << "Name: " << p_sName << endl;
	//cout << "ID: " << p_iID << endl << endl;
}

Fahrzeug::Fahrzeug(string sName, const double dGeschwindigkeit)
	: p_sName(sName),
	  p_dMaxGeschwindigkeit(dGeschwindigkeit > 0 ? dGeschwindigkeit : 0),
	  p_iID(++p_iMaxID)
{
	//cout << "Fahrzeug wurde konstruiert" << endl;
	//cout << "Name: " << p_sName << endl;
	//cout << "Maximale Geschwindigkeit " << p_dMaxGeschwindigkeit << endl << endl;
}

Fahrzeug::~Fahrzeug() {
	//cout << "Fahrzeug wurde gelöscht" <<endl;
	//cout << "Name: " << p_sName << endl;
	//cout << "ID: " << p_iID << endl << endl;
}

void Fahrzeug::vAusgeben() const
{
	cout << setprecision(2) << setiosflags(ios::fixed) << resetiosflags(ios::left) << setiosflags(ios::right) << setw(2) << setfill(' ') << p_iID
		 << setw(10) << p_sName
		 << setw(22) << p_dMaxGeschwindigkeit
		 << setw(16) << p_dGesamtStrecke;
}

void Fahrzeug::vKopf()
{
	cout << setw(7) << setfill(' ') << resetiosflags(ios::right) << setiosflags(ios::left) << "ID"
		 << setw(10) << "Name"
		 << setw(24) << "MaxGeschwindigkeit"
		 << setw(19) << "Gesamtstrecke"
		 << setw(20) << "Gesamtverbrauch"
		 << setw(10) << "Tankinhalt"
		 << setw(90) << setfill('-') << "\n" << "\n";
}

void Fahrzeug::vSimulieren(double dGlobaleZeit)
{
	if(p_dZeit >= dGlobaleZeit) //gucken, ob Fahrzeug in einem Zeitschritt schon bearbeitet wurde
	{
		return;
	}

	double dZeitdifferenz = dGlobaleZeit - p_dZeit;
	p_dGesamtStrecke += (p_dMaxGeschwindigkeit * dZeitdifferenz); //Strecke = Geschwindigkeit*Zeit
	p_dGesamtZeit += p_dZeit;
	p_dZeit = dGlobaleZeit; //Fahrzeugzeit wird mit globaler Zeit aktualisiert

}

double Fahrzeug::dGeschwindigkeit()
{
	return p_dMaxGeschwindigkeit;
}
