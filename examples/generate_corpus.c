/**
 * @file examples/example_spp.c
 * @brief PROJECT
 *
 * DESCRIPTION
 *
 * @author astrobyte
 * @date 2026-04-08
 * @license GNU General Public License
 * @copyright Copyright (c) 2026 kevin Leon
 * @contact kevinleon.morales@gmail.com
 */
#include "spp/spp.h"
#include "vulnccsds.h"
#include <stdio.h>

int main(void) {
  const uint8_t data[] = "CorpusPayload";
  space_packet_t packet;
  if(spp_tm_build_packet(&packet, SPP_GROUP_FLAG_UNSEGMENTED,
                                      SPP_SECHEAD_FLAG_NOPRESENT, 0, 100, data, sizeof(data)) == SPP_ERROR_NONE){
    FILE *f = fopen("seeds.bin", "wb");
    if (f) {
      // Write the primary header (6 bytes)
      fwrite(&packet.header, 1, 6, f);
      // Write the payload based on the length field (remember length is data_len - 1)
      // HOST_TO_BE16 conversion implies we need to be careful with endianness on standard Macs, 
      // but assuming your packet structure is packed correctly:
      uint16_t len = (packet.header.length >> 8) | (packet.header.length << 8); // Quick swap for BE to Host if needed, or use your getter
      fwrite(packet.data, 1, len + 1, f);
      fclose(f);
    }
  }
  
  return 0;
}
