#ifndef DB_CHAMPIONNAT_H_INCLUDED
#define DB_CHAMPIONNAT_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>

#include "../fonctions.h"
#include "../lib/sqlite/sqlite3.h"
#include "db.h"

#include "../class/championnat.h"


//fonction insérant un championnat dans la base de données
bool ins_championnat(championnat);

//fonction supprimant un championnat grâce à l'id dans la bd
bool del_championnat(int);

//fonction modifiant un championnat dans la bd
bool upd_championnat(championnat);

//fonction de selection d'un championnat dans la bd suivant son id passé en paramètre si on ne met rien on renvoie tout les championnat
std::vector<championnat> sel_championnat(int id=-1);

#endif // DB_CHAMPIONNAT_H_INCLUDED
