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
#include <vector>
#include <iomanip>
#include <cmath>
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
			fahrzeug->vSimulieren(dGlobaleZeit);
			fahrzeug->vAusgeben(o);
		}
		dGlobaleZeit += dZeitbruch;
	}

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
			fahrzeug->vSimulieren(dGlobaleZeit);
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
	Fahrzeug Fahrzeug1 = Fahrzeug("Fahrzeug1", 100);
	PKW PKW1 = PKW("PKW1", 200, 5, 50);
	Fahrrad Fahrrad1 = Fahrrad("Fahrrad1", 30);

	cout << "Test Operator <<" << endl;

	cout << Fahrzeug1 << endl;
	cout << PKW1 << endl;
	cout << Fahrrad1 << endl;

	cout << "Test Operator = " << endl;
	Fahrzeug Fahrzeug2 = PKW1;
	cout << Fahrzeug2 << endl;

	while(dGlobaleZeit < 5)
	{
		dGlobaleZeit += 0.1;
		Fahrzeug1.vSimulieren(dGlobaleZeit);
		PKW1.vSimulieren(dGlobaleZeit);
		Fahrrad1.vSimulieren(dGlobaleZeit);
	}

	cout << "Test Operator <" << endl;

	if(PKW1 < Fahrrad1)
	{
		cout << "PKW ist (natürlich) schneller gefahren" << endl;
	}

	else
	{
		cout << "wtf" << endl;
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
	vAufgabe_3();

	return 0;
}
