/**
 * @file sdcard.h
 * @brief Functions for accessing the SD card
 */
#ifndef __MEGA65_SDCARD_H
#define __MEGA65_SDCARD_H

#include <stdint.h>

#ifdef __cplusplus
// Being compiled by a C++ compiler, inhibit name mangling
extern "C" {
#endif

extern uint8_t sector_buffer[512];

void mega65_clear_sector_buffer(void);
void mega65_sdcard_reset(void);
void mega65_fast(void);
void mega65_sdcard_open(void);
void mega65_sdcard_map_sector_buffer(void);
void mega65_sdcard_unmap_sector_buffer(void);
uint8_t mega65_sdcard_readsector(const uint32_t sector_number);
uint8_t mega65_sdcard_writesector(const uint32_t sector_number);
void mega65_sdcard_erase(
    const uint32_t first_sector, const uint32_t last_sector);

#ifdef __cplusplus
} // End of extern "C"
#endif

#endif // __MEGA65_SDCARD_H
