/*
 * Losfahren.h
 *
 *  Created on: 28.10.2024
 *      Author: SABINA
 */

#ifndef LOSFAHREN_H_
#define LOSFAHREN_H_
#include "Fahrausnahme.h"

class Losfahren : public Fahrausnahme{
public:
	Losfahren(Fahrzeug& fahrzeug, Weg& weg);
	virtual ~Losfahren();

	void vBearbeiten() override;
};

#endif /* LOSFAHREN_H_ */
