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

extern double dGlobaleZeit;

class Fahrzeug;
class Kreuzung;

class Weg : public Simulationsobjekt {
public:
    Weg();
	Weg(string sName, double dLaenge, Tempolimit dTempolimit); //Möglichkeiten Tempolimit: Innerorts, Landstrasse, Autobahn
	Weg(string sName, double dLaenge, Tempolimit dTempolimit, bool bUeberholmoeglichkeit,
		shared_ptr<Kreuzung> pZielkreuzung = nullptr, shared_ptr<Weg> pRueckweg = nullptr);
	virtual ~Weg();

    virtual void vSimulieren();
    static void vKopf();
    virtual void vAusgeben(ostream& os) const override;
    double getLaenge() const;
    void vAnnahme(unique_ptr<Fahrzeug> pFzg);
    void vAnnahme(unique_ptr<Fahrzeug> pFzg, double dStartzeit);
    double getLimit() const;
    unique_ptr<Fahrzeug> pAbgabe(const Fahrzeug& pFzg);
    double dGetVirtuelleSchranke() const;
    void vSetVirtuelleSchranke(double dPosition);
    bool bGetUeberholverbot() const;
    shared_ptr<Weg> pGetRueckweg() const;
    shared_ptr<Kreuzung> pGetZielkreuzung() const;
    void vSetRueckweg(shared_ptr<Weg> pWeg);

private:
    double p_dLaenge = 0;
    Tempolimit p_eTempolimit = Tempolimit::Autobahn;
    vertagt::VListe<unique_ptr<Fahrzeug>> p_pFahrzeuge;
    bool p_bUeberholverbot = true;
    double p_dVirtuelleSchranke = p_dLaenge;
    weak_ptr<Weg> p_pRueckweg;
    const std::weak_ptr<Kreuzung> p_pZielkreuzung;

};
ostream& operator<<(ostream& o, const Weg& weg);

#endif /* WEG_H_ */
