/*
 * Kreuzung.h
 *
 *  Created on: 19.11.2024
 *      Author: SABINA
 */

#ifndef KREUZUNG_H_
#define KREUZUNG_H_
#include <vector>
#include <memory>
#include <random>

#include "Simulationsobjekt.h"
#include "Weg.h"
#include "Fahrzeug.h"
#include "Tempolimit.h"

class Kreuzung : public Simulationsobjekt {
public:
	Kreuzung();
	Kreuzung(string sName, double dTankstellenvolumen = 0);
	virtual ~Kreuzung();

	static void vVerbinde(string sHinweg, string sRueckweg, double dWeglaenge,
						  shared_ptr<Kreuzung> pStartkreuzung, shared_ptr<Kreuzung> pZielkreuzung,
						  Tempolimit eTempolimit, bool bUeberholverbot);
	void vTanken(Fahrzeug& rFzg);
	void vAnnahme(unique_ptr<Fahrzeug> pFzg, double dStartzeit);
	void vSimulieren() override;
	shared_ptr<Weg> pZufaelligerWeg(Weg& rWeg);
	double dGetTankstelleninhalt() const;
	void vEinlesen(istream& is) override;;

private:
	vector<std::shared_ptr<Weg>> p_pWege;
	double p_dTankstelle = 0; //Volumen, das zum Tanken zur Verfügung steht
};

#endif /* KREUZUNG_H_ */
