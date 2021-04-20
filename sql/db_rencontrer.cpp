#include "db_rencontrer.h"

std::vector<rencontrer> rencontrer_list;
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
    rencontrer r(std::stoi(argv[0]), argv[1], std::stoi(argv[2]), std::stoi(argv[3]), std::stoi(argv[4]), std::stoi(argv[5]), std::stoi(argv[6]));
    rencontrer_list.push_back(r);
    return 0;
}

static int callback_cal(void *data, int argc, char **argv, char **azColName){
    rencontrer r(std::stoi(argv[0]), argv[1], std::stoi(argv[2]), std::stoi(argv[3]), std::stoi(argv[4]), std::stoi(argv[5]), std::stoi(argv[6]), argv[7], argv[8]);
    rencontrer_list.push_back(r);
    return 0;
}

static int callback_aff(void *data, int argc, char **argv, char **azColName){
   int i;
   fprintf(stderr, "%s: ", (const char*)data);

   for(i = 0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }

   printf("\n---------------------------------------------------------------------------------------------------\n");
   return 0;
}

bool ins_rencontrer(rencontrer renc) {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    std::string sql;

    rc = sqlite3_open(DATABASE_NAME, &db);
    if( rc ) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    }

    sql = "INSERT INTO rencontrer (eq_1, eq_2, jour, score_1, score_2, num_journee) "  \
        "VALUES ('" + std::to_string(renc.eq_1) + "', '" + std::to_string(renc.eq_2) + "', '" + renc.jour + "', '" + \
        std::to_string(renc.score_1) + "', '" + std::to_string(renc.score_2) + "', '" + std::to_string(renc.num_journee) + "');";

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

bool del_rencontrer(int id) {
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

    sql = "DELETE from rencontrer WHERE id_ren=" + std::to_string(id) + ";";

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

bool upd_rencontrer(rencontrer renc) {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    std::string sql;

    rc = sqlite3_open(DATABASE_NAME, &db);
    if( rc ) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    }

    sql = "UPDATE rencontrer "  \
        "SET eq_1='" + std::to_string(renc.eq_1) + "', eq_2='" + std::to_string(renc.eq_2) + "', jour='" + renc.jour + \
        "', score_1='" + std::to_string(renc.score_1) + "', score_2='" + std::to_string(renc.score_2) + "', num_journee='" + std::to_string(renc.num_journee) + \
        "' WHERE id_ren=" + std::to_string(renc.id_ren) + ";";

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

std::vector<rencontrer> sel_rencontrer(int id) {
    rencontrer_list = {};
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    std::string sql;
    //const char* data = "Callback function called";

    rc = sqlite3_open(DATABASE_NAME, &db);
    if( rc ) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    }

    sql = "SELECT * from rencontrer";
    if (id > 0) {
        sql += " WHERE id_ren=" + std::to_string(id) + ";";
    }

    rc = sqlite3_exec(db, sql.c_str(), callback_sel, 0, &zErrMsg);
    if( rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    sqlite3_close(db);
    return rencontrer_list;
}

std::vector<rencontrer> sel_rencontrer_cal(int id) {
    rencontrer_list = {};
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    std::string sql;
    //const char* data = "Callback function called";

    rc = sqlite3_open(DATABASE_NAME, &db);
    if( rc ) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    }

    sql = "SELECT r.id_ren, r.jour, r.eq_1, r.eq_2, r.score_1, r.score_2, r.num_journee, e.libelle as libelle_1, (SELECT libelle FROM equipe WHERE id_eq=r.eq_2) as libelle_2" \
        " FROM rencontrer r, championnat c, equipe e" \
        " WHERE c.id_chp=" + std::to_string(id) + " AND e.id_eq=r.eq_1 AND e.id_chp=c.id_chp ORDER BY r.jour;";

    rc = sqlite3_exec(db, sql.c_str(), callback_cal, 0, &zErrMsg);
    if( rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    sqlite3_close(db);
    return rencontrer_list;
}

std::vector<rencontrer> sel_rencontrer_cal_by_chp(int id_chp, int id_ren) {
    rencontrer_list = {};
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    std::string sql;
    //const char* data = "Callback function called";

    rc = sqlite3_open(DATABASE_NAME, &db);
    if( rc ) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    }

    sql = "SELECT r.id_ren, r.jour, r.eq_1, r.eq_2, r.score_1, r.score_2, r.num_journee, e.libelle as libelle_1, (SELECT libelle FROM equipe WHERE id_eq=r.eq_2) as libelle_2" \
        " FROM rencontrer r, championnat c, equipe e" \
        " WHERE c.id_chp=" + std::to_string(id_chp) + " AND r.id_ren=" + std::to_string(id_ren) + " AND e.id_eq=r.eq_1 AND e.id_chp=c.id_chp ORDER BY r.jour;";

    rc = sqlite3_exec(db, sql.c_str(), callback_cal, 0, &zErrMsg);
    if( rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    sqlite3_close(db);
    return rencontrer_list;
}
