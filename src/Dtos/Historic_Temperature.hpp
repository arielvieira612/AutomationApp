#ifndef _HISTORIC_TEMPERATURE_DTO_
#define _HISTORIC_TEMPERATURE_DTO_

#include "../Models/Md_Historic_Temperature.hpp"
#include "Structures_Types.hpp"
namespace Dto{
    class Historic_Temperature{
        public:
            Historic_Temperature(){};
            DbStructures::st_ResultDatabase Insert_Temperature(Model::Historic_Temperature&);;
    };
}


#endif