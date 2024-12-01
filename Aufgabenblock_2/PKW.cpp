/*
 * PKW.cpp
 *
 *  Created on: 11.10.2024
 *      Author: SABINA
 */

#include "PKW.h"
#include "Fahrzeug.h"
#include "Verhalten.h"
#include "SimuClient.h"

PKW::PKW(string sName, const double dGeschwindigkeit, const double dVerbrauch)
: Fahrzeug(sName, dGeschwindigkeit), p_dVerbrauch(dVerbrauch)
{
}

PKW::PKW(string sName, const double dGeschwindigkeit, const double dVerbrauch, const double dTankvolumen)
	: Fahrzeug(sName, dGeschwindigkeit),
	  p_dVerbrauch(dVerbrauch),
	  p_dTankvolumen(dTankvolumen),
	  p_dTankinhalt(p_dTankvolumen / 2)

{
}

PKW::~PKW() {
}

double PKW::dTanken(double dMenge)
{
	double dTankFrei = p_dTankvolumen - p_dTankinhalt;
	double dTankVorher = p_dTankinhalt;

	if (dMenge <= dTankFrei)
	{
		p_dTankinhalt += dMenge;
	}

	else
	{
		p_dTankinhalt = p_dTankvolumen; //Volltanken
	}

	return (p_dTankinhalt - dTankVorher);
}

void PKW::vSimulieren()
{
    if (p_dZeit >= dGlobaleZeit)
    {
        return;
    }

    if(p_dTankinhalt <= 0)
	{
		p_dTankinhalt = 0;
		cout << "Der Tank vom Auto " << p_sName << " ist leer!" << endl;
		return;
	}

    Fahrzeug::vSimulieren();

    double dVerbrauch = p_dTankinhalt - (p_dGesamtStrecke * p_dVerbrauch) / 100.0; //durch 100 rechnen, da Verbrauch in L/100km angegeben ist

    if(dVerbrauch < 0)
    {
    	p_dTankinhalt = 0;
		cout << "Der Tank vom Auto " << p_sName << " ist leer!" << endl;
		return;
    }
    p_dTankinhalt -= (p_dGesamtStrecke * p_dVerbrauch) / 100.0;
}

void PKW::vAusgeben(ostream& o) const
{
	Fahrzeug::vAusgeben(o);
	cout << setw(20) << (p_dGesamtStrecke * p_dVerbrauch) / 100 //Gesamtverbrauch
		 << setw(18) << p_dTankinhalt << "\n";
}

double PKW::dGeschwindigkeit() const
{
	if(p_dTankinhalt <= 0)
	{
		return 0;
	}
	else
	{
		return min(p_pVerhalten->getWeg().getLimit(), p_dMaxGeschwindigkeit);
	}
}

void PKW::vZeichnen(const Weg& rWeg) const
{
	bZeichnePKW(p_sName, rWeg.sGetName(),  p_dAbschnittStrecke / rWeg.getLaenge(), p_dMaxGeschwindigkeit, p_dTankinhalt);
}
