// main.cpp
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "vulnccsds.h"
#include "spp/spp.h"

void hacker_mode(void){
  printf("Exploit me beibe!\n");
}

void procesar_paquete(const uint8_t *buffer, uint16_t len) {
    space_packet_t packet; // La víctima está ahora sola en este Stack Frame
    
    // Aquí ocurre el desbordamiento
    spp_tm_build_packet(&packet, 
                        SPP_GROUP_FLAG_UNSEGMENTED, 
                        SPP_SECHEAD_FLAG_NOPRESENT, 
                        0, 
                        100, 
                        buffer, 
                        len);
}

int main() {
    // Aumentamos el buffer de recepción para asegurarnos de que el atacante
    // tenga munición suficiente para el desbordamiento.
    uint8_t rx_buffer[2048];
    memset(rx_buffer, 0, sizeof(rx_buffer));

    printf("[SYSTEM] Waiting for incoming RF packet...\n");
    
    // Leemos hasta 2048 bytes
    ssize_t bytes_received = read(0, rx_buffer, sizeof(rx_buffer));
    if (bytes_received <= 0) {
        return 1;
    }

    printf("[SYSTEM] Received %zd bytes. Passing to SPP builder...\n", bytes_received);

    // 2. Pasamos los datos a la función vulnerable
    procesar_paquete(rx_buffer, (uint16_t)bytes_received);

    printf("[SYSTEM] Packet built successfully. Resuming normal operations.\n");
    return 0;
}