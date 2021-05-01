#include "db_championnat.h"

std::vector<championnat> championnat_list = {};

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
    championnat c(std::stoi(argv[0]), argv[1], argv[2], argv[3], argv[4]);
    championnat_list.push_back(c);
    return 0;
}

bool ins_championnat(championnat ch) {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    std::string sql;

    rc = sqlite3_open(DATABASE_NAME, &db);
    if( rc ) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    }
    std::cout << "--------------------" << ch.libelle << "--------------------" << std::endl;
    sleep(3);
    sql = "INSERT INTO championnat (libelle, pays, division, saison) "  \
        "VALUES (\"" + ch.libelle + "\", \"" + ch.pays + "\", \"" + ch.division + "\", \"" + ch.saison + "\");";

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

bool del_championnat(int id) {
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

    sql = "DELETE from championnat where id_chp=" + std::to_string(id) + "; ";

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

bool upd_championnat(championnat ch) {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    std::string sql;

    rc = sqlite3_open(DATABASE_NAME, &db);
    if( rc ) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    }

    sql = "UPDATE championnat "  \
        "SET libelle=\"" + ch.libelle + "\", pays=\"" + ch.pays + "\", division=\"" + ch.division + "\", saison=\"" + ch.saison + "\" WHERE id_chp=" + std::to_string(ch.id_chp) + ";";

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


std::vector<championnat> sel_championnat(int id) {
    championnat_list = {};
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    std::string sql;
    //const char* data = "Callback function called";

    rc = sqlite3_open(DATABASE_NAME, &db);
    if( rc ) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    }

    sql = "SELECT * from championnat";
    if (id > 0) {
        sql += " WHERE id_chp=" + std::to_string(id) + ";";
    }

    rc = sqlite3_exec(db, sql.c_str(), callback_sel, 0, &zErrMsg);
    if( rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    sqlite3_close(db);
    return championnat_list;
}
