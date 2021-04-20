#ifndef EQUIPE_H_INCLUDED
#define EQUIPE_H_INCLUDED
#include <string>
#include <iostream>

class equipe {
    public:
        int id_eq = -1;
        std::string libelle="";
        int point=0, ecart=0, m_nul=0, m_vict=0, m_def=0;
        int id_chp = -1;
        equipe(int id_eq, std::string libelle, int id_chp);
        equipe(int _id_chp);
};

    //equipe e(1, "elephant", 2);
    //cout << "Insertion de donnee: " << ins_equipe(e) << endl;
    //cout << "Suppression d'une donnee: " << del_equipe(1) << endl;
    //cout << "Modification d'une donnee: " << upd_equipe(e) << endl;

    //vector<equipe> c = sel_equipe();
    //for (int i=0; i < c.size(); i++) {
    //    cout << "id:" << c[i].id_eq << "\nlibelle:" << c[i].libelle << endl;
    //}

#endif // EQUIPE_H_INCLUDED
