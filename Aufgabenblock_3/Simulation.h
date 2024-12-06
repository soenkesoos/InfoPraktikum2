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

using namespace std;

class Simulation {
public:
	Simulation();
	virtual ~Simulation();

	void vEinlesen(istream& is);
	void vSimulieren();

private:
};

#endif /* SIMULATION_H_ */
