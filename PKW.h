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
	PKW(string sName, const double dGeschwindigkeit, const double dVerbrauch, const double dTankvolumen);
	virtual ~PKW();

	virtual double dTanken(double dMenge = numeric_limits<double>::infinity());
	virtual void vSimulieren(double dGlobaleZeit) override;
	virtual void vAusgeben() const override;
	virtual double dGeschwindigkeit() override;

private:
	const double p_dVerbrauch = 0; //in Liter/100km
	const double p_dTankvolumen = 0;
	double p_dTankinhalt = 0; // in Liter
};

#endif /* PKW_H_ */
