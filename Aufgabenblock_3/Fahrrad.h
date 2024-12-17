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
	Fahrrad(); //Standardkonstruktor
	Fahrrad(string sName, const double dGeschwindigkeit);

	virtual ~Fahrrad();

	double dGeschwindigkeit() const override;
	void vAusgeben(ostream& o) const override;
	void vEinlesen(istream& is) override;;
	void vZeichnen(const Weg& rWeg) const override;

private:

};

#endif /* FAHRRAD_H_ */
