
#include <iostream>
#include "SimpleGPIO.h"
#include "SimpleGPIO.cpp"
#include <stdint.h>
#include <unistd.h>

using namespace std;

int main()
{
    gpio_export(71);  // Exporta o GPIO71 para que possa ser acessado
    gpio_set_dir(71, OUTPUT_PIN);  // Configura o GPIO71 como saída

    for(uint32_t u32_i=0; u32_i<20; u32_i++)
    {
        gpio_set_value(71, LOW);  // Inicia com o LED desligado
        usleep(1000000);
        gpio_set_value(71, HIGH);  // Liga o LED
        usleep(1000000);
    }

    gpio_set_value(71, LOW);

    return 0;
}
