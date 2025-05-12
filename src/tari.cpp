#include "../include/tari.h"
#include <iostream>

// constructori

Tari::Tari() : nume(""), capitala(""), continent(""), emisfera(""), suprafata(0.0), veciniCardinal{} {}

Tari::Tari(const std::string& nume,
           const std::string& capitala,
           const std::string& continent,
           const std::string& emisfera,
           double suprafata,
           const std::map<std::string, std::vector<std::string>>& veciniCardinal) : nume(nume), capitala(capitala), continent(continent), emisfera(emisfera), suprafata(suprafata), veciniCardinal(veciniCardinal) {}

Tari::Tari(const Tari& other) : nume(other.nume), capitala(other.capitala), continent(other.continent), emisfera(emisfera), suprafata(other.suprafata), veciniCardinal(other.veciniCardinal) {}

Tari& Tari::operator=(const Tari& other) {
    if (this != &other) {
        nume = other.nume;
        capitala = other.capitala;
        continent = other.continent;
        emisfera = other.emisfera;
        suprafata = other.suprafata;
        veciniCardinal = other.veciniCardinal;
    }
    return *this;
}

Tari::~Tari() = default;

// getters

std::string Tari::getNume() const {
  return this->nume;
}

std::string Tari::getCapitala() const {
    return this->capitala;
}
std::string Tari::getContinent() const {
    return this->continent;
}
std::string Tari::getEmisfera() const {
    return this->emisfera;
}
double Tari::getSuprafata() const {
    return this->suprafata;
}

std::vector<std::string> Tari::getVeciniPeDirectie(const std::string& directie) const {

  // try and catch directie invalida

  if (directie != ""){
    auto it = veciniCardinal.find(directie);
    if (it != veciniCardinal.end())
        return it->second;
    else
        throw std::invalid_argument("Directie invalida");
  }

  std::vector<std::string> totiVecinii;
  for (const auto& [dir, vecini] : veciniCardinal)
    totiVecinii.insert(totiVecinii.end(), vecini.begin(), vecini.end());
  return totiVecinii;
}

// alte metode

bool Tari::esteVecinCu(const std::string& numeTara) const{
    for (const auto& [dir, vecini] : veciniCardinal)
      for (const auto& vecin : vecini)
        if (vecin == numeTara)
          return true;
    return false;
}

// operatori

std::istream& operator>>(std::istream& in, Tari& tara) {
    std::cout << "Introdu numele tarii: ";
    in >> tara.nume;

    // try catch daca nu gaseste tara (il voi implementa mai tarziu)

    return in;
}


std::ostream& operator<<(std::ostream& out, const Tari& tara) {
    out << "Tara: " << tara.nume << "\n";
    out << "Capitala: " << tara.capitala << "\n";
    out << "Continent: " << tara.continent << "\n";
    out << "Emisfera: " << tara.emisfera << "\n";
    out << "Suprafata: " << tara.suprafata << "\n";
    return out;
}

bool Tari::operator== (const Tari& other) const {
  return this->nume == other.nume;
}

bool Tari::operator!= (const Tari& other) const {
    return !(*this == other);
  }