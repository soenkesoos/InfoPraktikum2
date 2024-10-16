/*
 * Fahrrad.cpp
 *
 *  Created on: 11.10.2024
 *      Author: SABINA
 */

#include "Fahrrad.h"
#include "Fahrzeug.h"
#include <cmath>

Fahrrad::Fahrrad(string sName, const double dGeschwindigkeit)
	: Fahrzeug(sName, dGeschwindigkeit)

{

}

Fahrrad::~Fahrrad() {
}

double Fahrrad::dGeschwindigkeit()
{
	double dAktuelleGeschwindigkeit	= p_dMaxGeschwindigkeit;
	int i20KmStuecke = p_dGesamtStrecke / 20; //Gesamtstrecke in 20km Stücken geteilt

	if(dAktuelleGeschwindigkeit > 12)
	{
		dAktuelleGeschwindigkeit = pow(0.9, i20KmStuecke) * p_dMaxGeschwindigkeit;
	}

	else
	{
		dAktuelleGeschwindigkeit = 12;
	}
	return dAktuelleGeschwindigkeit;
}

void Fahrrad::vAusgeben(ostream& o) const
{
	Fahrzeug::vAusgeben(o);
	cout << setw(20) << 0.00
		 << setw(18) << 0.00 << "\n";
}
