#include "db_equipe.h"

std::vector<equipe> equipe_list = {};
static int callback_ins(void *NotUsed, int argc, char **argv, char **azColName) {
    return 0;
}

static int callback_del(void *data, int argc, char **argv, char **azColName) {
    return 0;
}

static int callback_upd(void *data, int argc, char **argv, char **azColName) {
    return 0;
}

static int callback_sel(void *data, int argc, char **argv, char **azColName){
    equipe e(std::stoi(argv[0]), argv[1], std::stoi(argv[2]));
    equipe_list.push_back(e);
    return 0;
}

bool ins_equipe(equipe eq) {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    std::string sql;

    rc = sqlite3_open(DATABASE_NAME, &db);
    if( rc ) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    }

    sql = "INSERT INTO equipe (libelle, id_chp) "  \
        "VALUES ('" + eq.libelle + "', '" + std::to_string(eq.id_chp) + "');";

    rc = sqlite3_exec(db, sql.c_str(), callback_ins, 0, &zErrMsg);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        return true;
    }
    sqlite3_close(db);
    return false;
}

bool del_equipe(int id) {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    const char* data = "Callback function called";
    std::string sql;

    rc = sqlite3_open(DATABASE_NAME, &db);
    if( rc ) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return false;
    }

    sql = "DELETE from equipe where id_eq=" + std::to_string(id) + "; ";

    rc = sqlite3_exec(db, sql.c_str(), callback_del, (void*)data, &zErrMsg);
    if( rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
      return true;
    }
    sqlite3_close(db);
    return false;
}

bool upd_equipe(equipe eq) {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    std::string sql;

    rc = sqlite3_open(DATABASE_NAME, &db);
    if( rc ) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    }

    sql = "UPDATE equipe "  \
        "SET libelle='" + eq.libelle + "' WHERE id_eq=" + std::to_string(eq.id_eq) + ";";

    rc = sqlite3_exec(db, sql.c_str(), callback_upd, 0, &zErrMsg);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        return true;
    }
    sqlite3_close(db);
    return false;
}


std::vector<equipe> sel_equipe(int id) {
    equipe_list = {};
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    std::string sql;
    //const char* data = "Callback function called";

    rc = sqlite3_open(DATABASE_NAME, &db);
    if( rc ) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    }

    sql = "SELECT * from equipe";
    if (id > 0) {
        sql += " WHERE id_eq=" + std::to_string(id) + ";";
    }

    rc = sqlite3_exec(db, sql.c_str(), callback_sel, 0, &zErrMsg);
    if( rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    sqlite3_close(db);
    return equipe_list;
}

std::vector<equipe> sel_equipe_by_championnat(int id) {
    equipe_list = {};
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    std::string sql;
    //const char* data = "Callback function called";

    rc = sqlite3_open(DATABASE_NAME, &db);
    if( rc ) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    }

    sql = "SELECT * from equipe";
    if (id > 0) {
        sql += " WHERE id_chp=" + std::to_string(id) + ";";
    }

    rc = sqlite3_exec(db, sql.c_str(), callback_sel, 0, &zErrMsg);
    if( rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    sqlite3_close(db);
    return equipe_list;
}

std::vector<equipe> sel_equipe_by_championnat_and_eq(int id_chp, int id_ep) {
    equipe_list = {};
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    std::string sql;
    //const char* data = "Callback function called";

    rc = sqlite3_open(DATABASE_NAME, &db);
    if( rc ) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    }

    sql = "SELECT * from equipe WHERE id_chp=" + std::to_string(id_chp) + " AND id_eq=" + std::to_string(id_ep) + ";";

    rc = sqlite3_exec(db, sql.c_str(), callback_sel, 0, &zErrMsg);
    if( rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    sqlite3_close(db);
    return equipe_list;
}
