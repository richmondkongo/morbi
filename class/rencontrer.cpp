#include "rencontrer.h"

rencontrer::rencontrer(int _id_ren, std::string _jour, int _eq_1, int _eq_2, int _score_1, int _score_2, int _num_jr) {
    id_ren = _id_ren;
    eq_1 = _eq_1;
    eq_2 = _eq_2;
    jour = _jour;
    score_1 = _score_1;
    score_2 = _score_2;
    num_journee = _num_jr;
}

rencontrer::rencontrer(int id_chp) {
    std::cout << "Date du match(sous le format jj/mm/aaaa, exemple 28/01/1900): ";
    int f = 1;
    do {
        if(!good_date(jour) && f>1) {
            std::cout << "\nLe format de votre date est incorrecte, \nla date doit etre sous la forme jj/mm/aaaa\n et doit etre valide: ";
        }
        f += 1;
        std::cin >> this->jour;
    } while(!good_date(jour));

    std::cout << "Id de l'equipe 1: ";
    f = 1;
    do {
        if(!exist_eq(id_chp, eq_1) && f>1) {
            std::cout << "\nCet equipe est inexistante dans la BD, \nassurez-vous d'entrer un identifiant correcte: ";
        }
        f +=1;
        std::cin >> this->eq_1;
    } while (!exist_eq(id_chp, eq_1));
    std::cout << "Id de l'equipe 2: ";

    f = 1;
    do {
        if (f == 1) {
            this->eq_2 = -1000;
        }

        if(!exist_eq(id_chp, eq_2) && f>1) {
            std::cout << "\nCet equipe est inexistante dans la BD, \nassurez-vous d'entrer un identifiant correcte: ";
        }

        if (this->eq_1 == this->eq_2) {
            std::cout << "\nUne equipe ne peut jouer contre elle-meme, \nassurez-vous d'entrer un identifiant correcte: ";
        } else {

        }
        f +=1;
        std::cin >> this->eq_2;
    } while (!exist_eq(id_chp, eq_2)||this->eq_1 == this->eq_2);

    std::cout << "Numero de la journee: ";
    f = 1;
    do {
        if (f>1 && this->num_journee < 1) {
            std::cout << "\nUne journee ne peut etre inferieure a 0, reessayer: ";
        }
        f += 1;
        std::cin >> this->num_journee;
    } while(this->num_journee < 1);


}

rencontrer::rencontrer(int _id_ren, std::string _jour, int _eq_1, int _eq_2, int _score_1, int _score_2, int _num_jr, std::string _libelle_1, std::string _libelle_2) {
    id_ren = _id_ren;
    eq_1 = _eq_1;
    eq_2 = _eq_2;
    jour = _jour;
    score_1 = _score_1;
    score_2 = _score_2;
    num_journee = _num_jr;

    libelle_1 = _libelle_1;
    libelle_2 = _libelle_2;
}

bool rencontrer::exist_eq(int id_chp, int id_eq) {
    return (sel_equipe_by_championnat_and_eq(id_chp, id_eq).size() == 1)?true:false;
}

bool rencontrer::good_date(std::string _date) {
    return (regex_match(_date, std::regex("[0-3][0-9]/[0-1][0-2]/[0-9][0-9][0-9][0-9]"))) ? true: false;
}
