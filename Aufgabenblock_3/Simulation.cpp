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
	int iZeilenzaehler = 0;

	if(bMitGrafik)
	{
		bInitialisiereGrafik(2000, 2000);
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

				//Mit Grafikausgabe
				if(bMitGrafik)
				{
					string sXKoordinate;
					string sYKoordinate;

					iss >> sXKoordinate >> sYKoordinate;
					bZeichneKreuzung(stoi(sXKoordinate), stoi(sYKoordinate));
				}
			}

			else if(sKeyword == "PKW")
			{
				cout << "PKW" << endl;
				string name;
				string sGeschwindigkeit;
				double geschwindigkeit;
				string sVerbrauch;
				double verbrauch;
				string sTankvolumen;
				double tankvolumen;
				string startkreuzungName;
				string sStartzeit;
				double startzeit;

				iss >> name >> sGeschwindigkeit >> sVerbrauch >> sTankvolumen >> startkreuzungName >> sStartzeit;

				geschwindigkeit = stod(sGeschwindigkeit);
				verbrauch = stod(sVerbrauch);
				tankvolumen = stod(sTankvolumen);
				startzeit = stod(sStartzeit);

				unique_ptr<PKW> pkw = make_unique<PKW>(name, geschwindigkeit, verbrauch, tankvolumen);

				if(p_mKreuzungen.count(startkreuzungName))
				{
					p_mKreuzungen[startkreuzungName]->vAnnahme(move(pkw), startzeit);
				}
				else
				{
					throw runtime_error("Kreuzung wurde nicht gefunden");
				}
			}

			else if(sKeyword == "FAHRRAD")
			{
				cout << "Fahrrad" << endl;
				string name;
				string sGeschwindigkeit;
				double geschwindigkeit;
				string startkreuzungName;
				string sStartzeit;
				double startzeit;

				iss >> name >> sGeschwindigkeit >> startkreuzungName >> sStartzeit;

				geschwindigkeit = stod(sGeschwindigkeit);
				startzeit = stod(sStartzeit);

				unique_ptr<Fahrrad> fahrrad = make_unique<Fahrrad>(name, geschwindigkeit);

				if(p_mKreuzungen.count(startkreuzungName))
				{
					p_mKreuzungen[startkreuzungName]->vAnnahme(move(fahrrad), startzeit);
				}
				else
				{
					throw runtime_error("Kreuzung wurde nicht gefunden");
				}
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

				if (p_mKreuzungen.count(nameQuellkreuzung))
				{
					quellkreuzung = p_mKreuzungen[nameQuellkreuzung];
				}
				else
				{
					throw runtime_error("Kreuzung nicht gefunden");
				}

				if (p_mKreuzungen.count(nameZielkreuzung))
				{
					zielkreuzung = p_mKreuzungen[nameZielkreuzung];
				}
				else {
					throw runtime_error("Kreuzung nicht gefunden");
				}

				if(quellkreuzung != nullptr && zielkreuzung != nullptr)
				{
					quellkreuzung->vVerbinde(nameWegQZ, nameWegZQ, laenge, quellkreuzung, zielkreuzung, tempolimit, ueberholverbot);
				}

				//Mit Grafikausgabe
				if(bMitGrafik)
				{
					string sAnzahlKoordinaten;
					iss >> sAnzahlKoordinaten;
					int iAnzahlKoordinaten = stoi(sAnzahlKoordinaten);
					int iKoordinaten[iAnzahlKoordinaten*2];
					string sKoordinate;

					for(int i=0; i<iAnzahlKoordinaten*2; i++)
					{
						iss >> sKoordinate;
						cout << sKoordinate << endl;
						int iKoordinate = stoi(sKoordinate);
						iKoordinaten[i] = iKoordinate;
					}

					bZeichneStrasse(nameWegQZ, nameWegZQ, laenge, iAnzahlKoordinaten, iKoordinaten);
				}
			}

			else
			{
				throw runtime_error(" Fehler in Zeile: "+ to_string(iZeilenzaehler));
			}
		}

		catch(exception& e)
		{
			cout << "Fehler beim Einlesen: " << e.what() << endl;
		}
	}
}

void Simulation::vSimulieren(double dDauer, double dZeitschritt)
{
	double dEndzeit = dGlobaleZeit + dDauer;

	cout << "Simulation gestartet" << endl;

	while(dGlobaleZeit < dEndzeit)
	{
		for (auto& kreuzung : p_vKreuzungen)
		{
			kreuzung->vSimulieren();
		}

		dGlobaleZeit += dZeitschritt;
		vSetzeZeit(dGlobaleZeit);
		vSleep(100);
	}

	cout << "Simulation beendet" << endl;
}
