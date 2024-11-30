/*
 * Kreuzung.cpp
 *
 *  Created on: 19.11.2024
 *      Author: SABINA
 */

#include "Kreuzung.h"
#include "PKW.h"

Kreuzung::Kreuzung() {
}

Kreuzung::Kreuzung(string sName, double dTankstellenvolumen)
	: Simulationsobjekt(sName),
	  p_dTankstelle(dTankstellenvolumen)
{
}

Kreuzung::~Kreuzung() {
	// TODO Auto-generated destructor stub
}

void Kreuzung::vVerbinde(string sHinweg, string sRueckweg, double dWeglaenge, shared_ptr<Kreuzung> pStartkreuzung, shared_ptr<Kreuzung> pZielkreuzung, Tempolimit eTempolimit, bool bUeberholverbot)
{
	shared_ptr<Weg> pHinweg = std::make_shared<Weg>(sHinweg, dWeglaenge, eTempolimit, bUeberholverbot, pZielkreuzung, nullptr);
	shared_ptr<Weg> pRueckweg = std::make_shared<Weg>(sRueckweg, dWeglaenge, eTempolimit, bUeberholverbot, pStartkreuzung, pHinweg);

	pHinweg->vSetRueckweg(pRueckweg);
	pRueckweg->vSetRueckweg(pHinweg);

	pStartkreuzung->p_pWege.push_back(pHinweg);
	pZielkreuzung->p_pWege.push_back(pRueckweg);
}

void Kreuzung::vTanken(Fahrzeug& rFzg)
{
	PKW* pPKW = dynamic_cast<PKW*>(&rFzg); // Überprüfen, ob das Fahrzeug ein PKW ist
	if (pPKW != nullptr && p_dTankstelle > 0.0)
	{
		double dTankbedarf = pPKW->dGetTankinhalt();
		if (p_dTankstelle >= dTankbedarf)
		{
			pPKW->dTanken(dTankbedarf);
			p_dTankstelle -= dTankbedarf;
		}
		else
		{
			pPKW->dTanken(p_dTankstelle);
			p_dTankstelle = 0.0;
		}
	}
}

void Kreuzung::vAnnahme(unique_ptr<Fahrzeug> pFzg, double dStartzeit)
{
	if (pFzg != nullptr && !p_pWege.empty())
	{
		vTanken(*pFzg); // Fahrzeug an der Kreuzung tanken
		p_pWege.front()->vAnnahme(move(pFzg), dStartzeit);
	}
}

void Kreuzung::vSimulieren()
{
	for (auto& pWeg : p_pWege)
	{
		pWeg->vSimulieren();
	}
}

shared_ptr<Weg> Kreuzung::pZufaelligerWeg(Weg& rWeg)
{
	vector<shared_ptr<Weg>> moeglicheWege;

	for (auto &weg : p_pWege)
	{
		if (weg.get() != &rWeg) // nicht der aktuelle Weg
		{
			moeglicheWege.push_back(weg);
		}
	}

	if (moeglicheWege.empty()) //Sackgasse
	{
	return rWeg.pGetRueckweg();
	}

	static std::mt19937 device(0);
	uniform_int_distribution<int> dist(0, moeglicheWege.size()-1);
	int zuf = dist(device);
	return moeglicheWege[zuf];
}

double Kreuzung::dGetTankstelleninhalt() const
{
	return p_dTankstelle;
}
