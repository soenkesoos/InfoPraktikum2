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

void Simulation::vEinlesen(istream& is, bool bMitGrafik)
{
	string sZeile;
	int iZeilenzaehler;

	if(bMitGrafik)
	{
		//TODO
	}

	while(getline(is, sZeile))
	{
		iZeilenzaehler++;
		cout << "Aktuelle Zeile: " << iZeilenzaehler << endl;;
		istringstream iss(sZeile);
		string sKeyword;
		iss >> sKeyword;

		try
		{
			if(sKeyword == "KREUZUNG")
			{
				cout << "Kreuzung" << endl;
				string name;
				double tankstellenvolumen;
				iss >> name >> tankstellenvolumen;
				shared_ptr<Kreuzung> kreuzung = make_shared<Kreuzung>(name, tankstellenvolumen);

				if(p_mKreuzungen.count(name))
				{
					throw runtime_error("Kreuzung mit dem Namen '" + name + "' existiert bereits.");
					return;
				}
				p_mKreuzungen[name] = kreuzung;
				p_vKreuzungen.push_back(move(kreuzung));
			}

			else if(sKeyword == "PKW")
			{
				cout << "PKW" << endl;
				string name;
				double geschwindigkeit;
				double verbrauch;
				double tankvolumen;
				string startkreuzungName;
				double startzeit;

				iss >> name >> geschwindigkeit >> verbrauch >> tankvolumen >> startkreuzungName >> startzeit;
				unique_ptr<PKW> pkw = make_unique<PKW>(name, geschwindigkeit, verbrauch, tankvolumen);
				p_vFahrzeuge.push_back(move(pkw));
			}

			else if(sKeyword == "FAHRRAD")
			{
				cout << "Fahrrad" << endl;
				string name;
				double geschwindigkeit;
				string startkreuzungName;
				double startzeit;

				iss >> name >> geschwindigkeit >> startkreuzungName >> startzeit;
				unique_ptr<Fahrrad> fahrrad = make_unique<Fahrrad>(name, geschwindigkeit);
				p_vFahrzeuge.push_back(move(fahrrad));
			}

			else if (sKeyword == "STRASSE")
			{
				cout << "Straße" << endl;
				string nameQuellkreuzung;
				string nameZielkreuzung;
				string nameWegQZ;
				string nameWegZQ;
				string sLaenge;
				string sTempolimit;
				string sUeberholverbot;

				iss >> nameQuellkreuzung >> nameZielkreuzung >> nameWegQZ >> nameWegZQ >> sLaenge >> sTempolimit >> sUeberholverbot;

				double laenge = stod(sLaenge);
				Tempolimit tempolimit = Tempolimit::Autobahn;
				if(sTempolimit == "1")
				{
					tempolimit = Tempolimit::Innerorts;
				}
				else if(sTempolimit == "2")
				{
					tempolimit = Tempolimit::Landstrasse;
				}
				else if(sTempolimit == "3")
				{
					tempolimit = Tempolimit::Autobahn;
				}

				bool ueberholverbot = stoi(sUeberholverbot);

				shared_ptr<Kreuzung> quellkreuzung = make_shared<Kreuzung>();
				shared_ptr<Kreuzung> zielkreuzung = make_shared<Kreuzung>();

				std::shared_ptr<Weg> wegQZ = std::make_shared<Weg>(nameWegQZ, laenge, tempolimit, ueberholverbot, zielkreuzung);
				std::shared_ptr<Weg> wegZQ = std::make_shared<Weg>(nameWegZQ, laenge, tempolimit, ueberholverbot, quellkreuzung);

				if(quellkreuzung != nullptr && zielkreuzung != nullptr)
				{
					quellkreuzung->vVerbinde(nameWegQZ, nameWegZQ, laenge, quellkreuzung, zielkreuzung, tempolimit, ueberholverbot);
				}
			}

			else
			{
				throw runtime_error(" Fehler in Zeile: "+ to_string(iZeilenzaehler));
			}
		}

		catch(exception& e)
		{
			cout << "Fehler beim Einlesen" << e.what() << endl;
		}
	}
}

void Simulation::vSimulieren(double dDauer, double dZeitschritt)
{
	double dEndzeit = dGlobaleZeit + dDauer;

	cout << "Simulation gestartet" << endl;

	while(dGlobaleZeit < dEndzeit)
	{
		for (auto& [name, kreuzung] : p_mKreuzungen)
		{
			kreuzung->vSimulieren();
		}
		dGlobaleZeit += dZeitschritt;
	}

	cout << "Simulation beendet" << endl;
}
