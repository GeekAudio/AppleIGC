#ifndef IGC_RX_MBUF_VALIDATION_H
#define IGC_RX_MBUF_VALIDATION_H

#include <stdbool.h>
#include <stdint.h>

static inline bool igc_rx_mbuf_compute_expected_len(uint32_t original_len,
                                                    uint32_t fragment_len,
                                                    uint32_t *expected_len)
{
    if (!expected_len || fragment_len > UINT32_MAX - original_len) {
        return false;
    }

    *expected_len = original_len + fragment_len;
    return true;
}

static inline bool igc_rx_mbuf_metadata_is_valid(bool has_packet_header,
                                                 uint32_t expected_len,
                                                 uint32_t actual_len)
{
    return has_packet_header && actual_len == expected_len;
}

#endif /* IGC_RX_MBUF_VALIDATION_H */
