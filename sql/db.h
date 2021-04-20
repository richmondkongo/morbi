#ifndef DB_H_INCLUDED
#define DB_H_INCLUDED
#include <iostream>
#include <string>
#include "../lib/sqlite/sqlite3.h"
#include "../fonctions.h"

// nom de la base donnée
#define DATABASE_NAME "./morbi_database.db"

//fonction créant la base de donnée avec ses tables
void create_database();

#endif // DB_H_INCLUDED
