#include "Historic_Temperature.hpp"
#include <sstream>
#include <stdio.h>
#include "Database.hpp"
#include <ctime>

using namespace Dto;



DbStructures::st_ResultDatabase Historic_Temperature::Insert_Temperature(Model::Historic_Temperature& Data){
   DbStructures::st_ResultDatabase Result;
   std::stringstream Command;
   Database db;
   char dateFormat[20];
   time_t t = time(0);                  // get time now
   struct tm * now = localtime(&t);

   /* Open database */
   Result = db.OpenDatabase();
   if( Result.Error ){
      return Result;
   }
   
   if(strftime(dateFormat,sizeof(dateFormat), "%Y-%m-%d %H:%M:%S", now)){
        /* Create SQL statement */
        Command << "INSERT INTO Historic_Temperature (Temperature,Humidity, Date) ";
        Command << "VALUES (" << Data.Temperature << "," << Data.Humidity << ",'" << dateFormat << "')";

        Result = db.ExecCommand(Command.str().c_str());

        db.CloseDatabase();
   }else{
       Result.Error = true;
       Result.Detail="Fail in convert Datetime";
   }
   
   return Result;
}