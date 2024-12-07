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
#include "Kreuzung.h"
#include "Simulation.h"

#include <algorithm>
#include <vector>
#include <iomanip>
#include <cmath>
#include <random>
#include <fstream>
#include <exception>
#include <stdexcept>
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
	vector<unique_ptr<Fahrzeug>> fahrzeuge;
	fahrzeuge.push_back(make_unique<PKW>("Mini", 180, 5.5, 40));
	fahrzeuge.push_back(make_unique<PKW>("BMW", 220, 7.5, 60));
	fahrzeuge.push_back(make_unique<Fahrrad>("Bike", 25));
	Fahrzeug f3("base_fz");

	Fahrzeug::vKopf();
	cout << endl;
	for(auto &f : fahrzeuge){
		cout << *f << endl;
	}
	f3.vAusgeben(cout);cout << endl;
	PKW f4("Audi", 200, 6.5, 50);
	f3 = f4; //copying f4 to f3 from PKW to Fahrzeug (implicit conversion) NOTE! properties of PKW are lost
	f4.vAusgeben(cout);cout << endl;
	f3.vAusgeben(cout);cout << endl;
	while(dGlobaleZeit < 10){
		dGlobaleZeit += 0.5;
		for(auto &f : fahrzeuge){
			f->vSimulieren();
			cout << *f << endl;
		}
	}
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
	Weg w1("Hin", 500, Tempolimit::Autobahn, true);
	Weg w2("Rueck", 500, Tempolimit::Autobahn, true);
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
		vSleep(300);
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

void vAufgabe_6_Teil3()
{
	Weg w1("Hin", 500, Tempolimit::Autobahn);
	Weg w2("Rueck", 500, Tempolimit::Autobahn);
	unique_ptr<Fahrzeug> f1 = make_unique<PKW>("Auto1", 100, 5, 50);
	unique_ptr<Fahrzeug> f2 = make_unique<PKW>("Auto2", 200, 8, 60);
	unique_ptr<Fahrzeug> f3 = make_unique<Fahrrad>("Fahrrad1", 25);
	unique_ptr<Fahrzeug> f4Parkend = make_unique<PKW>("Auto3", 50, 5, 55);
	w1.vAnnahme(move(f1));
	w1.vAnnahme(move(f2));
	w1.vAnnahme(move(f3)); //Verschiedene Startzeiten
	Weg::vKopf();

	bInitialisiereGrafik(800,500);
	vSleep(500);
	int feld[] = { 700, 250, 100, 250};
	int anzahl = 2;
	bZeichneStrasse("Hin", "Rueck", 500, anzahl, feld);
	int x;
	cout << w1 << endl;

	while(dGlobaleZeit < 5){
		dGlobaleZeit += 0.3;
		w1.vSimulieren();
		Weg::vKopf();
		w1.vAusgeben(cout);
		cout << "---\n" << endl;
		vSetzeZeit(dGlobaleZeit);
		vSleep(100);
	}

	w1.vAnnahme(move(f4Parkend), 5);
	w1.vAusgeben(cout);
	cout << dGlobaleZeit << endl;


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

void vAufgabe_7()
{
	shared_ptr<Kreuzung> Kr1 = make_shared<Kreuzung>("Kreuzung1", 0);
	shared_ptr<Kreuzung> Kr2 = make_shared<Kreuzung>("Kreuzung2", 1000);
	shared_ptr<Kreuzung> Kr3 = make_shared<Kreuzung>("Kreuzung3", 0);
	shared_ptr<Kreuzung> Kr4 = make_shared<Kreuzung>("Kreuzung4", 0);

	Kreuzung::vVerbinde("W12", "W21", 40, Kr1, Kr2, Tempolimit::Innerorts, true);
	Kreuzung::vVerbinde("W23a", "W32a", 115, Kr2, Kr3, Tempolimit::Autobahn, false);
	Kreuzung::vVerbinde("W23b", "W32b", 40, Kr2, Kr3, Tempolimit::Innerorts, true);
	Kreuzung::vVerbinde("W24", "W42", 55, Kr2, Kr4, Tempolimit::Innerorts, true);
	Kreuzung::vVerbinde("W34", "W43", 85, Kr3, Kr4, Tempolimit::Autobahn, false);
	Kreuzung::vVerbinde("W44a", "W44b", 130, Kr4, Kr4, Tempolimit::Landstrasse, false);

	bInitialisiereGrafik(1000,800);
	vSleep(500);
	bZeichneKreuzung(680, 40);
	bZeichneKreuzung(680, 300);
	bZeichneKreuzung(680, 570);
	bZeichneKreuzung(320, 300);

	int koordinaten1[] = {680, 40, 680, 300};
	int koordinaten2[] = {680, 300,  850, 300, 970, 390, 970, 500, 850, 570, 680, 570};
	int koordinaten3[] = {680, 300, 680, 570};
	int koordinaten4[] = {680, 300, 320, 300};
	int koordinaten5[] = {680, 570, 500, 570, 350, 510, 320, 420, 320, 300};
	int koordinaten6[] = {320, 300, 170, 300, 70, 250, 80, 90, 200, 60, 320, 150, 320, 300};

	bZeichneStrasse("W12", "W21", 40, 2, koordinaten1);
	bZeichneStrasse("W23a", "W32a", 40, 6, koordinaten2);
	bZeichneStrasse("W23b", "W32b", 40, 2, koordinaten3);
	bZeichneStrasse("W24", "W42", 55, 2, koordinaten4);
	bZeichneStrasse("W34", "W43", 85, 5, koordinaten5);
	bZeichneStrasse("W44a", "W44b", 130, 7, koordinaten6);

	unique_ptr<Fahrzeug> f1 = make_unique<PKW>("Auto1", 40, 5.5, 250);
	unique_ptr<Fahrzeug> f2 = make_unique<Fahrrad>("Fahrrad1", 20);
	Kr1->vAnnahme(move(f1), 0);
	Kr1->vAnnahme(move(f2), 1);

	while(dGlobaleZeit < 10){
		dGlobaleZeit += 0.1;
		Kr1->vSimulieren();
		Kr2->vSimulieren();
		Kr3->vSimulieren();
		Kr4->vSimulieren();
		vSetzeZeit(dGlobaleZeit);
		vSleep(100);
	}

	int x;
	cout << "Gebe 1 ein um Fenster zu schließen";
	cin >> x;
	if(x==1)
	{
		vBeendeGrafik();
	}
}

void vAufgabe_8()
{

	ifstream infile("VO.dat");

	if(!infile)
	{
		throw runtime_error("Error beim Einlesen der Datei!");
		return;
	}
	unique_ptr<PKW> pkw = make_unique<PKW>();
	unique_ptr<Fahrrad> fahrrad = make_unique<Fahrrad>();
	shared_ptr<Kreuzung> kreuzung = make_shared<Kreuzung>();

	Fahrzeug::vKopf();

	try
	{
		infile >> *pkw;
		infile >> *fahrrad;
		infile >> *kreuzung;

		cout << *pkw;
		cout << *fahrrad;
		cout << *kreuzung;
	}

	catch(exception& e)
	{
		cout << "FEHLER" << e.what() << endl;
		return;
	}
}

void vAufgabe_9()
{
	ifstream infile("Simu.dat");

	if(!infile)
	{
		throw runtime_error("Error beim Einlesen der Datei!");
		return;
	}

	try
	{
		Simulation simulation;
		simulation.vEinlesen(infile);

		double dDauer = 10;
		double dZeitschritt = 0.1;
		simulation.vSimulieren(dDauer, dZeitschritt);
		cout << dGlobaleZeit << endl;
	}

	catch(exception& e)
	{
		cout << "FEHLER" << e.what() << endl;
	}
}

void vAufgabe_9a()
{
	ifstream infile("SimuDisplay.dat");

	if(!infile)
	{
		throw runtime_error("Error beim Einlesen der Datei!");
		return;
	}

	try
	{
		Simulation simulation;
		simulation.vEinlesen(infile, true);
		double dDauer = 10;
		double dZeitschritt = 0.25;
		simulation.vSimulieren(dDauer+dGlobaleZeit, dZeitschritt);

		int x;
		cout << "Gebe 1 ein um Fenster zu schließen";
		cin >> x;
		if(x==1)
		{
			vBeendeGrafik();
		}
	}

	catch(exception& e)
	{
		cout << "FEHLER" << e.what() << endl;
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
	//vAufgabe_6();
	//vAufgabe_6a();
	//vAufgabe_6_Teil3();
	//vAufgabe_7();
	//vAufgabe_8();
	//vAufgabe_9();
	vAufgabe_9a();

	return 0;
}
