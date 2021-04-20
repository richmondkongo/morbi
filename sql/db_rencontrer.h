#ifndef DB_RENCONTRER_H_INCLUDED
#define DB_RENCONTRER_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>

#include "../fonctions.h"
#include "../lib/sqlite/sqlite3.h"
#include "db.h"

#include "../class/rencontrer.h"


//fonction ins�rant une rencontre dans la base de donn�es
bool ins_rencontrer(rencontrer);

//fonction supprimant une rencontre gr�ce � l'id dans la bd
bool del_rencontrer(int);

//fonction modifiant une rencontrer dans la bd
bool upd_rencontrer(rencontrer);

//fonction de selection d'une rencontre dans la bd suivant son id pass� en param�tre si on ne met rien on renvoie toutes les rencontres
std::vector<rencontrer> sel_rencontrer(int id=-1);

std::vector<rencontrer> sel_rencontrer_eq(int id=-1);

// liste des rencontres par championnat
std::vector<rencontrer> sel_rencontrer_cal(int id);

// selectionne des rencontres par championnats et par id de la rencontre � travers une jointure
std::vector<rencontrer> sel_rencontrer_cal_by_chp(int id_chp, int id_ren);

#endif // DB_RENCONTRER_H_INCLUDED
