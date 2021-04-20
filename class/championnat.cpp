#include "championnat.h"

championnat::championnat(int _id_chp, std::string _libelle, std::string _pays, std::string _division, std::string _saison) {
    id_chp = _id_chp;
    libelle = _libelle;
    pays = _pays;
    division = _division;
    saison = _saison;
}

championnat::championnat() {
    std::cout << "libelle: ";
    std::cin >> this->libelle;
    std::cout << "\npays: ";
    std::cin >> this->pays;
    std::cout << "\ndivision: ";
    std::cin >> this->division;
    std::cout << "\nSaison: ";
    std::cin >> this->saison;
    this->id_chp = 0;
}

