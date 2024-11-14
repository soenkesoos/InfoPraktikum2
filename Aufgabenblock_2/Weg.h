/*
 * Weg.h
 *
 *  Created on: 21.10.2024
 *      Author: SABINA
 */

#include <list>
#include <memory>
#include <string>
#include <cmath>
#include <limits>

#ifndef WEG_H_
#define WEG_H_
#include "Simulationsobjekt.h"
#include "Tempolimit.h"
#include "vertagt_liste.h"

using namespace std;

extern double dGlobaleZeit;

class Fahrzeug;

class Weg : public Simulationsobjekt {
public:
    Weg();
	Weg(string sName, double dLaenge, Tempolimit dTempolimit); //Möglichkeiten: Innerorts, Landstrasse, Autobahn
    virtual ~Weg();

    virtual void vSimulieren();
    static void vKopf();
    virtual void vAusgeben(ostream& os) const override;
    double getLaenge() const;
    void vAnnahme(unique_ptr<Fahrzeug> pFzg);
    void vAnnahme(unique_ptr<Fahrzeug> pFzg, double dStartzeit);
    double getLimit() const;
    unique_ptr<Fahrzeug> pAbgabe(const Fahrzeug& pFzg);

private:
    double p_dLaenge = 0;
    Tempolimit p_eTempolimit;
    vertagt::VListe<unique_ptr<Fahrzeug>> p_pFahrzeuge;
};
ostream& operator<<(ostream& o, const Weg& weg);

#endif /* WEG_H_ */
