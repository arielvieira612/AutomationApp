#ifndef _STRUCTURE_TYPES_
#define _STRUCTURE_TYPES_

#include <string>
#include "../Models/Md_Status_Sensors.hpp"

namespace DbStructures{ 
    struct st_ResultDatabase{
        bool Error;
        std::string Detail;
        
    };

    struct st_ResultStaus_Sensor:st_ResultDatabase{
        Model::Status_Sensors Status;
        st_ResultDatabase& operator=(const st_ResultDatabase& base){
            this->Error =  base.Error;
            this->Detail = base.Detail;
            return *this;
        };
    };
}

#endif

