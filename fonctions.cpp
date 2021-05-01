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


int good_choix_score(int id, std::vector<int> liste_id_renc) {
    for(int i_liste_id_renc=0; i_liste_id_renc < liste_id_renc.size(); ++i_liste_id_renc) {
        if(liste_id_renc[i_liste_id_renc] == id) {
            return i_liste_id_renc;
        }
    }
    return -1;
}

bool read_choice(int &N) {
    while (!(std::cin >> N)){
        if ( std::cin.eof() ){
            return false;
        } else if ( std::cin.fail() ) {
            std::cout << "Saisie incorrecte, recommencez : ";
            std::cin.clear();
            std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
        }
    }
    return true;
}

bool is_int(std::string str) {
    return (regex_match(str, std::regex("[0-9]{1,2}"))) ? true: false;
}

void splashscreen(float tps) {
    std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    std::cout << "                                BIENVENUE SUR NOTRE APPLICATION DE GESTION DE CHAMPIONNATS DE FOOTBALL, DENOMMEE:\n\n" << std::endl;
    std::cout << "                                     ....       ...   ..............   ..........       ..........     ...." << std::endl;
    std::cout << "                                     .   .     .  .   .            .   .          .     .         .    .  ." << std::endl;
    std::cout << "                                     .    .   .   .   .   ......   .   .   .....   .    .   ....   .   .  ." << std::endl;
    std::cout << "                                     .      .     .   .   .    .   .   .   .    .  .    .   .  .   .   .  ." << std::endl;
    std::cout << "                                     .  .      .  .   .   .    .   .   .   ......  .    .   ....   .   .  ." << std::endl;
    std::cout << "                                     .  .   .  .  .   .   .    .   .   .   .  .  .      .        .     .  ." << std::endl;
    std::cout << "                                     .  .      .  .   .   .    .   .   .   .   .  .     .   ....   .   .  ." << std::endl;
    std::cout << "                                     .  .      .  .   .   ......   .   .   .    .  .    .   .  .   .   .  ." << std::endl;
    std::cout << "                                     .  .      .  .   .            .   .   .    .  .    .   ....  .    .  ." << std::endl;
    std::cout << "                                     ....      ....   ..............   .....    ....    .........      ...." << std::endl;
    std::cout << "\n\n                                          VEUILLEZ PATIENTER LE TEMPS QUE LES DONNEES SE CHARGENT..." << std::endl;
    sleep(tps);
}


void splashscreen_end(float tps) {
    system("cls");
    std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    std::cout << "                                MERCI D'AVOIR UTILISER NOTRE APPLICATION DE GESTION DE CHAMPIONNATS DE FOOTBALL\n\n" << std::endl;
    std::cout << "                                     ....       ...   ..............   ..........       ..........     ...." << std::endl;
    std::cout << "                                     .   .     .  .   .            .   .          .     .         .    .  ." << std::endl;
    std::cout << "                                     .    .   .   .   .   ......   .   .   .....   .    .   ....   .   .  ." << std::endl;
    std::cout << "                                     .      .     .   .   .    .   .   .   .    .  .    .   .  .   .   .  ." << std::endl;
    std::cout << "                                     .  .      .  .   .   .    .   .   .   ......  .    .   ....   .   .  ." << std::endl;
    std::cout << "                                     .  .   .  .  .   .   .    .   .   .   .  .  .      .        .     .  ." << std::endl;
    std::cout << "                                     .  .      .  .   .   .    .   .   .   .   .  .     .   ....   .   .  ." << std::endl;
    std::cout << "                                     .  .      .  .   .   ......   .   .   .    .  .    .   .  .   .   .  ." << std::endl;
    std::cout << "                                     .  .      .  .   .            .   .   .    .  .    .   ....  .    .  ." << std::endl;
    std::cout << "                                     ....      ....   ..............   .....    ....    .........      ...." << std::endl;
    std::cout << "\n\n                                          NOUS ATTENDONS VOTRE PROCHAIN USAGE AVEC EMPRESSEMENT..." << std::endl;
    sleep(tps);
    exit(0);
}

