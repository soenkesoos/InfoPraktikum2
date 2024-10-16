/*
 * Fahrrad.h
 *
 *  Created on: 11.10.2024
 *      Author: SABINA
 */

#ifndef FAHRRAD_H_
#define FAHRRAD_H_
#include "Fahrzeug.h"

class Fahrrad : public Fahrzeug
{
public:
	Fahrrad(string sName, const double dGeschwindigkeit);

	virtual ~Fahrrad();

	virtual double dGeschwindigkeit() override;
	virtual void vAusgeben(ostream& o) const override;

private:

};

#endif /* FAHRRAD_H_ */
