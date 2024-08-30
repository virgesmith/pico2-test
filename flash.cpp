
#include "flash.h"

#include <hardware/sync.h> // for interrupts

#include <algorithm>
#include <pico/stdlib.h>

namespace {
const uint32_t storage_offset = PICO_FLASH_SIZE_BYTES - FLASH_SECTOR_SIZE; // last sector
const uint8_t* storage_address = reinterpret_cast<uint8_t*>(XIP_BASE + storage_offset);
} // namespace

uint32_t flash::write(const std::vector<uint8_t>& b) {
  uint32_t length = std::min(b.size(), FLASH_SECTOR_SIZE);
  uint32_t ints = save_and_disable_interrupts();
  flash_range_erase(storage_offset, length);
  flash_range_program(storage_offset, b.data(), length);
  restore_interrupts(ints);
  // now read to confirm
  std::vector<uint8_t> check = flash::read(length);
  return b == check ? 0 : -1u; // this will be nonzero if b longer than FLASH_SECTOR_SIZE
}

std::vector<uint8_t> flash::read(size_t length) {
  length = std::min(length, FLASH_SECTOR_SIZE);
  return std::vector<uint8_t>(storage_address, storage_address + length);
}
