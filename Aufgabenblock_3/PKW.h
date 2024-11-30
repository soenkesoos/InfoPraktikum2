/*
 * PKW.h
 *
 *  Created on: 11.10.2024
 *      Author: SABINA
 */

#ifndef PKW_H_
#define PKW_H_
#include "Fahrzeug.h"
#include <limits>

class PKW : public Fahrzeug
{
public:
	PKW(string sName, const double dGeschwindigkeit, const double dVerbrauch);
	PKW(string sName, const double dGeschwindigkeit, const double dVerbrauch, const double dTankvolumen);
	virtual ~PKW();

	double dTanken(double dMenge = numeric_limits<double>::infinity()) override;
	void vSimulieren() override;
	void vAusgeben(ostream& o) const override;
	double dGeschwindigkeit() const override;
	void vZeichnen(const Weg& rWeg) const override;
	double dGetTankinhalt() const override;

private:
	const double p_dVerbrauch = 0; //in Liter/100km
	const double p_dTankvolumen = 55;
	double p_dTankinhalt = 55/2; // in Liter
};

#endif /* PKW_H_ */
