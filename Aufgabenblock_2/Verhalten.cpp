/*
 * Verhalten.cpp
 *
 *  Created on: 22.10.2024
 *      Author: SABINA
 */

#include "Verhalten.h"

Verhalten::Verhalten(Weg& rWeg)
	: p_rWeg(rWeg)
{
}

Verhalten::~Verhalten() {
}

double Verhalten::dStrecke(Fahrzeug& aFzg, double dZeitIntervall)
{
	double dMoeglicheStrecke = aFzg.dGetGeschwindigkeit() * dZeitIntervall;
	double dVerbleibendeStrecke = p_rWeg.getLaenge() - aFzg.dGetAbschnittStrecke();

	if(dMoeglicheStrecke >= dVerbleibendeStrecke)
	{
		cout << "Das Fahrzeug hat schon das Ende des Weges erreicht!" << endl;
		return dVerbleibendeStrecke;
	}

	return dMoeglicheStrecke;
}

Weg& Verhalten::getWeg() const
{
	return p_rWeg;
}
