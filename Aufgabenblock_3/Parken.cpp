/*
 * Parken.cpp
 *
 *  Created on: 27.10.2024
 *      Author: SABINA
 */

#include "Parken.h"
#include "Losfahren.h"

Parken::Parken(Weg& rWeg, double dparkEndZeit)
	: Verhalten(rWeg),
	  p_dParkEndZeit(dparkEndZeit)
{

}

Parken::~Parken() {
}

double Parken::dStrecke(Fahrzeug& aFzg, double dZeitIntervall)
{
	if(dGlobaleZeit >= p_dParkEndZeit){
		throw Losfahren(aFzg, p_rWeg);
	}
	return 0;
}

double Parken::dGetParkEndZeit() const
{
	return p_dParkEndZeit;
}
