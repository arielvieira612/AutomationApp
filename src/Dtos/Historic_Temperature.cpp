#include "Historic_Temperature.hpp"
#include <sstream>
#include <stdio.h>
#include "Database.hpp"

using namespace Dto;

DbStructures::st_ResultDatabase Historic_Temperature::Insert_Temperature(Model::Historic_Temperature& Data){
   DbStructures::st_ResultDatabase Result;
   std::stringstream Command;
   Database db;
   

   /* Open database */
   Result = db.OpenDatabase();
   if( Result.Error ){
      return Result;
   }

   /* Create SQL statement */
   Command << "INSERT INTO Historic_Temperature (Temperature,Humidity) ";
   Command << "VALUES (" << Data.Temperature << "," << Data.Humidity << ")";

   Result = db.ExecCommand(Command.str().c_str());

   db.CloseDatabase();
   
   return Result;
}