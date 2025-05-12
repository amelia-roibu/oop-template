#include "../include/tariGlobal.h"
#include <fstream>
#include "../include/nlohmann/json.hpp"  // dacă aici parsezi JSON-ul
using json = nlohmann::json;
#include <algorithm>
#include <random>
#include <iostream>

TariGlobal::TariGlobal() {
    std::ifstream file("resurse/tari.json");
    if (!file.is_open())
        throw std::runtime_error("Nu s-a putut deschide fisierul tari.json");

    json j;
    file >> j;

    for (auto& [numeTara, date] : j.items()) {
        std::string continent = date["continent"];
        std::string capitala = date["capitala"];
        std::string emisfera = date["emisfera"];
        int suprafata = date["suprafata"];

        std::map<std::string, std::vector<std::string>> vecini;
        for (const std::string& directie : {"Nord", "Sud", "Est", "Vest"}) {
            vecini[directie] = date["vecini"][directie].get<std::vector<std::string>>();
        }

        tari[numeTara] = Tari(numeTara, capitala, continent, emisfera, suprafata, vecini);
    }
}

TariGlobal* TariGlobal::instanta = nullptr;

TariGlobal& TariGlobal::getInstance() {
    if (instanta == nullptr)
        instanta = new TariGlobal();
    return *instanta;
}

const Tari& TariGlobal::getTara(const std::string& nume) const {
    auto it = tari.find(nume);
    // try and catch daca nu gasesc tara
    return it->second;
}

std::vector<Tari> TariGlobal::getTariDinContinent(const std::string& continent) const{
    std::vector<Tari> rezultat;
    for (const auto& [nume, tara] : tari)
        if (tara.getContinent() == continent)
            rezultat.push_back(tara);
    return rezultat;
}

std::vector<Tari> TariGlobal::getTariRandom(int nr) const {
    std::vector<Tari> toateTarile;

    for (const auto& [_, tara] : tari)
        toateTarile.push_back(tara);

    std::random_device rd; // genereaza un generator de entropie din surse externe, un fel de seed aleator, mai bun decat rand()
    std::mt19937 gen(rd());
    /* mt19937 e un motor de generare de numere pseudo-aleatoare; numele vine de la „Mersenne Twister”
    primește seed de la rd() — deci va genera o secvență diferită de fiecare dată când rulezi programul. */

    std::shuffle(toateTarile.begin(), toateTarile.end(), gen);

    if (nr > toateTarile.size()) nr = toateTarile.size();
    return std::vector<Tari>(toateTarile.begin(), toateTarile.begin() + nr);

    return toateTarile;
}

bool TariGlobal::existaTara(const std::string& nume) const {
    return tari.find(nume) != tari.end();
}

int main() {
    try {
        auto& db = TariGlobal::getInstance();
        auto tari = db.getTariRandom(1);
        for (const auto& tara : tari)
            std::cout << tara.getNume() << '\n';
    } catch (const std::exception& e) {
        std::cerr << "Eroare: " << e.what() << '\n';
    }
    return 0;
}
