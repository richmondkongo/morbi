#ifndef RENCONTRER_H_INCLUDED
#define RENCONTRER_H_INCLUDED
#include <string>
#include <iostream>
#include <regex>

#include "../sql/db.h"
#include "../sql/db_equipe.h"
#include "../fonctions.h"

class rencontrer {
    public:
        int id_ren=-1, eq_1=-1, eq_2=-1, score_1=-1, score_2=-1, num_journee=-1;
        std::string jour;
        std::string libelle_1="#", libelle_2="#";
        rencontrer(int _id_ren, std::string _jour, int _eq_1=-1, int _eq_2=-1, int _score_1=-1, int _score_2=-1, int num_journee=1);
        rencontrer(int id_chp);
        rencontrer(int _id_ren, std::string _jour, int _eq_1, int _eq_2, int _score_1, int _score_2, int _num_journee, std::string _libelle_1, std::string _libelle_2);
        //rencontrer(int id_ren, std::string jour, std::string score_1, std::string score_2, int eq_2, int eq_1, int num_journee, \
                   int id_chp, std::string libelle, std::string pays, std::string division, int saison, int id_eq, std::string libelle, int id_chp);

        bool exist_eq(int id_chp, int id_eq);
        bool good_date(std::string d);
};
    //rencontrer r(1, "28/01/2021", 5, 1);

    //cout << "Insertion de donnee: " << ins_rencontrer(r) << endl;
    //cout << "Suppression d'une donnee: " << del_rencontrer(1) << endl;
    //cout << "Modification d'une donnee: " << upd_rencontrer(r) << endl;

    //vector<rencontrer> c = sel_rencontrer();
    //for (int i=0; i < c.size(); i++) {
    //    cout << "id:" << c[i].id_ren << "\njour:" << c[i].jour << endl;
    //}
#endif // RENCONTRER_H_INCLUDED
