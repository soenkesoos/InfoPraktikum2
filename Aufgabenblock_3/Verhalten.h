/*
 * Verhalten.h
 *
 *  Created on: 22.10.2024
 *      Author: SABINA
 */

#ifndef VERHALTEN_H_
#define VERHALTEN_H_
#include <iostream>
#include <cmath>
#include <algorithm>
#include "Weg.h"
#include "Fahrzeug.h"

class Verhalten {
public:
	Verhalten(Weg& rWeg);
	virtual ~Verhalten();

	virtual double dStrecke(Fahrzeug& aFzg, double dZeitIntervall);
	Weg& getWeg() const;

protected:
	Weg& p_rWeg;

};

#endif /* VERHALTEN_H_ */
