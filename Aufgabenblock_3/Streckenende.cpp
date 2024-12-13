/*
 * Streckenende.cpp
 *
 *  Created on: 28.10.2024
 *      Author: SABINA
 */

#include "Streckenende.h"
#include "Kreuzung.h"
#include "Weg.h"
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
	cout << "Fahrausnahme Streckenende" << endl;

	cout << "ZEIT :" << dGlobaleZeit  << "\n"
			 << "KREUZUNG :" << p_rWeg.pGetZielkreuzung()->sGetName() << " " << p_rWeg.pGetZielkreuzung()->dGetTankstelleninhalt() << "\n"
			 << "WECHSEL :" << p_rWeg.sGetName() << "->" << p_rWeg.pGetRueckweg()->sGetName() <<"\n"
			 << "FAHRZEUG :" << "\n";
	Fahrzeug::vKopf();
	cout << p_rFahrzeug << endl << endl;

	unique_ptr<Fahrzeug> pEntferntesFzg = p_rWeg.pAbgabe(p_rFahrzeug);
	auto pKreuzung = p_rWeg.pGetZielkreuzung();
	std::shared_ptr<Weg> pNeuerweg = pKreuzung->pZufaelligerWeg(p_rWeg);

	pKreuzung->vTanken(p_rFahrzeug);
	pNeuerweg->vAnnahme(move(pEntferntesFzg));
}
