#ifndef _STATUS_SENSORS_DTO_
#define _HISTORIC_STATUS_SENSORS_DTO__TEMPERATURE_DTO_

#include "../Models/Md_Status_Sensors.hpp"
#include "Structures_Types.hpp"
namespace Dto{
    class Status_Sensors{
        public:
            Status_Sensors(){};
            DbStructures::st_ResultDatabase Update_Sensors(Model::Status_Sensors&);
            DbStructures::st_ResultStaus_Sensor Read_Sensors();
    };
}


#endif