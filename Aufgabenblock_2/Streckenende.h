/*
 * Streckenende.h
 *
 *  Created on: 28.10.2024
 *      Author: SABINA
 */

#ifndef STRECKENENDE_H_
#define STRECKENENDE_H_
#include "Fahrausnahme.h"

class Streckenende : public Fahrausnahme{
public:
	Streckenende(Fahrzeug& fahrzeug, Weg& weg);
	virtual ~Streckenende();

	void vBearbeiten() override;
};

#endif /* STRECKENENDE_H_ */
