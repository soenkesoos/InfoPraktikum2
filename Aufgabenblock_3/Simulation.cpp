#include "Simulation.h"

Simulation::Simulation() {
	// TODO Auto-generated constructor stub

}

Simulation::~Simulation() {
	// TODO Auto-generated destructor stub
}

void Simulation::vEinlesen(istream &is, bool bMitGrafik) {
	string sZeile;
	int iZeilenzaehler = 0;

	if (bMitGrafik)
		bInitialisiereGrafik(2000, 2000);

	while (getline(is, sZeile)) {
		iZeilenzaehler++;
		cout << "Aktuelle Zeile: " << iZeilenzaehler << "\t" << sZeile;
		istringstream iss(sZeile);
		string sKeyword;
		iss >> sKeyword;

		try {
			if (sKeyword == "KREUZUNG")
				vLeseKreuzung(iss, bMitGrafik);
			else if (sKeyword == "STRASSE")
				vLeseWeg(iss, bMitGrafik);
			else if (sKeyword == "PKW")
				vLesePkw(iss);
			else if (sKeyword == "FAHRRAD")
				vLeseFahrrad(iss);
			else
				throw runtime_error(
						" Fehler in Zeile: " + to_string(iZeilenzaehler));
		} catch (exception &e) {
			cout << "Fehler beim Einlesen: " << e.what() << endl;
		}
	}
}

void Simulation::vLeseKreuzung(istringstream &iss, bool bMitGrafik) {
	cout << "Kreuzung" << endl;
	string name, sTankstellenvolumen;
	iss >> name >> sTankstellenvolumen;
	double tankstellenvolumen = (double) stoi(sTankstellenvolumen);
	shared_ptr<Kreuzung> kreuzung = make_shared<Kreuzung>(name,
			tankstellenvolumen);

	if (p_mKreuzungen.count(name))
		throw runtime_error(
				"Kreuzung mit dem Namen '" + name + "' existiert bereits.");

	p_mKreuzungen[name] = kreuzung;
	p_vKreuzungen.push_back(move(kreuzung));

	if (!bMitGrafik)
		return;
	//Mit Grafikausgabe
	string sXKoordinate, sYKoordinate;
	cout << "Koordinaten" << endl;
	iss >> sXKoordinate >> sYKoordinate;
	bZeichneKreuzung(stoi(sXKoordinate), stoi(sYKoordinate));
}

void Simulation::vLeseWeg(istringstream &iss, bool bMitGrafik) {
	cout << "Straße" << endl;
	string nameQuellkreuzung, nameZielkreuzung, nameWegQZ, nameWegZQ,
			sLaenge, sTempolimit, sUeberholverbot;

	iss >> nameQuellkreuzung >> nameZielkreuzung >> nameWegQZ >> nameWegZQ
			>> sLaenge >> sTempolimit >> sUeberholverbot;

	double laenge = stod(sLaenge);
	Tempolimit tempolimit;
	switch (stoi(sTempolimit)) {
	case 1:
		tempolimit = Tempolimit::Innerorts;
		break;
	case 2:
		tempolimit = Tempolimit::Landstrasse;
		break;
	case 3:
		tempolimit = Tempolimit::Autobahn;
		break;
	default:
		throw runtime_error(
				"Ungültiges Tempolimit '" + sTempolimit
						+ "' gültige Werte: 1, 2, 3");
	}

	bool ueberholverbot = stoi(sUeberholverbot);

	shared_ptr<Kreuzung> quellkreuzung = make_shared<Kreuzung>();
	shared_ptr<Kreuzung> zielkreuzung = make_shared<Kreuzung>();

	shared_ptr<Weg> wegQZ = make_shared<Weg>(nameWegQZ, laenge,
			tempolimit, ueberholverbot, zielkreuzung);
	shared_ptr<Weg> wegZQ = make_shared<Weg>(nameWegZQ, laenge,
			tempolimit, ueberholverbot, quellkreuzung);

	if (p_mKreuzungen.count(nameQuellkreuzung))
		quellkreuzung = p_mKreuzungen[nameQuellkreuzung];
	else
		throw runtime_error("Kreuzung nicht gefunden");

	if (p_mKreuzungen.count(nameZielkreuzung))
		zielkreuzung = p_mKreuzungen[nameZielkreuzung];
	else
		throw runtime_error("Kreuzung nicht gefunden");

	if (quellkreuzung != nullptr && zielkreuzung != nullptr)
		quellkreuzung->vVerbinde(nameWegQZ, nameWegZQ, laenge, quellkreuzung,
				zielkreuzung, tempolimit, ueberholverbot);

	//Mit Grafikausgabe
	if (!bMitGrafik)
		return;

	string sAnzahlKoordinaten;
	iss >> sAnzahlKoordinaten;
	int iAnzahlKoordinaten = stoi(sAnzahlKoordinaten);
	int iKoordinaten[iAnzahlKoordinaten * 2];
	string sKoordinate;

	for (int i = 0; i < iAnzahlKoordinaten * 2; i++) {
		iss >> sKoordinate;
		int iKoordinate = stoi(sKoordinate);
		iKoordinaten[i] = iKoordinate;
	}

	bZeichneStrasse(nameWegQZ, nameWegZQ, laenge, iAnzahlKoordinaten,
			iKoordinaten);

}

void Simulation::vLesePkw(istringstream &iss) {
	cout << "PKW" << endl;
	string name, sGeschwindigkeit, sVerbrauch, sTankvolumen,
			startkreuzungName, sStartzeit;
	double geschwindigkeit, verbrauch, tankvolumen, startzeit;

	iss >> name >> sGeschwindigkeit >> sVerbrauch >> sTankvolumen
			>> startkreuzungName >> sStartzeit;

	geschwindigkeit = stod(sGeschwindigkeit);
	verbrauch = stod(sVerbrauch);
	tankvolumen = stod(sTankvolumen);
	startzeit = stod(sStartzeit);

	cout << "point";
	cout << name << geschwindigkeit << verbrauch << tankvolumen << endl;
	unique_ptr<PKW> pkw = make_unique<PKW>(name, geschwindigkeit, tankvolumen, verbrauch);
	// Achte auf Konstruktorparameter reihenfolge
	cout << "point1";
	if (p_mKreuzungen.count(startkreuzungName)) {
		p_mKreuzungen[startkreuzungName]->vAnnahme(move(pkw), startzeit);
	} else {
		throw runtime_error("Kreuzung wurde nicht gefunden");
	}
}

void Simulation::vLeseFahrrad(istringstream &iss) {
	cout << "Fahrrad" << endl;
	string name, sGeschwindigkeit, startkreuzungName, sStartzeit;
	double geschwindigkeit, startzeit;

	iss >> name >> sGeschwindigkeit >> startkreuzungName >> sStartzeit;

	geschwindigkeit = stod(sGeschwindigkeit);
	startzeit = stod(sStartzeit);

	unique_ptr<Fahrrad> fahrrad = make_unique<Fahrrad>(name,
			geschwindigkeit);

	if (p_mKreuzungen.count(startkreuzungName)) {
		p_mKreuzungen[startkreuzungName]->vAnnahme(move(fahrrad),
				startzeit);
	} else {
		throw runtime_error("Kreuzung wurde nicht gefunden");
	}
}

void Simulation::vSimulieren(double dDauer, double dZeitschritt) {
	double dEndzeit = dGlobaleZeit + dDauer;

	cout << "Simulation gestartet" << endl;

	while (dGlobaleZeit < dEndzeit) {
		for (auto &kreuzung : p_vKreuzungen) {
			kreuzung->vSimulieren();
		}

		dGlobaleZeit += dZeitschritt;
		vSetzeZeit(dGlobaleZeit);
		vSleep(100);
	}

	cout << "Simulation beendet" << endl;
}
