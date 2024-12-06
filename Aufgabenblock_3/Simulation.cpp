/*
 * Simulation.cpp
 *
 *  Created on: 06.12.2024
 *      Author: SABINA
 */

#include "Simulation.h"

Simulation::Simulation() {
	// TODO Auto-generated constructor stub

}

Simulation::~Simulation() {
	// TODO Auto-generated destructor stub
}

void Simulation::vEinlesen(istream& is)
{
	string sZeile;
	int iZeilenzaehler;
	while(getline(is, sZeile))
	{
		iZeilenzaehler++;
		istringstream iss(sZeile);
		string sKeyword;
		iss >> sKeyword;

		try
		{
			if(sKeyword == "KREUZUNG")
			{

			}
		}

		catch(exception& e)
		{
			cout << "Fehler beim Einlesen" << e.what() << endl;
		}
	}
}

void Simulation::vSimulieren()
{

}
