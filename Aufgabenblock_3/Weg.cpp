/*
 * Weg.cpp
 *
 *  Created on: 21.10.2024
 *      Author: SABINA
 */

#include "Weg.h"
#include "Fahrzeug.h"
#include "Fahrausnahme.h"
#include "Kreuzung.h"

Weg::Weg()
	: Simulationsobjekt(),
	  p_eTempolimit(Tempolimit::Autobahn)
{
}

Weg::Weg(string sName, double dLaenge, Tempolimit dTempolimit)
	: Simulationsobjekt(sName),
	  p_dLaenge(dLaenge),
	  p_eTempolimit(dTempolimit),
	  p_bUeberholverbot(true)
{
}

Weg::Weg(string sName, double dLaenge, Tempolimit dTempolimit, bool bUeberholmoeglichkeit, shared_ptr<Kreuzung> pZielkreuzung, shared_ptr<Weg> pRueckweg)
	: Simulationsobjekt(sName),
	  p_dLaenge(dLaenge),
	  p_eTempolimit(dTempolimit),
	  p_bUeberholverbot(bUeberholmoeglichkeit),
	  p_pZielkreuzung(pZielkreuzung),
	  p_pRueckweg(pRueckweg)
{
}

Weg::~Weg() {
}

void Weg::vSimulieren()
{
	p_pFahrzeuge.vAktualisieren();
	p_dVirtuelleSchranke = p_dLaenge;

    for (auto it = p_pFahrzeuge.begin(); it != p_pFahrzeuge.end(); ++it) {
        try {
            (*it)->vSimulieren();
            (*it)->vZeichnen(*this);;
        }
		catch(Fahrausnahme& e) {
			e.vBearbeiten();
		}
	}
	p_pFahrzeuge.vAktualisieren();
}

void Weg::vKopf()
{
	cout << setw(7) << setfill(' ') << resetiosflags(ios::right) << setiosflags(ios::left) << "ID |"
		 << setw(10) << "Name" << resetiosflags(ios::left) << setiosflags(ios::right) << "|"
		 << setw(15) << resetiosflags(ios::right) << setiosflags(ios::left) << "Laenge"
		 << resetiosflags(ios::left) << setiosflags(ios::right) << "|"
		 << setw(24) << resetiosflags(ios::right) << setiosflags(ios::left) << "Fahrzeuge"
		 << setw(70) << resetiosflags(ios::right) << setiosflags(ios::left) << setfill('-') << "\n" << "\n";
}

void Weg::vAusgeben(ostream& os) const
{
	Simulationsobjekt::vAusgeben(os);
	cout << setw(6) << ":" << setw(10) << p_dLaenge
		 << setw(10) << "(";
	for(auto& fahrzeug : p_pFahrzeuge)
	{
		cout << fahrzeug->sGetName() << " ";
	}
	cout << ")\n";
}

ostream& operator<<(ostream& o, const Weg& weg)
{
	weg.vAusgeben(o);
	return o;
}

double Weg::getLaenge() const
{
	return p_dLaenge;
}

void Weg::vAnnahme(unique_ptr<Fahrzeug> pFzg) //Für fahrende Fahrzeuge
{
	if(pFzg == nullptr)
	{
		return;
	}

	pFzg->vNeueStrecke(*this);
	p_pFahrzeuge.push_back(move(pFzg));
}

void Weg::vAnnahme(unique_ptr<Fahrzeug> pFzg, double dStartzeit) //Für parkende Fahrzeuge
{
	if (pFzg == nullptr)
	{
		return;
	}

	pFzg->vNeueStrecke(*this, dStartzeit);
	p_pFahrzeuge.push_front(move(pFzg));
}

double Weg::getLimit() const
{
	return getTempolimit(p_eTempolimit);
}

unique_ptr<Fahrzeug> Weg::pAbgabe(const Fahrzeug& pFzg)
{
	 /*for (auto it = p_pFahrzeuge.begin(); it != p_pFahrzeuge.end(); ++it)
	 {
		if (*(*it) == pFzg)
		{
			// unique_ptr verschieben und aus der Liste entfernen
			unique_ptr<Fahrzeug> pGefundenesFzg = move(*it);
			p_pFahrzeuge.erase(it);
			return pGefundenesFzg;
		}
	 }
	return nullptr;*/

	for(auto it = p_pFahrzeuge.begin(); it != p_pFahrzeuge.end(); ++it){
		if(*it == nullptr){
			continue;
		}
		if(**it == pFzg){
			unique_ptr<Fahrzeug> tempFz = move(*it);
			p_pFahrzeuge.erase(it);
			return tempFz;
		}
	}
	return nullptr;
}

double Weg::dGetVirtuelleSchranke() const
{
	if(p_bUeberholverbot)
	{
		return p_dVirtuelleSchranke;
	}

	else
	{
		return p_dLaenge;
	}
}

void Weg::vSetVirtuelleSchranke(double dPosition)
{
	p_dVirtuelleSchranke = dPosition;
}

bool Weg::bGetUeberholverbot() const
{
	return p_bUeberholverbot;
}

shared_ptr<Weg> Weg::pGetRueckweg() const
{
	return p_pRueckweg.lock(); //lock() upgradet weak ptr in shared ptr
}

shared_ptr<Kreuzung> Weg::pGetZielkreuzung() const
{
	return p_pZielkreuzung.lock();
}

void Weg::vSetRueckweg(shared_ptr<Weg> pWeg)
{
	p_pRueckweg = pWeg;
}
