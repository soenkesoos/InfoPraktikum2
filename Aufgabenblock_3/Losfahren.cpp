/*
 * Losfahren.cpp
 *
 *  Created on: 28.10.2024
 *      Author: SABINA
 */

#include "Losfahren.h"
#include "Fahrzeug.h"
#include "Weg.h"

Losfahren::Losfahren(Fahrzeug& fahrzeug, Weg& weg)
	: Fahrausnahme(fahrzeug, weg)
{
	// TODO Auto-generated constructor stub

}

Losfahren::~Losfahren() {
	// TODO Auto-generated destructor stub
}

void Losfahren::vBearbeiten()
{
	cout << "Losfahren Fahrausnahme: Fahrzeug " << p_rFahrzeug.sGetName() << " auf Weg " << p_rWeg.sGetName() << " ist bereit loszufahren."<<endl;
	Fahrzeug::vKopf();
	cout << p_rFahrzeug << endl;
	p_rWeg.vAnnahme(p_rWeg.pAbgabe(p_rFahrzeug));
}
