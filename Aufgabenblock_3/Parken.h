/*
 * Parken.h
 *
 *  Created on: 27.10.2024
 *      Author: SABINA
 */

#ifndef PARKEN_H_
#define PARKEN_H_
#include "Verhalten.h"

class Parken : public Verhalten{
public:
	Parken(Weg& rWeg, double dparkEndZeit);
	virtual ~Parken();

	double dStrecke(Fahrzeug& aFzg, double dZeitIntervall) override;
	double dGetParkEndZeit() const;

private:
    double p_dParkEndZeit;
};

#endif /* PARKEN_H_ */
