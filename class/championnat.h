#ifndef CHAMPIONNAT_H_INCLUDED
#define CHAMPIONNAT_H_INCLUDED

#include <string>
#include <iostream>


class championnat {
    public:
        int id_chp = -1;
        std::string libelle, pays, division, saison;
        championnat();
        championnat(int id_chp, std::string libelle, std::string pays, std::string division, std::string saison);

};

    //championnat ch(1, "can", "en", "2nd", "saison 3");
    //cout << "Insertion de donnee: " << ins_championnat(ch) << endl;
    //cout << "Suppression d'une donnee: " << del_championnat(5) << endl;
    //cout << "Modification d'une donnee: " << upd_championnat(ch) << endl;

    //vector<championnat> c = sel_championnat();
    //for (int i=0; i < c.size(); i++) {
    //    cout << "id:" << c[i].id_chp << "\nlibelle:" << c[i].libelle << endl;
    //}

#endif // CHAMPIONNAT_H_INCLUDED
