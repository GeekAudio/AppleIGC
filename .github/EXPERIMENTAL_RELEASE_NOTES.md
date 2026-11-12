## Experimental test candidate

This prerelease adds defensive RX metadata validation around `mbuf_copyback()` and uses `MBUF_DONTWAIT` so RX allocation does not wait for memory. If allocation fails, the existing RX discard path drops the rest of that frame. Invalid packet-header flags, length overflow, or a mismatched packet-header length are dropped before the packet enters IONetworkingFamily.

This is a hypothesis-driven hardening candidate, **not a confirmed fix** for the `M_PKTHDR` kernel panic. It has passed the standalone metadata regression test and an Xcode Release build, but has not been tested on real I225-V/I226 hardware or under network stress. `MBUF_DONTWAIT` can drop packets under memory pressure. Keep a bootable EFI backup and revert if the panic or new network instability occurs.

## Separate compatibility reports

Upstream issue #40 reports an I225-V rev02 MSI/no-RX problem, while reports in PR #38 include mixed outcomes. These are separate reports, and the relationship and cause are unverified. This candidate does not change MSI or INTx handling and does not claim to address that issue.
