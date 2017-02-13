#include "Database.hpp"


using namespace DbStructures;

int Database::callback(void *NotUsed, int argc, char **argv, char **azColName){
   int i;
   for(i=0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

st_ResultDatabase Database::OpenDatabase(void){
    
    st_ResultDatabase result;
    int rc =sqlite3_open(DbName, &this->db);
    if(rc){
        result.Error = true;
        result.Detail = sqlite3_errmsg(this->db);
    }else{
        result.Error = false;
    }
    return result;
}

DbStructures::st_ResultDatabase Database::ExecCommand(const char* Command){
   int rc;
   char *zErrMsg = 0;
   st_ResultDatabase result;
   rc = sqlite3_exec(this->db, Command, callback, 0, &zErrMsg);
   if( rc != SQLITE_OK ){
      result.Error = true;
      result.Detail =  zErrMsg;
      sqlite3_free(zErrMsg);
      return result;
   }else{
      result.Error = false;
   }
   return result;
}

void Database::CloseDatabase(){
     sqlite3_close(this->db);
}