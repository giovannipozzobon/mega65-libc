/**
 * @file targets.h
 * @brief Target detection, e.g. Nexys4, Mega65R3, etc.
 */

#ifndef __MEGA65_TARGETS_H
#define __MEGA65_TARGETS_H

#include <stdint.h>

#define TARGET_UNKNOWN 0
#define TARGET_MEGA65R1 1
#define TARGET_MEGA65R2 2
#define TARGET_MEGA65R3 3
#define TARGET_MEGAPHONER1 0x21
#define TARGET_MEGAPHONER4 0x22
#define TARGET_NEXYS4 0x40
#define TARGET_NEXYS4DDR 0x41
#define TARGET_NEXYS4DDRWIDGET 0x42
#define TARGET_WUKONG 0xFD
#define TARGET_SIMULATION 0xFE
#define TARGET_EMULATION 0xFF //!< Emulator like Xemu

/// Detects the target on which we're running
uint8_t detect_target(void);

#endif // __MEGA65_TARGETS_H
