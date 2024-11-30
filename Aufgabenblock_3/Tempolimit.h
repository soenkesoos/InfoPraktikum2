/*
 * Tempolimit.h
 *
 *  Created on: 22.10.2024
 *      Author: SABINA
 */

#ifndef TEMPOLIMIT_H_
#define TEMPOLIMIT_H_
#include <iostream>
#include <limits>
using namespace std;

enum class Tempolimit {
    Innerorts = 50,
    Landstrasse = 100,
    Autobahn = numeric_limits<int>::max() // Unbegrenztes Tempolimit
};

// Konvertierungsfunktion
inline double getTempolimit(Tempolimit limit) {
    switch (limit) {
        case Tempolimit::Innerorts: return 50.0;
        case Tempolimit::Landstrasse: return 100.0;
        case Tempolimit::Autobahn: return numeric_limits<double>::max(); // Unbegrenzte Geschwindigkeit
        default: return numeric_limits<double>::max();
    }
}


#endif /* TEMPOLIMIT_H_ */
