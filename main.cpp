#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <conio.h>
#include <unistd.h>


#include "lib/sqlite/sqlite3.h"
#include "sql/db.h"
#include "sql/db_championnat.h"
#include "sql/db_equipe.h"
#include "sql/db_rencontrer.h"
#include "class/championnat.h"
#include "class/equipe.h"
#include "class/rencontrer.h"
#include "fonctions.h"
#include "lib/ConsoleTable/ConsoleTable.h"

using namespace std;

// fonction de gestion des menus
void action_championnat();
void action_one_championnat(championnat one_chp);
void action_equipe(championnat one_chp);
void action_calendrier(championnat one_chp);
void action_one_calendrier(championnat one_chp, rencontrer one_renc);
void action_resultat(championnat one_chp);
void action_classement(championnat one_chp);
void action_one_resultat(championnat one_chp, rencontrer one_renc);


void action_classement(championnat one_chp) {
    system("cls");
    grand_titre("Classement du championnat " + std::to_string(one_chp.id_chp) + ": " + one_chp.libelle + "(saison=" + one_chp.saison + ")" );
    vector<rencontrer> clas = sel_rencontrer_cal(one_chp.id_chp);
    vector<equipe> eq = sel_equipe_by_championnat(one_chp.id_chp);
    for (int i=0; i < eq.size(); i++) {
        for(int j=0; j < clas.size(); j++) {
            if(clas[j].score_1 != -1||clas[j].score_2 != -1) {
                if(clas[j].eq_1 == eq[i].id_eq) {
                    eq[i].ecart += (clas[j].score_1 - clas[j].score_2);
                    eq[i].point += (clas[j].score_1 > clas[j].score_2)? 3: ((clas[j].score_1 == clas[j].score_2)?1:0);
                    eq[i].m_nul += (clas[j].score_1 == clas[j].score_2)?1:0;
                    eq[i].m_vict += (clas[j].score_1 > clas[j].score_2)?1:0;
                    eq[i].m_def += (clas[j].score_1 < clas[j].score_2)?1:0;
                } else if(clas[j].eq_2 == eq[i].id_eq) {
                    eq[i].ecart += clas[j].score_2 - clas[j].score_1;
                    eq[i].point += (clas[j].score_2 > clas[j].score_1)? 3: ((clas[j].score_1 == clas[j].score_2)?1:0);
                    eq[i].m_nul += (clas[j].score_1 == clas[j].score_2)?1:0;
                    eq[i].m_vict += (clas[j].score_2 > clas[j].score_1)?1:0;
                    eq[i].m_def += (clas[j].score_2 < clas[j].score_1)?1:0;
                }
            }
        }
    }
    vector<equipe> eq_classe = {};
    int tab_size = eq.size();
    while(eq_classe.size() < tab_size) {
        int j = 0;
        for(int i=1; i < eq.size(); i++) {
            if ((eq[j].point < eq[i].point)||(eq[j].point == eq[i].point && eq[j].ecart < eq[i].ecart)) {
                j = i;
            }
        }

        eq_classe.push_back(eq[j]);
        eq.erase(eq.begin() + j);
    }

    ConsoleTable table{ "rang", "equipe", "point", "ecart", "match perdu", "match nul", "match gagne" };
    table.setPadding(2);
    table.setStyle(0);

    for (int i=0; i < eq_classe.size(); i++) {
        //aff("", std::to_string(i+1) , "");
        //cout << eq_classe[i].libelle << "\necart: " << eq_classe[i].ecart << "\npoint: " << eq_classe[i].point << "\nmatch nul: " << eq_classe[i].m_nul << "\nperdu: " << eq_classe[i].m_def << "\ngagne: " << eq_classe[i].m_vict << endl;
        table += { to_string(i+1), eq_classe[i].libelle, to_string(eq_classe[i].point), to_string(eq_classe[i].ecart), to_string(eq_classe[i].m_def), to_string(eq_classe[i].m_nul), to_string(eq_classe[i].m_vict) };
    }
    table.sort(true);
    std::cout << table;

    int choix_cla = -1000;
    do {
        cout << "\nTaper -1 pour retourner au menu et -2 pour sortir de l'application: ";
        read_choice(choix_cla);
        if(choix_cla == -1) {
            action_one_championnat(one_chp);
        } else if (choix_cla == -2) {
            splashscreen_end();
        }
    } while(choix_cla != -1);
}

void action_one_resultat(championnat one_chp, rencontrer one_renc) {
    system("cls");
    grand_titre("Resultat " + std::to_string(one_renc.id_ren) + ": du " + one_renc.jour + "(" + one_renc.libelle_1 + " " \
                            + std::to_string(one_renc.score_1) + " vs " + std::to_string(one_renc.score_2) + " " + one_renc.libelle_2 + ")" );

    aff("", "-2. Sortir de l'application ", "", " ");
    aff("", "-1. Retour au menu des resultats ", "", " ");
    aff("", "0. Modifier ce resultat", "", " ");
    aff("", "1. Supprimer ce resultat", "", " ");
    cout << "\nEntrer votre choix: ";
    int choix_one_score = -1000;
    do {
        read_choice(choix_one_score);
        if (choix_one_score == -1) {
            action_resultat(one_chp);
        } else if (choix_one_score == -2) {
            splashscreen_end();
        } else if (choix_one_score == 0) {
            system("cls");
            grand_titre("Modifier le resultat " + std::to_string(one_renc.id_ren) + ": du " + one_renc.jour + "(" + one_renc.libelle_1 + " " \
                + std::to_string(one_renc.score_1) + " vs " + std::to_string(one_renc.score_2) + " " + one_renc.libelle_2 + ")" );

            cout << "Modifier le score de l'equipe 1 (ancienne valeur=" + std::to_string(one_renc.score_1) + "):";
            int f = 0;
            string s="-2";
            do {
                if (f > 0 && std::stoi(s) < 0) { cout << "le score doit etre positif: "; }
                f += 1;
                cin >> s;
                if (s == "*" || s =="-1") {
                    break;
                } else if (!is_int(s)) {
                    s = "-2";
                }
            } while (std::stoi(s) < -1);

            if (s == "-1") {
                cout << "Vous avez annule votre modification en entrant -1, vous retournez donc a la liste des scores.";
                sleep(3.5);
                action_resultat(one_chp);
            } else {
                one_renc.score_1 = (s == "*")?one_renc.score_1:std::stoi(s);
            }

            cout << "Modifier le score de l'equipe 2 (ancienne valeur=" + std::to_string(one_renc.score_2) + "):";
            f = 0;
            s="-2";
            do {
                if (f > 0 && std::stoi(s) < 0) { cout << "le score doit etre positif: "; }
                f += 1;
                cin >> s;
                if (s == "*" || s =="-1") {
                    break;
                } else if (!is_int(s)) {
                    s = "-2";
                }
            } while (std::stoi(s) < -1);

            if (s == "-1") {
                cout << "Vous avez annule votre modification en entrant -1, vous retournez donc a la liste des scores.";
                sleep(3.5);
                action_resultat(one_chp);
            } else {
                one_renc.score_2 = (s == "*")?one_renc.score_2:std::stoi(s);
            }

            if(upd_rencontrer(one_renc)) {
                cout << "Modification effectuee avec succes.";
            } else {
                cout << "Un probleme est survenu, reessayez plus tard.";
            }
            sleep(2);
            action_one_resultat(one_chp, one_renc);
        } else if (choix_one_score == 1) {
            system("cls");
            grand_titre("Supprimer le resultat " + std::to_string(one_renc.id_ren) + ": du " + one_renc.jour + "(" + one_renc.libelle_1 + " " \
                + std::to_string(one_renc.score_1) + " vs " + std::to_string(one_renc.score_2) + " " + one_renc.libelle_2 \
                + ")  [journee:" + std::to_string(one_renc.num_journee) + ")" );

            aff("", "Voulez-vous Supprimer vraiment ce resultat " + std::to_string(one_renc.id_ren) + ": du " + one_renc.jour + "(" + one_renc.libelle_1 + " " \
                + std::to_string(one_renc.score_1) + " vs " + std::to_string(one_renc.score_2) + " " + one_renc.libelle_2 \
                + ")  [journee:" + std::to_string(one_renc.num_journee) + ")" \
                + "?\nO:oui\nN:non", "", " ");

            string del_score = "n";
            cin >> del_score;
            if (del_score.size()==1 && (del_score == "o" || del_score == "O")){
                cout << "Suppression du score en cours...\n";
                one_renc.score_1 = -1;
                one_renc.score_2 = -1;
                if(upd_rencontrer(one_renc)) {
                    cout << "Suppression effectuee avec succes." << endl;
                } else {
                    cout << "Un probleme est survenu, reessayez plus tard." << endl;
                }
                sleep(2);
                action_resultat(one_chp);
            } else {
                cout << "\nVous avez entre autre chose que 'o' pour oui donc pas de suppression." << endl;
                sleep(5);
                action_one_resultat(one_chp, one_renc);
            }
        } else {
            cout << "Choix indisponible, veuillez ressayer: ";
        }
    } while (choix_one_score < -1 && choix_one_score > 1);
}

void action_resultat(championnat one_chp) {
    system("cls");
    grand_titre("Resultats du championnat " + std::to_string(one_chp.id_chp) + ": " + one_chp.libelle + "(saison=" + one_chp.saison + ")" );
    vector<rencontrer> renc_by_chp = sel_rencontrer_cal(one_chp.id_chp);
    vector<int> liste_id_renc_score = {};
    if (renc_by_chp.size() == 0) {
        cout << "Aucun resultat pour l'instant." << endl;
    }

    ConsoleTable table{"ID", "date du match", "equipes et scores", "journee"};
    table.setPadding(2);
    table.setStyle(3);



    for (int i_renc_by_chp=0; i_renc_by_chp < renc_by_chp.size(); i_renc_by_chp++) {
        if (renc_by_chp[i_renc_by_chp].score_1 > -1 && renc_by_chp[i_renc_by_chp].score_2 > -1) {
            //cout << "[ID:" << renc_by_chp[i_renc_by_chp].id_ren << "] le " + renc_by_chp[i_renc_by_chp].jour + "  " + renc_by_chp[i_renc_by_chp].libelle_1 + " " \
                + std::to_string(renc_by_chp[i_renc_by_chp].score_1) + " vs " + std::to_string(renc_by_chp[i_renc_by_chp].score_2) + " " + renc_by_chp[i_renc_by_chp].libelle_2 << \
                " [ journee: "  << renc_by_chp[i_renc_by_chp].num_journee << " ] " << endl;
            table += { to_string(renc_by_chp[i_renc_by_chp].id_ren), \
            renc_by_chp[i_renc_by_chp].jour, renc_by_chp[i_renc_by_chp].libelle_1 + "  (" + std::to_string(renc_by_chp[i_renc_by_chp].score_1) \
            + ") vs (" + std::to_string(renc_by_chp[i_renc_by_chp].score_2) + ")  " + renc_by_chp[i_renc_by_chp].libelle_2, \
            to_string(renc_by_chp[i_renc_by_chp].num_journee) };

            liste_id_renc_score.push_back(renc_by_chp[i_renc_by_chp].id_ren);
        }
    }

    table.sort(true);
    std::cout << table;

    if (liste_id_renc_score.size() == 0 && renc_by_chp.size() > 0) {
        cout << "Aucun resultat pour l'instant." << endl;
    }
    aff("", "", "");
    aff("", "-2. Sortir de l'application ", "", " ");
    aff("", "-1. Retour au menu du championnat ", "", " ");
    aff("", "0. Ajouter un resultat ", "", " ");
    aff("", "ID. Entrer l'ID d'un resultat pour en voir les details", "", " ");
    int choix_cal = -1000;
    vector<rencontrer> one_renc = {};
    cout << "\nEntrer votre choix: ";
    do {
        read_choice(choix_cal);
        if (choix_cal == -1) {
            action_one_championnat(one_chp);
        } else if(choix_cal == 0) {
            system("cls");
            grand_titre("Ajouter un resultat au championnat " + std::to_string(one_chp.id_chp) + ": " + one_chp.libelle + "(saison=" + one_chp.saison + ")" );
            vector<int> liste_id_renc_non_score = {};

            ConsoleTable table_m{"ID", "date du match", "equipes", "journee"};
            table_m.setPadding(2);
            table_m.setStyle(3);

            for (int i_renc_by_chp=0; i_renc_by_chp < renc_by_chp.size(); i_renc_by_chp++) {
                if (renc_by_chp[i_renc_by_chp].score_1 < 0 || renc_by_chp[i_renc_by_chp].score_2 < 0) {
                    //cout << "[ID:" << renc_by_chp[i_renc_by_chp].id_ren << "] le " + renc_by_chp[i_renc_by_chp].jour + "  " + renc_by_chp[i_renc_by_chp].libelle_1 + " " \
                        + std::to_string(renc_by_chp[i_renc_by_chp].score_1) + " vs " + std::to_string(renc_by_chp[i_renc_by_chp].score_2) + " " + renc_by_chp[i_renc_by_chp].libelle_2 << \
                        " [ journee: "  << renc_by_chp[i_renc_by_chp].num_journee << " ] " << endl;
                    table_m += { to_string(renc_by_chp[i_renc_by_chp].id_ren), \
                        renc_by_chp[i_renc_by_chp].jour, renc_by_chp[i_renc_by_chp].libelle_1 + " vs " \
                        + renc_by_chp[i_renc_by_chp].libelle_2, to_string(renc_by_chp[i_renc_by_chp].num_journee) };

                    liste_id_renc_non_score.push_back(renc_by_chp[i_renc_by_chp].id_ren);
                }
            }
            table_m.sort(true);
            std::cout << table_m;

            if (liste_id_renc_non_score.size() == 0 && renc_by_chp.size() > 0) {
                cout << "Aucun resultat pour l'instant." << endl;
            }

            std::cout << "Entrer l'ID du match dont vous voulez entrer le score \n(si vous voulez annuler et retourner au menu des resultats entrer -1): ";
            int choix_score = -1000;
            do {
                read_choice(choix_score);
                if (choix_score == -1) {
                    action_resultat(one_chp);
                } else if (choix_score == -2) {
                    splashscreen_end();
                } else if(choix_score > 0 && good_choix_score(choix_score, liste_id_renc_non_score) >= 0){
                    one_renc = sel_rencontrer_cal_by_chp(one_chp.id_chp, liste_id_renc_non_score[good_choix_score(choix_score, liste_id_renc_non_score)]);
                    cout << "\n\nVous souhaitez entrer le score du match " << one_renc[0].id_ren << ":" << endl;
                    cout << "\tScore de l'equipe 1 (" << one_renc[0].libelle_1 << "): ";
                    int f = 0;
                    do {
                        if (f > 0 && one_renc[0].score_1 < 0) { cout << "le score doit etre positif: "; }
                        f += 1;
                        read_choice(one_renc[0].score_1);
                    } while (one_renc[0].score_1 < -1);
                    if (one_renc[0].score_1 == -1) { action_resultat(one_chp); }

                    cout << "\tScore de l'equipe 2 (" << one_renc[0].libelle_2 << "): ";
                    f = 0;
                    do {
                        if (f > 0 && one_renc[0].score_2 < 0) { cout << "le score doit etre positif: "; }
                        f += 1;
                        read_choice(one_renc[0].score_2);
                    } while (one_renc[0].score_2 < -1);
                    if (one_renc[0].score_2 == -1) { action_resultat(one_chp); }

                    upd_rencontrer(one_renc[0]);
                    action_resultat(one_chp);
                } else {
                    cout << "Choix indisponible, reessayer: ";
                }
            } while(choix_score < -1 || good_choix_score(choix_score, liste_id_renc_non_score) < 0);

        } else if(choix_cal > 0) {

            if (good_choix_score(choix_cal, liste_id_renc_score) > -1) {
                action_one_resultat(one_chp, sel_rencontrer_cal_by_chp(one_chp.id_chp, liste_id_renc_score[good_choix_score(choix_cal, liste_id_renc_score)])[0]);
            } else {
                cout << "Choix indisponible, veuillez ressayer: ";
            }
        } else {
            cout << "Choix indisponible, veuillez ressayer: ";
        }
    } while (one_renc.size() < 1 || choix_cal < -1);
}

void action_one_calendrier(championnat one_chp, rencontrer one_renc) {
    system("cls");
    grand_titre("Menu concernant le match " + std::to_string(one_renc.id_ren) + " du " + one_renc.jour \
                + ":" + one_renc.libelle_1 + " vs " + one_renc.libelle_2 + "[journee:" + std::to_string(one_renc.num_journee) + "]");

    aff("", "-2. Sortir de l'application ", "", " ");
    aff("", "-1. Retour au calendrier", "", " ");
    aff("", "0. Modifier le match", "", " ");
    aff("", "1. Supprimer le match", "", " ");

    int choix_one_cal = -1000;
    cout << "\nEntrer votre choix: ";
    do {
        read_choice(choix_one_cal);
        if (choix_one_cal == -1) {
            action_calendrier(one_chp);
        } else if (choix_one_cal == -2) {
            splashscreen_end();
        } else if (choix_one_cal == 0) {
            // modification du match
            system("cls");
            std::cout << "Vous allez apporter des modifications au match " + std::to_string(one_renc.id_ren) + " du " + one_renc.jour \
                + ":" + one_renc.libelle_1 + " vs " + one_renc.libelle_2 + "[journee:" + std::to_string(one_renc.num_journee) + "]" + "?(si vous ne voulez pas retoucher un champs, taper '*')\n";
            std::string jour, eq_1="-999", eq_2="-1000", num_journee;

            std::cout << "Date du match(sous le format jj/mm/aaaa, exemple 28/01/1900)\n(valeur actuelle=" + one_renc.jour + "): ";
            int f = 1;
            do {
                if(!one_renc.good_date(jour) && f>1) {
                    std::cout << "\nLe format de votre date est incorrecte, \nla date doit etre sous la forme jj/mm/aaaa\n et doit etre valide(date >= xx/05/2021): ";
                }
                f += 1;
                std::cin >> jour;
            } while(!one_renc.good_date(jour) && jour != "*");
            one_renc.jour = (jour == "*")?one_renc.jour:jour;



            vector<equipe> eq_by_chp = sel_equipe_by_championnat(one_chp.id_chp);
            aff("", "Liste des equipes", "", " ");
            if (eq_by_chp.size() == 0) {
                cout << "Aucune equipe pour ce championnat pour l'instant\n";
            } else {
                for (int i_eq_by_chp=0; i_eq_by_chp < eq_by_chp.size(); i_eq_by_chp++) {
                    cout << "[ID:" << eq_by_chp[i_eq_by_chp].id_eq << "] " << eq_by_chp[i_eq_by_chp].libelle << endl;
                }
            }



            std::cout << "\n\nEquipe 1 du match(valeur actuelle=" + std::to_string(one_renc.eq_1) + "=" + one_renc.libelle_1 + ", entrer l'ID de la nouvel equipe 1): ";
            f = 1;
            do {
                if(!one_renc.exist_eq(one_chp.id_chp, std::stoi(eq_1)) && f>1) {
                    std::cout << "\nCet equipe est inexistante dans la BD, \nassurez-vous d'entrer un identifiant correcte: ";
                }
                f +=1;
                std::cin >> eq_1;
                if (!is_int(eq_1) && eq_1 == "*") {
                    break;
                } else if (!is_int(eq_1) && eq_1 != "*") {
                    std::cout << "\nVous devez entrer un entier ";
                    eq_1 = "-999";
                }
            } while (!one_renc.exist_eq(one_chp.id_chp, std::stoi(eq_1)));
            one_renc.eq_1 = (eq_1 == "*")?one_renc.eq_1:std::stoi(eq_1);

            std::cout << "\nEquipe 2 du match(valeur actuelle=" + std::to_string(one_renc.eq_2) + "=" + one_renc.libelle_2 + ", entrer l'ID de la nouvel equipe 2): ";
            f = 1;
            do {
                if (f == 1) {
                    eq_2 = "-1000";
                }

                if(!one_renc.exist_eq(one_chp.id_chp, std::stoi(eq_2)) && f>1) {
                    std::cout << "\nCet equipe est inexistante dans la BD, \nassurez-vous d'entrer un identifiant correcte: ";
                }

                if (one_renc.eq_1 == std::stoi(eq_2)) {
                    std::cout << "\nUne equipe ne peut jouer contre elle-meme, \nassurez-vous d'entrer un identifiant correcte: ";
                }
                f +=1;
                std::cin >> eq_2;
                if (!is_int(eq_2) && eq_2 == "*") {
                    break;
                } else if (!is_int(eq_2) && eq_2 != "*") {
                    std::cout << "\nVous devez entrer un entier ";
                    eq_2 = "-1000";
                }
            } while (!one_renc.exist_eq(one_chp.id_chp, std::stoi(eq_2))||one_renc.eq_1 == std::stoi(eq_2));
            one_renc.eq_2 = (eq_2 == "*")?one_renc.eq_2:std::stoi(eq_2);

            std::cout << "\nNumero de la journee du match(valeur actuelle=" + std::to_string(one_renc.num_journee) + "): ";
            f = 1;
            do {
                if (f>1 && std::stoi(num_journee) < 1) {
                    std::cout << "\nUne journee ne peut etre inferieure a 0, reessayer: ";
                }
                f += 1;
                std::cin >> num_journee;
                if (!is_int(num_journee) && num_journee == "*") {
                    break;
                } else if (!is_int(num_journee) && num_journee != "*") {
                    std::cout << "\nVous devez entrer un entier ";
                    num_journee = "-999";
                }
            } while(std::stoi(num_journee) < 1);
            one_renc.num_journee = (num_journee == "*")?one_renc.num_journee:std::stoi(num_journee);

            if (upd_rencontrer(one_renc)) {
                cout << "Modification effectuee avec succes.";
            } else {
                cout << "Un problème est survenu veuillez reessayer plus tard.";
            }
            sleep(2);
            action_one_calendrier(one_chp, one_renc);
        } else if (choix_one_cal == 1) {
            // suppression d'un match
            system("cls");
            aff("", "Voulez-vous Supprimer vraiment le match " + std::to_string(one_renc.id_ren) + " du " + one_renc.jour \
                + ":" + one_renc.libelle_1 + " vs " + one_renc.libelle_2 + "[journee:" + std::to_string(one_renc.num_journee) + "]" \
                + "?\nO:oui\nN:non", "", " ");
            string del_renc = "n";
            cin >> del_renc;
            if (del_renc.size()==1 && (del_renc == "o" || del_renc == "O")) {
                cout << "Suppression du match en cours...\n";
                if(del_rencontrer(one_renc.id_ren)) {
                    cout << "Match supprime avec succes.\n";
                    sleep(2);
                    action_calendrier(one_chp);
                } else {
                    cout << "Une erreur est survenue veuillez ressayer plus tard.\n";
                    sleep(2);
                    action_one_calendrier(one_chp, one_renc);
                }
            } else {
                cout << "\nVous avez entre autre chose que 'o' pour oui donc pas de suppression." << endl;
                sleep(5);
                action_one_calendrier(one_chp, one_renc);
            }

        } else {
            cout << "Choix indisponible, veuillez ressayer: ";
        }
    } while (choix_one_cal < -1 && choix_one_cal > 1);
}

void action_calendrier(championnat one_chp) {
    system("cls");
    grand_titre("Calendrier du championnat " + std::to_string(one_chp.id_chp) + ": " + one_chp.libelle + "(saison=" + one_chp.saison + ")" );
    vector<rencontrer> renc_by_chp = sel_rencontrer_cal(one_chp.id_chp);
    if (renc_by_chp.size() == 0) {
        cout << "Aucun match n'a ete programme pour l'instant." << endl;
    }

    ConsoleTable table{"ID", "date du match", "equipes", "journee"};
    table.setPadding(2);
    table.setStyle(3);

    for (int i_renc_by_chp=0; i_renc_by_chp < renc_by_chp.size(); i_renc_by_chp++) {
        //cout << "[ID:" << renc_by_chp[i_renc_by_chp].id_ren << "] le " << renc_by_chp[i_renc_by_chp].jour <<  \
            " " << renc_by_chp[i_renc_by_chp].libelle_1 << " vs " << renc_by_chp[i_renc_by_chp].libelle_2 << \
            " [ journee: "  << renc_by_chp[i_renc_by_chp].num_journee << " ] " << endl;

        table += {std::to_string(renc_by_chp[i_renc_by_chp].id_ren), renc_by_chp[i_renc_by_chp].jour, renc_by_chp[i_renc_by_chp].libelle_1 + " vs " + renc_by_chp[i_renc_by_chp].libelle_2, to_string(renc_by_chp[i_renc_by_chp].num_journee) };
    }

    table.sort(true);
    std::cout << table;

    aff("", "", "");
    aff("", "-2. Sortir de l'application ", "", " ");
    aff("", "-1. Retour au menu du championnat ", "", " ");
    aff("", "0. Ajouter un match a ce championnat ", "", " ");
    aff("", "ID. Entrer l'ID d'un match pour en voir les details", "", " ");
    int choix_cal = -1000;
    vector<rencontrer> one_renc = {};
    cout << "\nEntrer votre choix: ";
    do {
        read_choice(choix_cal);
        if (choix_cal == -1) {
            action_one_championnat(one_chp);
        } else if (choix_cal == -2) {
            splashscreen_end();
        } else if(choix_cal == 0) {
            system("cls");
            grand_titre("Ajouter un match au championnat " + std::to_string(one_chp.id_chp) + ": " + one_chp.libelle + "(saison=" + one_chp.saison + ")" );
            vector<equipe> eq_by_chp = sel_equipe_by_championnat(one_chp.id_chp);
            aff("", "Liste des equipes", "", " ");
            if (eq_by_chp.size() == 0) {
                cout << "Aucune equipe pour ce championnat pour l'instant\n";
            } else {
                ConsoleTable table_eq{ "ID", "equipes" };
                table_eq.setPadding(2);
                table_eq.setStyle(3);
                for (int i_eq_by_chp=0; i_eq_by_chp < eq_by_chp.size(); i_eq_by_chp++) {
                    //cout << "[ID:" << eq_by_chp[i_eq_by_chp].id_eq << "] " << eq_by_chp[i_eq_by_chp].libelle << endl;
                    table_eq += { to_string(eq_by_chp[i_eq_by_chp].id_eq), eq_by_chp[i_eq_by_chp].libelle };
                }
                table_eq.sort(true);
                std::cout << table_eq;

                rencontrer r(one_chp.id_chp);
                if(ins_rencontrer(r)) {
                    cout << "Match ajoute avec succes.\n";
                } else {
                    cout << "Une erreur est survenue veuillez ressayer plus tard.\n";
                }
            }
            sleep(2);
            action_calendrier(one_chp);
        } else if(choix_cal > 0) {
            one_renc = sel_rencontrer_cal_by_chp(one_chp.id_chp, choix_cal);
            if (one_renc.size() == 1) {
                action_one_calendrier(one_chp, one_renc[0]);
            } else {
                cout << "Choix indisponible, veuillez ressayer: ";
            }
        } else {
            cout << "Choix indisponible, veuillez ressayer: ";
        }
    } while (one_renc.size() < 1 || choix_cal < -1);
}

void action_one_equipe(championnat one_chp, equipe one_eq) {
    system("cls");
    grand_titre("Menu de l'equipe " + std::to_string(one_eq.id_eq) + ": " + one_eq.libelle);

    aff("", "-2. Sortir de l'application ", "", " ");
    aff("", "-1. Retour au menu des equipes", "", " ");
    aff("", "0. Modifier le nom de l'equipe", "", " ");
    aff("", "1. Supprimer l'equipe", "", " ");
    int choix_one_eq = -1000;
    cout << "\nEntrer votre choix: ";
    do {
        read_choice(choix_one_eq);
        if (choix_one_eq == -1) {
            action_equipe(one_chp);
        } else if (choix_one_eq == -2) {
            splashscreen_end();
        } else if (choix_one_eq == 0) {
            // modification de l'equipe
            system("cls");
            std::cout << "Vous allez apporter des modifications a l'equipe " + one_eq.libelle + "?(si vous ne voulez pas retoucher un champs, taper '*')\n";
            std::string libelle;
            std::cout << "libelle(valeur actuelle=" + one_eq.libelle + "): ";
            std::cin.ignore();
            getline(std::cin, libelle);
            one_eq.libelle = (libelle == "*")?one_eq.libelle:libelle;
            upd_equipe(one_eq);
            cout << "Modification effectuee avec succes.";
            sleep(2);
            action_one_equipe(one_chp, one_eq);
        } else if (choix_one_eq == 1) {
            // suppression d'equipe
            system("cls");
            aff("", "Voulez-vous Supprimer vraiment l'equipe " + one_eq.libelle + "?\nO:oui\nN:non", "", " ");
            string del_eq = "n";
            cin >> del_eq;
            if (del_eq.size()==1 && (del_eq == "o" || del_eq == "O")) {
                cout << "Suppression de l'equipe en cours...\n";
                if(del_equipe(one_eq.id_eq)) {
                    cout << "Equipe supprime avec succes.\n";
                    sleep(2);
                    action_equipe(one_chp);
                } else {
                    cout << "Une erreur est survenue veuillez ressayer plus tard.\n";
                    sleep(2);
                    action_one_equipe(one_chp, one_eq);
                }
            } else {
                cout << "\nVous avez entre autre chose que 'o' pour oui donc pas de suppression." << endl;
                sleep(5);
                action_one_equipe(one_chp, one_eq);
            }

        } else {
            cout << "Choix indisponible, veuillez ressayer: ";
        }
    } while (choix_one_eq<-1 && choix_one_eq>1);
}

void action_equipe(championnat one_chp) {
    system("cls");
    grand_titre("Menu des equipes du championnat " + std::to_string(one_chp.id_chp) + ": " + one_chp.libelle + "(saison=" + one_chp.saison + ")" );
    vector<equipe> eq_by_chp = sel_equipe_by_championnat(one_chp.id_chp);
    aff("", "Liste des equipes", "", " ");
    if (eq_by_chp.size() == 0) {
        cout << "Aucune equipe pour ce championnat pour l'instant\n";
    }

    ConsoleTable table{"ID", "Nom de l'equipe"};
    table.setPadding(2);
    table.setStyle(3);

    for (int i_eq_by_chp=0; i_eq_by_chp < eq_by_chp.size(); i_eq_by_chp++) {
        //cout << "[ID:" << eq_by_chp[i_eq_by_chp].id_eq << "] " << eq_by_chp[i_eq_by_chp].libelle << endl;
        table += { std::to_string(eq_by_chp[i_eq_by_chp].id_eq), eq_by_chp[i_eq_by_chp].libelle };
    }

    table.sort(true);
    std::cout << table;

    aff("", "", "");
    aff("", "-2. Sortir de l'application ", "", " ");
    aff("", "-1. Retour au menu du championnat ", "", " ");
    aff("", "0. Ajouter une equipe a ce championnat ", "", " ");
    aff("", "ID. Entrer l'ID d'une equipe pour en voir les details", "", " ");
    int choix_eq =-1000;
    vector<equipe> one_eq = {};
    cout << "\nEntrer votre choix: ";
    do {
        read_choice(choix_eq);
        if (choix_eq == -1) {
            action_one_championnat(one_chp);
        } else if (choix_eq == -2) {
            splashscreen_end();
        } else if (choix_eq == 0) {
            system("cls");
            grand_titre("Ajouter une equipe au championnat " + std::to_string(one_chp.id_chp) + ": " + one_chp.libelle + "(saison=" + one_chp.saison + ")" );
            equipe eq_one_chp(one_chp.id_chp);
            if(!ins_equipe(eq_one_chp)) {
                cout << "Une erreur est survenue lors de l'insertion, reessayez plus tard.";
            } else {
                cout << "Insertion effectuee avec succes.\n";
            }
            sleep(2);
            action_equipe(one_chp);
        } else if (choix_eq > 0) {
            one_eq = sel_equipe_by_championnat_and_eq(one_chp.id_chp ,choix_eq);
            if (one_eq.size() == 1) {
                action_one_equipe(one_chp, one_eq[0]);
            } else {
                cout << "Choix indisponible, veuillez ressayer: ";
            }
        } else {
            cout << "Choix indisponbles reessayer: ";
        }
    } while (one_eq.size()< 1 || choix_eq < -1);
}

void action_one_championnat(championnat one_chp) {
    system("cls");
    grand_titre("Menu du championnat " + std::to_string(one_chp.id_chp) + ": " + one_chp.libelle + "(saison=" + one_chp.saison + ")" );

    aff("", "-2. Sortir de l'application ", "", " ");
    aff("", "-1. Retour a la liste des championnats", "", " ");
    aff("", "0. Equipes", "", " ");
    aff("", "1. Calendrier", "", " ");
    aff("", "2. Classement", "", " ");
    aff("", "3. Resultats", "", " ");
    aff("", "", "");
    aff("", "4. Supprimer ce championnat", "", " ");
    aff("", "5. Modifier ce championnat", "", " ");

    int choix_one_chp = -1000;
    cout << "\nEntrer votre choix: ";
    do {
        read_choice(choix_one_chp);
        if(choix_one_chp == -1) {
            // retour à la liste des championnats
            action_championnat();
        } else if (choix_one_chp == -2) {
            splashscreen_end();
        } else if (choix_one_chp == 0) {
            action_equipe(one_chp);
        } else if (choix_one_chp == 1) {
            action_calendrier(one_chp);
        } else if (choix_one_chp == 2) {
            action_classement(one_chp);
        } else if (choix_one_chp == 3) {
            action_resultat(one_chp);
        } else if (choix_one_chp == 4) {
            // suppression du championnat
            system("cls");
            aff("", "Voulez-vous Supprimer le championnat " + std::to_string(one_chp.id_chp) + ": " + one_chp.libelle + "(saison=" + one_chp.saison + ") \nO:oui\nN:non", "", " ");
            string del_chp = "n";
            cin >> del_chp;
            if (del_chp.size()==1 && (del_chp == "o" || del_chp == "O")){
                cout << "Suppression de l'equipe en cours...\n";
                if(del_championnat(one_chp.id_chp)) {
                    cout << "Championnat supprime avec succes.\n";
                } else {
                    cout << "Une erreur est survenue veuillez ressayer plus tard.\n";
                }
                sleep(2);
            } else {
                cout << "\nVous avez entre autre chose que 'o' pour oui donc pas de suppression." << endl;
                sleep(5);
            }
            system("cls");
            action_championnat();
        } else if (choix_one_chp == 5) {
            // modification du championnat
            system("cls");
            std::cout << "Vous allez apporter des modifications a le championnat " + std::to_string(one_chp.id_chp) + ": " + one_chp.libelle + "(saison=" + one_chp.saison + ")\n(si vous ne voulez pas retoucher un champs, taper '*')\n";
            std::string libelle, pays, division, saison;
            std::cout << "libelle(valeur actuelle=)" + one_chp.libelle + ": ";
            std::cin.ignore();
            getline(std::cin, libelle);
            std::cout << "\npays(valeur actuelle=" + one_chp.pays + "): ";
            getline(std::cin, pays);
            std::cout << "\ndivision(valeur actuelle=" + one_chp.division + "): ";
            getline(std::cin, division);
            std::cout << "\nSaison(valeur actuelle=" + one_chp.saison + "): ";
            getline(std::cin, saison);
            one_chp.libelle = (libelle == "*")?one_chp.libelle:libelle;
            one_chp.pays = (pays == "*")?one_chp.pays:pays;
            one_chp.division = (division == "*")?one_chp.division:division;
            one_chp.saison = (saison == "*")?one_chp.saison:saison;
            if(upd_championnat(one_chp)) {
                cout << "Modification effectuee avec succes.";
            } else {
                cout << "Une erreur est survenue veuillez ressayer plus tard.\n";
            }
            sleep(2);
            action_one_championnat(one_chp);
        } else {
            cout << "Choix indisponible, veuillez ressayer: ";
        }
    } while (choix_one_chp > 5 || choix_one_chp < -2);
}

void action_championnat() {
    system("cls");
    vector<championnat> one_chp = {};
    // voir tous les championnats
    vector<championnat> list_chp = sel_championnat();
    grand_titre("MENU CHAMPIONNAT");
    if (list_chp.size() == 0) {
        cout << "Aucun championnat n'a ete enregistre." << endl;
    }

    ConsoleTable table{"ID", "LIBELLE", "PAYS", "DIVISION", "SAISON"};

    table.setPadding(2);
    table.setStyle(3);




    for (int i=0; i < list_chp.size(); i++) {
        //cout << "[ID:" << list_chp[i].id_chp << "]  LIBELLE: " << list_chp[i].libelle << "\tPAYS: " << list_chp[i].pays << "\tDIVISION: " << list_chp[i].division << "\tSAISON: " << list_chp[i].saison <<endl;
        table += { std::to_string(list_chp[i].id_chp), list_chp[i].libelle, list_chp[i].pays, list_chp[i].division, list_chp[i].saison };
    }
    table.sort(true);
    std::cout << table;

    cout << "\n";
    aff("", "", "");
    aff("", "-2. Sortir de l'application", "", " ");
    aff("", "0. Ajouter un championnat", "", " ");
    aff("", "ID. Entrer l'ID d'un championnat pour en voir les details", "", " ");
    std::cout << "\n\nEntrer votre choix: ";
    int choix_chp = -1000;
    do {
        read_choice(choix_chp);
        if (choix_chp == -2) {
            splashscreen_end();
        } else if (choix_chp == -1) {
            cout << "Choix indisponible, veuillez ressayer: ";
        } else if (choix_chp == 0) {
            // ajouter un championnat
            system("cls");
            grand_titre("Insertion d'un championnat");
            championnat add_chp;
            if(ins_championnat(add_chp)) {
                cout << "Insertion du championnat effectuee avec succes";
            } else {
                cout << "Une erreur est survenue, veuillez reprendre le processus";
            }
            action_championnat();
        } else if (choix_chp > 0) {
            one_chp = sel_championnat(choix_chp);
            if(one_chp.size() == 1) {
                action_one_championnat(one_chp[0]);
            } else {
                cout << "Choix indisponible, veuillez ressayer: ";
            }
        } else {
            cout << "Choix indisponible, veuillez ressayer: ";
        }
    } while (one_chp.size()< 1 || choix_chp < -2 || choix_chp == -1);
}


int main() {

    // pour utiliser la taille agrandie de la fenetre
    //HWND hwnd = GetForegroundWindow();
    //ShowWindow(hwnd, SW_MAXIMIZE);

    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);
    MoveWindow(console, 100, 50, 1170, 900, TRUE);

    //splashscreen();

    create_database();
    action_championnat();


    /*
    ConsoleTable table{""};
    table.setPadding(2);
    table.setStyle(0);
    table += {};
    table.sort(true);
    std::cout << table;
    */


    getch();
    return 0;
}


