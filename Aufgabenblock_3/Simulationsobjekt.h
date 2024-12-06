/*
 * Simulationsobjekt.h
 *
 *  Created on: 21.10.2024
 *      Author: SABINA
 */

#ifndef SIMULATIONSOBJEKT_H_
#define SIMULATIONSOBJEKT_H_
#include <iostream>
#include <string>
#include <iomanip>
#include <memory>
using namespace std;

extern double dGlobaleZeit;


class Simulationsobjekt {
public:
	Simulationsobjekt();
	Simulationsobjekt(const std::string& name);
	virtual ~Simulationsobjekt();

	virtual void vAusgeben(ostream& os) const;
	virtual void vSimulieren() = 0;
	virtual void vEinlesen(istream& is);

	Simulationsobjekt(const Simulationsobjekt&) = delete;
	bool operator==(const Simulationsobjekt& obj) const;
	string sGetName() const;

protected:
	string p_sName = "";
	const int p_iID = 0;
	double p_dZeit = 0;

private:
	static int p_iMaxID;

};
ostream& operator<<(std::ostream& os, const Simulationsobjekt& obj);
istream& operator>>(istream& is, Simulationsobjekt& obj);

#endif /* SIMULATIONSOBJEKT_H_ */
