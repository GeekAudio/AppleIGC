#include "../AppleIGC/igc/igc_rx_mbuf_validation.h"

#include <cstdio>
#include <cstdlib>
#include <cstdint>

static void check(bool condition, const char *name)
{
    if (!condition) {
        std::fprintf(stderr, "FAIL: %s\n", name);
        std::exit(1);
    }
}

int main()
{
    uint32_t expected = 0;

    check(igc_rx_mbuf_compute_expected_len(0, 1514, &expected),
          "first fragment length is computed");
    check(expected == 1514, "first fragment expected length");
    check(igc_rx_mbuf_metadata_is_valid(true, expected, 1514),
          "valid packet header and length are accepted");
    check(!igc_rx_mbuf_metadata_is_valid(false, expected, 1514),
          "missing M_PKTHDR is rejected");
    check(!igc_rx_mbuf_metadata_is_valid(true, expected, 1513),
          "short pkthdr length is rejected");
    check(!igc_rx_mbuf_metadata_is_valid(true, expected, 1515),
          "long pkthdr length is rejected");

    check(igc_rx_mbuf_compute_expected_len(1514, 128, &expected),
          "subsequent fragment length is computed");
    check(expected == 1642, "subsequent fragment expected length");
    check(!igc_rx_mbuf_compute_expected_len(UINT32_MAX, 1, &expected),
          "length overflow is rejected");

    std::puts("RX mbuf metadata checks passed");
    return 0;
}
