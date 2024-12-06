/*
 * Simulationsobjekt.cpp
 *
 *  Created on: 21.10.2024
 *      Author: SABINA
 */

#include "Simulationsobjekt.h"

int Simulationsobjekt::p_iMaxID = 0;

Simulationsobjekt::Simulationsobjekt()
	: p_iID(++p_iMaxID)
{
}

Simulationsobjekt::Simulationsobjekt(const string& sName)
	: p_sName(sName),
	  p_iID(++p_iMaxID)
{
}

Simulationsobjekt::~Simulationsobjekt() {
	//cout << "Simulationsobjekt wurde gelöscht" <<endl;
	//cout << "Name: " << p_sName << endl;
	//cout << "ID: " << p_iID << endl << endl;
}

void Simulationsobjekt::vAusgeben(ostream& os) const
{
	cout << setprecision(2) << setiosflags(ios::fixed) << resetiosflags(ios::left) << setiosflags(ios::right) << setw(2) << setfill(' ') << p_iID
	 << setw(10) << p_sName;
}

bool Simulationsobjekt::operator ==(const Simulationsobjekt& obj) const
{
	if(p_iID == obj.p_iID)
	{
		return true;
	}

	else
	{
		return false;
	}
}

string Simulationsobjekt::sGetName() const
{
	return p_sName;
}

void Simulationsobjekt::vEinlesen(istream& is)
{
	if(!p_sName.empty())
	{
		throw runtime_error("Das Objekt wurde bereits initialisiert mit dem Namen: " + p_sName);
	}

	is >> p_sName;
}

ostream& operator<<(ostream& os, const Simulationsobjekt& obj)
{
	obj.vAusgeben(os);
	return os;
}

istream& operator>>(istream& is, Simulationsobjekt& obj)
{
	obj.vEinlesen(is);
	return is;
}
