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

    space_packet_t unpacket;
    spp_unpack_packet(&unpacket, Data, Size);

    return 0; // The fuzzer expects 0
}