#ifndef _DHT11_
#define _DHT11_

#include <string>

enum class ErrorCodes{
    STB_NO_LOW_DETTECTED=-1,
    STB_NO_SEC_LOW_DETTECTED=-2,
    STB_NO_HIGH_DETTECTED=-3,
    BIT_NO_START_OF_BIT_DETTECTED=-4,
    BIT_NO_END_OF_BIT_DETTECTED=-5,
    BIT_UNKNOW_BIT_VALUE=-6,
    CHK_INVALID_CHECK_SUM=-7,

    DHT11_FAIL_OPEN_DEVICE=1,
    DHT11_FAIL_INVALID_MESSAGE=2
};

#define INTEGRAL_HUMD_DATA      0
#define DECIMAL_HUMD_DATA       1
#define INTEGRAL_TEMP_DATA      2
#define DECIMAL_TEMP_DATA       3


struct st_Response_Dht11{
    bool erro;
    ErrorCodes DescErro;
    float Temperature;
    float Humidity;
};

class Dht11{
    private:
        const static int Tam_Buffer=4;
        char Buffer_Rx[Tam_Buffer];
        std::string Dev_Path{"/dev/dht11"};
        float CastBytesToFloat(unsigned Integral,unsigned char Decimal);
        bool ModoDebug;
    public:
        Dht11(bool ModoDebug):ModoDebug{ModoDebug}{};
        Dht11():Dht11{false}{};
        st_Response_Dht11 Read_DHT11(void);
};


#endif