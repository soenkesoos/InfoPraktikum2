/*
 * Streckenende.cpp
 *
 *  Created on: 28.10.2024
 *      Author: SABINA
 */

#include "Streckenende.h"
using namespace std;

Streckenende::Streckenende(Fahrzeug& fahrzeug, Weg& weg)
	: Fahrausnahme(fahrzeug, weg)
{
	// TODO Auto-generated constructor stub

}

Streckenende::~Streckenende() {
	// TODO Auto-generated destructor stub
}

void Streckenende::vBearbeiten()
{
	unique_ptr<Fahrzeug> pEntferntesFzg = p_rWeg.pAbgabe(p_rFahrzeug);

	cout << "Fahrzeug " << pEntferntesFzg->sGetName() << " wurde am Ende des Weges entfernt." << endl;
}
