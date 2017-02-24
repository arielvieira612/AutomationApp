#include "Status_Sensors.hpp"
#include <sstream>
#include <stdio.h>
#include "Database.hpp"
#include <ctime>
#include "../../inc/sqlite3.h"
using namespace Dto;
using namespace DbStructures;


DbStructures::st_ResultStaus_Sensor Status_Sensors::Read_Sensors(){
   st_ResultStaus_Sensor Result;
   std::stringstream Command;
   Database db;
   sqlite3_stmt* stmt;
   int s;

   /* Open database */
   Result = db.OpenDatabase();
   if( Result.Error ){
      return Result;
   }
   
    /* Create SQL statement */
    Command << "SELECT * FROM Status_Sensors LIMIT 1;";
    
    sqlite3_prepare(db.GetDataBase(), Command.str().c_str(), strlen(Command.str().c_str())+1, &stmt, NULL);
    do{
        s = sqlite3_step (stmt);
        if(s == SQLITE_ROW){
            Result.Status.StatusID = sqlite3_column_bytes(stmt, 0);
            Result.Status.Rain = sqlite3_column_bytes(stmt, 1);
            Result.Status.Photo = sqlite3_column_bytes(stmt, 2);
        }
    }while(s == SQLITE_ROW);

    db.CloseDatabase();
   
   return Result;
}

DbStructures::st_ResultDatabase Status_Sensors::Update_Sensors(Model::Status_Sensors& Data){
   DbStructures::st_ResultDatabase Result;
   std::stringstream Command;
   Database db;

   /* Open database */
   Result = db.OpenDatabase();
   if( Result.Error ){
      return Result;
   }
   
    /* Create SQL statement */
    Command << "UPDATE Status Sensors ";
    Command << "SET Rain=" << Data.Rain << ", Photo" << Data.Photo << " WHERE=" << Data.StatusID;
    Result = db.ExecCommand(Command.str().c_str());
    db.CloseDatabase();
   
   return Result;
}