/*
 * Fahrausnahme.h
 *
 *  Created on: 28.10.2024
 *      Author: SABINA
 */

#ifndef FAHRAUSNAHME_H_
#define FAHRAUSNAHME_H_
#include <iostream>
#include <exception>
#include <string>
#include "Fahrzeug.h"
#include "Weg.h"
using namespace std;

class Fahrausnahme : public exception{
public:
	Fahrausnahme(Fahrzeug& fahrzeug, Weg& weg);
	virtual ~Fahrausnahme();;

	virtual void vBearbeiten() = 0;

protected:
	Fahrzeug& p_rFahrzeug;
	Weg& p_rWeg;
};

#endif /* FAHRAUSNAHME_H_ */
