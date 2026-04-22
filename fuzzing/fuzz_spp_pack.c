#include <stdint.h>
#include <stddef.h>
#include "spp/spp.h"
#include "vulnccsds.h"
#include <stdio.h>

// libFuzzer entry point
int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
    // Optional: Filter out inputs that are too small to be a valid header
    // to improve fuzzing performance.
    if (Size < 6) { 
        return 0; 
    }

    space_packet_t packet;
    
    // Assuming you have an unpack/parse function similar to this:
    // spp_unpack_packet(&packet, Data, Size);
    
    // If you strictly want to fuzz the builder you provided in the example:
    spp_tm_build_packet(&packet, 
        SPP_GROUP_FLAG_UNSEGMENTED, 
        SPP_SECHEAD_FLAG_NOPRESENT, 0, 100,
        Data, Size);

    return 0; // The fuzzer expects 0
}