/*
 * Fahren.cpp
 *
 *  Created on: 27.10.2024
 *      Author: SABINA
 */

#include "Fahren.h"
#include "Streckenende.h"
#include "Losfahren.h"

Fahren::Fahren(Weg& rWeg)
	: Verhalten(rWeg)
{
}

Fahren::~Fahren() {
}


double Fahren::dStrecke(Fahrzeug& aFzg, double dZeitIntervall)
{
	double dMoeglicheStrecke = aFzg.dGetGeschwindigkeit() * dZeitIntervall;
	double dVerbleibendeStrecke = p_rWeg.getLaenge() - aFzg.dGetAbschnittStrecke();

	//if(dMoeglicheStrecke >= dVerbleibendeStrecke)
	//{
	//	cout << "Das Fahrzeug hat schon das Ende des Weges erreicht!" << endl;
	//	return dVerbleibendeStrecke;
	//}

	if (dMoeglicheStrecke >= dVerbleibendeStrecke)
	{
		cout << "Das Fahrzeug hat schon das Ende des Weges erreicht!" << endl;
		throw Streckenende(aFzg, p_rWeg);
		return 0;
	}

	if(dVerbleibendeStrecke < dMoeglicheStrecke){
		return dVerbleibendeStrecke;
	}

	return dMoeglicheStrecke;
}
