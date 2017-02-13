#include "Dht11.hpp"
#include <errno.h>
#include <string.h>
#include <fstream>      // std::ifstream
#include <iostream>

using namespace std;

st_Response_Dht11 Dht11::Read_DHT11(void){
    st_Response_Dht11 saida;
    int state=0;
    bool fim=false;
    ifstream filedriver;

    if(ModoDebug){
        saida.erro = false;
        saida.Humidity = 80.3;
        saida.Temperature = 22.56;
        return saida;
    }

    do{
        switch(state){
            case 0:
                filedriver.open("DEV_PATH", ios::in | ios::binary);           // Open the device with read access
                if (!filedriver.is_open()){
                    saida.erro = true;
                    saida.DescErro = ErrorCodes::DHT11_FAIL_OPEN_DEVICE;
                }
                state++;
            break;
            case 1:
                filedriver.read(Buffer_Rx,Tam_Buffer);
                
                if (!filedriver.good()){
                    saida.erro = true;
                    saida.DescErro = ErrorCodes::DHT11_FAIL_INVALID_MESSAGE;
                    fim=true;
                }
                filedriver.close();
                state++;     
            break;
            case 2:
                saida.Humidity = CastBytesToFloat(Buffer_Rx[INTEGRAL_HUMD_DATA],Buffer_Rx[DECIMAL_HUMD_DATA]);
                saida.Temperature = CastBytesToFloat(Buffer_Rx[INTEGRAL_TEMP_DATA],Buffer_Rx[DECIMAL_TEMP_DATA]);
            break;
        }

    }while((!saida.erro)&&(!fim));

    return saida;
}

float Dht11::CastBytesToFloat(unsigned Integral,unsigned char Decimal){
    float saida;
    saida = Integral;
    saida += (Decimal/10);
    return saida;
}