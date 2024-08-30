#include <pico/sha256.h>

#include <pico/stdlib.h>

#include <vector>

inline std::vector<uint8_t> hw_sha256(const std::vector<uint8_t>& data) {
  pico_sha256_state_t state;
  sha256_result_t result;
  if (pico_sha256_try_start(&state, SHA256_BIG_ENDIAN, true) == PICO_OK) {
    pico_sha256_update(&state, data.data(), data.size());
    pico_sha256_finish(&state, &result);
  }
  // returns garbage if not PICO_OK
  return std::vector<uint8_t>(result.bytes, result.bytes + SHA256_RESULT_BYTES);
}
