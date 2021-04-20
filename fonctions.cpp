#include "fonctions.h"

bool is_readable( const std::string & file ) {
    std::ifstream fichier(file.c_str());
    return !fichier.fail();
}


void aff(std::string strd, std::string strm, std::string strf, std::string ch, int taille) {
    std::string chaine = strd;
    int len = (taille - strf.size() - strd.size() + 1), cpt = 0, len2 = floor((len-strm.size())/2);
    for (int i = 0; i < len; i++) {
        if (i < len2 || i > (len2+strm.size())) {
            chaine += ch;
        } else if (cpt < 1) {
            cpt += 1;
            chaine += strm;
        }
    }
    chaine += (strf + "\n");
    std::cout << chaine;
}

void grand_titre(std::string title) {
    std::cout << "\n\n";
    aff("|", "", "|");

    for(int i=0; i < title.size(); i++) {
        title[i] = std::toupper(title[i]);
    }

    aff("|", title, "|", " ");
    aff("|", "", "|");
    std::cout << "\n\n";
}

int menu_championnat(){
    std::cout << "\n\n";
    aff("|", "", "|");
    aff("|", "MENU CHAMPIONNAT", "|", " ");
    aff("|", "", "|");
    std::cout << "\n\n";
    aff("", "1. Voir les championnats", "", " ");
    aff("", "2. Ajouter un championnat", "", " ");
    //aff("", "3. Modifer un championnat", "", " ");
    //aff("", "  4. Supprimer un championnat", "", " ");
    std::cout << "\n\nVeuillez entrer votre choix: " << std::endl;
    int c = -1;
    std::cin >> c;
    system("cls");
    return c;
}


int good_choix_score(int id, std::vector<int> liste_id_renc) {
    for(int i_liste_id_renc=0; i_liste_id_renc < liste_id_renc.size(); ++i_liste_id_renc) {
        if(liste_id_renc[i_liste_id_renc] == id) {
            return i_liste_id_renc;
        }
    }
    return -1;
}

