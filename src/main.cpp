#include "Dht11.hpp"
#include <iostream>
#include <unistd.h>

#include "Dtos/Historic_Temperature.hpp"
#include "Dtos/Structures_Types.hpp"
#include "Models/Md_Historic_Temperature.hpp"

using namespace std;
using namespace Dto;

/*int main(){
    st_Response_Dht11 saida;
    Dht11 SensDht11{true};

    saida = SensDht11.Read_DHT11();
    cout << "Saida Erro " << saida.erro << " Saida Temp " << saida.Temperature << " Saida Hum " << saida.Humidity << endl;
        
    return 0;
}*/

int main(){
    Historic_Temperature st;
    
    Model::Historic_Temperature stmodel;
    
    st_Response_Dht11 saida;
    Dht11 SensDht11{true};
    
    do{
        saida = SensDht11.Read_DHT11();
        stmodel.Temperature = saida.Temperature;
        stmodel.Humidity = saida.Humidity;

        cout << "Result DHT11 " << saida.erro << " Saida Temp " << saida.Temperature << " Saida Hum " << saida.Humidity << endl;
        
        DbStructures::st_ResultDatabase resultdb = st.Insert_Temperature(stmodel);
        cout << "Result DataBase " << saida.erro << " " << endl;
        sleep(10);
    }while(true);
    return 0;
}