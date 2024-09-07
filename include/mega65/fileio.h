/**
 * @file fileio.h
 * @brief File I/O functions
 *
 * If in C64 mode you must call `mega65_io_enable()` found in `memory.h`
 * before using any of the fileio functions.
 */

#ifndef __MEGA65_FILEIO_H
#define __MEGA65_FILEIO_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#ifdef __cplusplus
// Being compiled by a C++ compiler, inhibit name mangling
extern "C" {
#endif

/**
 * @brief Toggles write-protection for `$20000–$3FFFF`
 * @return True if write protected
 */
#ifdef __clang__
bool toggle_rom_write_protect(void);
#else
void toggle_rom_write_protect(void);
#endif

/** Closes all open files */
void closeall(void);

/**
 * @brief Closes a single file
 * @param fd File descriptor pointing to file to close
 */
void close(uint8_t fd);

/**
 * @brief Open file
 * @param filename to open
 * @return File descriptor or `0xff` if error
 */
#ifdef __clang__
__attribute__((leaf))
#endif
uint8_t
open(char* filename);

/**
 * @brief Read up to 512 bytes from file
 * @param buffer Input buffer
 * @return Number of bytes read
 */
#ifdef __clang__
__attribute__((leaf))
#endif
size_t
read512(uint8_t* buffer);

/**
 * @brief Change working directory
 * @param filename Directory name
 * @return Error code (currently unused)
 * @note Only accepts one directory segment at a time
 */
#ifdef __clang__
__attribute__((leaf))
#endif
uint8_t
chdir(char* filename);

/**
 * @brief Change working directory to the root directory
 * @return Error code from `hyppo_selectdrive`. 128 = no such drive.
 * @todo Should probably be deprecated in favor of `cdrootdir()` to better reflect hyppo naming.
 */
uint8_t chdirroot(void);

#ifdef __clang__
/** Get current drive number using `hyppo_getcurrentdrive` */
unsigned char get_current_drive(void);

/**
 * @brief Sets the currently selected drive (SD card partition)
 * @return Error code: 128 = no such drive.
 */
unsigned char select_drive(unsigned char);

#endif

/**
 * @brief Struct for holding version information of the hypervisor
 *
 * The HDOS in Hyppo is not related to the CBDOS inside the Kernal
 * or to the DOS in the disk drive units attached to the serial port.
 */
struct hyppo_version {
    uint8_t hyppo_major;
    uint8_t hyppo_minor;
    uint8_t hdos_major;
    uint8_t hdos_minor;
};

/**
 * @brief Get the version of the hypervisor
 * @param version Pointer to a `struct hyppo_version` to fill
 */
#ifdef __clang__
__attribute__((leaf))
#endif
void gethyppoversion(struct hyppo_version* version);

#ifdef __cplusplus
} // End of extern "C"
#endif

#endif // __MEGA65_FILEIO_H
