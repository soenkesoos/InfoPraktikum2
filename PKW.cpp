/*
 * PKW.cpp
 *
 *  Created on: 11.10.2024
 *      Author: SABINA
 */

#include "PKW.h"
#include "Fahrzeug.h"

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

void PKW::vSimulieren(double dGlobaleZeit)
{
    if (p_dZeit >= dGlobaleZeit)
    {
        return;
    }

    if (p_dTankinhalt > 0 && (p_dTankinhalt - (p_dGesamtStrecke * p_dVerbrauch)/100) >= 0)
    {
    	p_dTankinhalt -= (p_dGesamtStrecke * p_dVerbrauch) / 100.0; //durch 100 rechnen, da Verbrauch in L/100km angegeben ist
    	Fahrzeug::vSimulieren(dGlobaleZeit);
    }

    else
    {
    	p_dTankinhalt = 0;
    }
}

void PKW::vAusgeben() const
{
	Fahrzeug::vAusgeben();
	cout << setw(20) << (p_dGesamtStrecke * p_dVerbrauch) / 100 //Gesamtverbrauch
		 << setw(18) << p_dTankinhalt << "\n";
}

double PKW::dGeschwindigkeit()
{
	return p_dMaxGeschwindigkeit;
}
