/*
 * Simulation.h
 *
 *  Created on: 06.12.2024
 *      Author: SABINA
 */

#ifndef SIMULATION_H_
#define SIMULATION_H_
#include <iostream>
#include <sstream>
#include <memory>
#include <exception>
#include <stdexcept>
#include <map>
#include <vector>
#include "Kreuzung.h"
#include "PKW.h"
#include "Fahrrad.h"
#include "Weg.h"
#include "Tempolimit.h"
#include "SimuClient.h"

using namespace std;

extern double dGlobaleZeit;

class Simulation {
public:
	Simulation();
	virtual ~Simulation();

	void vEinlesen(istream& is, bool bMitGrafik = false);
	void vSimulieren(double dDauer, double dZeitschritt);

private:
	map<string, shared_ptr<Kreuzung>> p_mKreuzungen; //map sucht nach Kreuzung mit Key value string (name)
	vector<shared_ptr<Kreuzung>> p_vKreuzungen;
};

#endif /* SIMULATION_H_ */
