#include <iostream>
#include "SimpleGPIO.h"
#include "SimpleGPIO.cpp"
#include <stdint.h>
#include <unistd.h>

using namespace std;

int main()
{
   gpio_export(60); // Exporta o GPIO60 para que possa ser acessado
   gpio_set_dir(60, OUTPUT_PIN); // Configura o GPIO60 como saída
   
   for(uint32_t u32_i=0; u32_i<5; u32_i++)
   {
      gpio_set_value(60, LOW); // Inicia com o LED desligado
      usleep(1000000);
      gpio_set_value(60, HIGH); // Liga o LED
      usleep(1000000);
   }
   gpio_set_value(60, LOW);

   return 0;
}