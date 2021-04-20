#ifndef DB_EQUIPE_H_INCLUDED
#define DB_EQUIPE_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>

#include "../fonctions.h"
#include "../lib/sqlite/sqlite3.h"
#include "db.h"

#include "../class/equipe.h"


//fonction ins�rant une equipe dans la base de donn�es
bool ins_equipe(equipe);

//fonction supprimant une equipe gr�ce � l'id dans la bd
bool del_equipe(int);

//fonction modifiant une equipe dans la bd
bool upd_equipe(equipe);

//fonction de selection d'une equipe dans la bd suivant son id pass� en param�tre si on ne met rien on renvoie tout les equipe
std::vector<equipe> sel_equipe(int id=-1);

// fonction retournant la liste des �quipe qui participe � un championnat dont l'id est pass� en param�tre
std::vector<equipe> sel_equipe_by_championnat(int id);

// s�lection d'�quipe par son id et l'id de son championnat
std::vector<equipe> sel_equipe_by_championnat_and_eq(int id_chp, int id_ep);

#endif // DB_EQUIPE_H_INCLUDED
