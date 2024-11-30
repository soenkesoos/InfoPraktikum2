/*
 * Fahren.h
 *
 *  Created on: 27.10.2024
 *      Author: SABINA
 */

#ifndef FAHREN_H_
#define FAHREN_H_
#include "Verhalten.h"


class Fahren : public Verhalten{
public:
	Fahren(Weg& rWeg);
	virtual ~Fahren();

	double dStrecke(Fahrzeug& aFzg, double dZeitIntervall) override;
};

#endif /* FAHREN_H_ */
