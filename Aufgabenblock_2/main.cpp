/*
 * main.cpp
 *
 *  Created on: 10.10.2024
 *      Author: SABINA
 */
#include <iostream>
#include <memory>
#include <string>
#include "Fahrzeug.h"
#include "PKW.h"
#include "Fahrrad.h"
#include "Simulationsobjekt.h"
#include "Weg.h"
#include "Tempolimit.h"
#include "Fahrausnahme.h"
#include "SimuClient.h"
#include "vertagt_liste.h"

#include <algorithm>
#include <vector>
#include <iomanip>
#include <cmath>
#include <random>
using namespace std;

//globale Uhr
extern double dGlobaleZeit = 0.0;

void vAufgabe_1()
{
	//statische Erzeugung
	Fahrzeug fahrzeug1("fahrzeug1");

	//dynamische Erzeugung
	Fahrzeug* fahrzeug2 = new Fahrzeug("fahrzeug2");
	delete fahrzeug2;

	//Smartpointer: unique Pointer
	unique_ptr<Fahrzeug> fahrzeug3 = make_unique<Fahrzeug>("fahrzeug3");
	unique_ptr<Fahrzeug> fahrzeug4 = make_unique<Fahrzeug>("fahrzeug4");

	//Smartpointer: shared Pointer
	shared_ptr<Fahrzeug> fahrzeug5 = make_shared<Fahrzeug>("fahrzeug5");
	shared_ptr<Fahrzeug> fahrzeug6 = make_shared<Fahrzeug>("fahrzeug6");

	cout << "Pointer use count: " << fahrzeug6.use_count() << endl;
	shared_ptr<Fahrzeug> fahrzeug6Shared = fahrzeug6;
	cout << "Pointer use count: " << fahrzeug6.use_count() << endl << endl;

	vector<unique_ptr<Fahrzeug>> uniqueVektor;
	uniqueVektor.push_back(move(fahrzeug3));
	uniqueVektor.push_back(move(fahrzeug4));
	uniqueVektor.clear();

	vector<shared_ptr<Fahrzeug>> sharedVektor;
	sharedVektor.push_back(move(fahrzeug5));
	sharedVektor.push_back(fahrzeug6);
	cout << "Pointer use count: " << fahrzeug5.use_count() << endl;
	cout << "Pointer use count: " << fahrzeug6.use_count() << endl << endl;
}


void vAufgabe_1a(ostream& o)
{
	vector<unique_ptr<Fahrzeug>> vectorFahrzeuge;

	for(int i=0; i<3; i++)
	{
		string sName;
		double dGeschwindigkeit;

		cout << "Geben Sie den Namen des Fahrzeuges ein: " << endl;
		cin >> sName;
		cout << "Geben Sie die maximale Geschwindigkeit des Fahrzeuges ein: " << endl;
		cin >> dGeschwindigkeit;

		unique_ptr<Fahrzeug> neuFahrzeug = make_unique<Fahrzeug>(sName, dGeschwindigkeit);
		vectorFahrzeuge.push_back(move(neuFahrzeug));
	}

	double dZeitbruch = 0.1; //also 6 Minuten
	Fahrzeug::vKopf();

	while (dGlobaleZeit <= 1)
	{
		for (auto& fahrzeug : vectorFahrzeuge)
		{
			fahrzeug->vSimulieren();
			fahrzeug->vAusgeben(o);
		}
		dGlobaleZeit += dZeitbruch;
	}

}

double dEpsilon = 0.001;
void vAufgabe_AB1() {

    int l = 0; // Laufindex für gezielte AUsgabe
    vector<int> ausgabe{13};
    double dTakt = 0.4;

    std::vector<unique_ptr<Fahrzeug>> vecFahrzeuge;
    vecFahrzeuge.push_back(make_unique <PKW>("Audi", 231, 11.4));
    vecFahrzeuge.push_back(make_unique <Fahrrad>("BMX", 19.8));
    for (dGlobaleZeit = 0; dGlobaleZeit < 10; dGlobaleZeit += dTakt)
    {
        auto itL = find(ausgabe.begin(), ausgabe.end(), l);
        if (itL != ausgabe.end()) {
            std::cout << std::endl << l <<  " Globalezeit = " << dGlobaleZeit << std::endl;
            Fahrzeug::vKopf();
        }

        for (int i = 0; i < vecFahrzeuge.size(); i++)
        {
            vecFahrzeuge[i]->vSimulieren();
            if (fabs(dGlobaleZeit - 3.0) < dTakt/2)
            {
                vecFahrzeuge[i]->dTanken();
            }
            if (itL != ausgabe.end()) {
                std::cout << *vecFahrzeuge[i] << endl;
            }
        }
        l++;
    }
    char c;
    std::cin >> c;
}


void vAufgabe_2(ostream& o)
{
	vector<unique_ptr<Fahrzeug>> vectorPKWFahrrad;

	int iAnzahlPKWs;
	int iAnzahlFahrraeder;
	double dSimIntervall;

	cout << "Wie viele PKWs sollen erzeugt werden? " << endl;
	cin >> iAnzahlPKWs;

	cout << "Wie viele Fahrräder sollen erzeugt werden? " << endl;
	cin >> iAnzahlFahrraeder;

	cout << "Wie lange soll simuliert werden (in Stunden)? " << endl;
	cin >> dSimIntervall;

	//PKWs erzeugen
	for(int i=0; i<iAnzahlPKWs; i++)
	{
		std::string name = "PKW" + to_string(i + 1);
		double dMaxGeschwindigkeit = 100 + i*10; // Placeholder Werte
		double dVerbrauch = 10 + i;                	//TODO Werteeingabe vom Benutzer
		double dTankvolumen = 50 + i;
		vectorPKWFahrrad.push_back(make_unique<PKW>(name, dMaxGeschwindigkeit, dVerbrauch, dTankvolumen));
	}

	//Fahrräder erzeugen
	for(int i=0; i<iAnzahlFahrraeder; i++)
	{
		std::string name = "Fahrrad" + to_string(i + 1);
		double dMaxGeschwindigkeit = 10 + i; //TODO Werteeingabe vom Benutzer
		vectorPKWFahrrad.push_back(make_unique<Fahrrad>(name, dMaxGeschwindigkeit));
	}

	Fahrzeug::vKopf();
	for (auto& fahrzeug : vectorPKWFahrrad)
	{
		fahrzeug->vAusgeben(o);
	}

	double dZeittakt = 0.1; //Beispielzeittakt 6 Minuten
	double dEpsilon = 0.01; //Toleranzwert

	while(dGlobaleZeit < dSimIntervall)
	{
		dGlobaleZeit += dZeittakt;
		for (auto& fahrzeug : vectorPKWFahrrad)
		{
			fahrzeug->vSimulieren();
			fahrzeug->vAusgeben(o);
		}

		//Volltanken nach 3 Stunden mit Toleranz Epsilon
		if(dGlobaleZeit >= (3 - dEpsilon) && dGlobaleZeit <= (3 + dEpsilon))
		{
			cout << "!!!PKWs werden vollgetankt!!!" << endl;
			for (auto& fahrzeug : vectorPKWFahrrad)
			{
				if (PKW* pkw = dynamic_cast<PKW*>(fahrzeug.get()))
				{
					pkw->dTanken(numeric_limits<double>::infinity());
				}
			}
		}

	}

}

void vAufgabe_3()
{

}

void vAufgabe_4()
{
	Weg autobahn1("A1", 100, Tempolimit::Autobahn);

	autobahn1.vAnnahme(make_unique<Fahrzeug>("Auto1", 100));
	autobahn1.vAnnahme(make_unique<Fahrzeug>("Auto2", 200));

	Weg::vKopf();
	cout << autobahn1;
}

void vAufgabe_5(ostream& o)
{
	Weg w1("Weg1", 100, Tempolimit::Innerorts);
		unique_ptr<Fahrzeug> f1 = make_unique<PKW>("Mini", 180, 5.5, 40);
		unique_ptr<Fahrzeug> f2 = make_unique<PKW>("BMW", 220, 7.5, 60);
		unique_ptr<Fahrzeug> f3 = make_unique<Fahrrad>("Bike", 25);
		w1.vAnnahme(std::move(f1));
		w1.vAnnahme(std::move(f2), 3.0);
		w1.vAnnahme(std::move(f3), 6);
		Weg::vKopf();
		cout << w1 << endl;
		while(dGlobaleZeit < 10){
			dGlobaleZeit += 0.3;
			w1.vSimulieren();
			cout << "---" << endl;
		}
}

void vAufgabe_6()
{
	Weg w1("Hin", 500, Tempolimit::Autobahn);
	Weg w2("Rueck", 500, Tempolimit::Autobahn);
	unique_ptr<Fahrzeug> f1 = make_unique<PKW>("Auto1", 100, 5, 50);
	unique_ptr<Fahrzeug> f2 = make_unique<PKW>("Auto2", 200, 8, 60);
	unique_ptr<Fahrzeug> f3 = make_unique<Fahrrad>("Fahrrad1", 25);
	w1.vAnnahme(move(f1));
	w1.vAnnahme(move(f2), 3.0);
	w1.vAnnahme(move(f3), 0.5); //Verschiedene Startzeiten
	Weg::vKopf();

	bInitialisiereGrafik(800,500);
	vSleep(500);
	int feld[] = { 700, 250, 100, 250};
	int anzahl = 2;
	bZeichneStrasse("Hin", "Rueck", 500, anzahl, feld);
	int x;
	cout << w1 << endl;

	while(dGlobaleZeit < 10){
		dGlobaleZeit += 0.3;
		w1.vSimulieren();
		Weg::vKopf();
		w1.vAusgeben(cout);
		cout << "---\n" << endl;
		vSetzeZeit(dGlobaleZeit);
		vSleep(100);
	}

	cout << "Gebe 1 ein um Fenster zu schließen";
	cin >> x;
	if(x==1)
	{
		vBeendeGrafik();
	}
}

void vAufgabe_6a()
{
	static std::mt19937 device(0);
	std::uniform_int_distribution<int> dist(1,10);
	vertagt::VListe<int> liste1;

	for(int i=0; i<10; i++)
	{
		liste1.push_back(dist(device));
	}
	liste1.vAktualisieren();

	cout << "Inhalt der Liste" << endl; //Liste ausgeben
	for (auto it = liste1.begin(); it != liste1.end(); ++it) {
		cout << *it << " ";
	}
	cout << endl;

	//innerhalb einer Schleife alle Elemente >5 mit erase() löschen
	for (auto it = liste1.begin(); it != liste1.end(); ++it) {
		if (*it > 5) {
			liste1.erase(it);
		}
	}

	//Liste wieder ausgeben
	cout << "Inhalt der Liste" << endl;
	for (auto it = liste1.begin(); it != liste1.end(); ++it) {
		cout << *it << " ";
	}
	cout << endl;

	liste1.vAktualisieren();

	cout << "Inhalt der Liste" << endl;
	for (auto it = liste1.begin(); it != liste1.end(); ++it) {
		cout << *it << " ";
	}
	cout << endl;

	int zuf1 = dist(device);
	int zuf2 = dist(device);
	//Am Anfang und Ende der Liste zwei beliebige Zahlen einfügen und Liste nochmal ausgeben
	liste1.push_front(zuf1);
	liste1.push_back(zuf2);
	liste1.vAktualisieren();
	cout << "Inhalt der Liste 1" << endl;
	for (auto it = liste1.begin(); it != liste1.end(); ++it) {
		cout << *it << " ";
	}

}

int main()
{
	//vAufgabe_1();
	//Fahrzeug::vKopf();

	//Fahrzeug pkw1("PKW1", 40);
	//Fahrzeug auto3("AUTO3", 30);
	//pkw1.vAusgeben();
	//auto3.vAusgeben();

	//vAufgabe_1a();
	//vAufgabe_2(cout);
	//vAufgabe_3();

	//vAufgabe_AB1();
	//vAufgabe_4();
	//vAufgabe_5(cout);
	vAufgabe_6();
	vAufgabe_6a();

	return 0;
}
