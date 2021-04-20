#include "equipe.h"

equipe::equipe(int _id_eq, std::string _libelle, int _id_chp) {
    id_eq = _id_eq;
    libelle = _libelle;
    id_chp = _id_chp;
}

equipe::equipe(int _id_chp) {
    std::cout << "Nom de l'equipe: ";
    std::cin >> this->libelle;
    id_chp = _id_chp;
}
