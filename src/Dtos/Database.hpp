#ifndef __DATABASE__
#define __DATABASE__
#include <string.h>
#include <stdio.h>
#include "Structures_Types.hpp"
#include "../../inc/sqlite3.h"

class Database{
    private:
        sqlite3 *db;
        const char *DbName = "test.db";
        static int callback(void *NotUsed, int argc, char **argv, char **azColName);
    public:
         DbStructures::st_ResultDatabase OpenDatabase();
         DbStructures::st_ResultDatabase ExecCommand(const char* Command);
         void CloseDatabase();
};

#endif