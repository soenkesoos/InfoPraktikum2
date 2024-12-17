/*
 * Fahrrad.cpp
 *
 *  Created on: 11.10.2024
 *      Author: SABINA
 */

#include "Fahrrad.h"
#include "Fahrzeug.h"
#include <cmath>
#include "SimuClient.h"
#include "Weg.h"

Fahrrad::Fahrrad()
	: Fahrzeug()
{
}

Fahrrad::Fahrrad(string sName, const double dGeschwindigkeit)
	: Fahrzeug(sName, dGeschwindigkeit)

{

}

Fahrrad::~Fahrrad() {
}

double Fahrrad::dGeschwindigkeit() const
{
	double dAktuelleGeschwindigkeit	= p_dMaxGeschwindigkeit;
	int i20KmStuecke = p_dGesamtStrecke / 20; //Gesamtstrecke in 20km Stücken geteilt

	dAktuelleGeschwindigkeit = pow(0.9, i20KmStuecke) * p_dMaxGeschwindigkeit;

	if(dAktuelleGeschwindigkeit <= 12)
	{
		dAktuelleGeschwindigkeit = 12;
	}
	return dAktuelleGeschwindigkeit;
}

void Fahrrad::vAusgeben(ostream& o) const
{
	Fahrzeug::vAusgeben(o);
	cout << setw(20) << 0.00
		 << setw(18) << 0.00 << "\n";;
}

void Fahrrad::vZeichnen(const Weg& rWeg) const
{
	bZeichneFahrrad(p_sName, rWeg.sGetName() , p_dAbschnittStrecke / rWeg.getLaenge(), dGeschwindigkeit());
}

void Fahrrad::vEinlesen(istream& is)
{
	Fahrzeug::vEinlesen(is);
}
