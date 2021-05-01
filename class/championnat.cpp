#include "championnat.h"

championnat::championnat(int _id_chp, std::string _libelle, std::string _pays, std::string _division, std::string _saison) {
    id_chp = _id_chp;
    libelle = _libelle;
    pays = _pays;
    division = _division;
    saison = _saison;
}

championnat::championnat() {
    std::cin.ignore();
    std::cout << "libelle: ";
    getline(std::cin, libelle);
    std::cout << "\npays: ";
    getline(std::cin, pays);
    std::cout << "\ndivision: ";
    getline(std::cin, division);
    std::cout << "\nSaison: ";
    getline(std::cin, saison);
    id_chp = 0;
}

