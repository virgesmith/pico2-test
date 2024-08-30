#pragma once

#include <hardware/flash.h>

#include <vector>

namespace flash {

// returns 0 if subsequent read matches whats requested to be written
// (so will be nonzero if b is longer than flash sector size and truncated)
uint32_t write(const std::vector<uint8_t>& b);

// will only read max 1 flash sector
std::vector<uint8_t> read(size_t length);

} // namespace flash
