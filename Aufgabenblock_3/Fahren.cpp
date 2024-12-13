/*
 * Fahren.cpp
 *
 *  Created on: 27.10.2024
 *      Author: SABINA
 */

#include "Fahren.h"
#include "Streckenende.h"
#include "Losfahren.h"
#include "PKW.h"
#include "Fahrrad.h"

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

	if (dMoeglicheStrecke >= dVerbleibendeStrecke)
	{
		cout << "Das Fahrzeug hat schon das Ende des Weges erreicht!" << endl;
		throw Streckenende(aFzg, p_rWeg);
		return dVerbleibendeStrecke;
	}

	if (p_rWeg.bGetUeberholverbot()) //Überholverbot nachgucken
	{
		if (dynamic_cast<PKW*>(&aFzg))
		{
			// cout <<"Test PKW" << endl;
			// cout << "Test:" << aFzg.dGetAbschnittStrecke() + dMoeglicheStrecke << " "<<p_rWeg.dGetVirtuelleSchranke() << endl;
			if (aFzg.dGetTankinhalt() != 0 && (aFzg.dGetAbschnittStrecke() + dMoeglicheStrecke) > (p_rWeg.dGetVirtuelleSchranke()))
			{
				cout << "Das Fahrzeug kann nicht weiterfahren aufgrund des Überholverbots.\n";
				return (p_rWeg.dGetVirtuelleSchranke() - aFzg.dGetAbschnittStrecke());
			}
		}
		else if (dynamic_cast<Fahrrad*>(&aFzg))
		{
			// cout << "Test Fahrrad" << endl;
			// cout << "Test:" << aFzg.dGetAbschnittStrecke() + dMoeglicheStrecke <<" "<< p_rWeg.dGetVirtuelleSchranke() << endl;
			if ((aFzg.dGetAbschnittStrecke() + dMoeglicheStrecke) > (p_rWeg.dGetVirtuelleSchranke() - 0.001))
			{
				cout << "Das Fahrzeug kann nicht weiterfahren aufgrund des Überholverbots von Fahrrädern.\n";
				return (p_rWeg.dGetVirtuelleSchranke() - aFzg.dGetAbschnittStrecke());
			}
		}
	}

	p_rWeg.vSetVirtuelleSchranke(aFzg.dGetAbschnittStrecke() + dMoeglicheStrecke);
	return dMoeglicheStrecke;

}
