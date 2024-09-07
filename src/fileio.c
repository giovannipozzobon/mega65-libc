#include <mega65/fileio.h>

bool toggle_rom_write_protect(void)
{
    unsigned char status;
    __attribute__((leaf)) __asm__ volatile("lda #$70  \n"
                                           "sta $d640 \n"
                                           "clv       \n"
                                           : /* output */ "=a"(status)
                                           : /* no input */
                                           : /* clobbers */ "v");
    bool write_protected = status & (unsigned char)(1 << 2);
    return write_protected;
}

void close(unsigned char fd)
{
    __attribute__((leaf)) __asm__ volatile("lda #$20  \n"
                                           "sta $d640 \n"
                                           "clv       \n"
                                           : /* no output */
                                           : /* input */ "x"(fd)
                                           : /* clobbers */ "a", "v");
}

void closeall(void)
{
    __attribute__((leaf)) __asm__ volatile("lda #$22  \n"
                                           "sta $d640 \n"
                                           "clv       \n"
                                           : /* no output */
                                           : /* no input */
                                           : /* clobbers */ "a", "v");
}

unsigned char get_current_drive(void)
{
    unsigned char drive_number;
    __attribute__((leaf)) __asm__ volatile("lda #$04  \n"
                                           "sta $d640 \n"
                                           "clv       \n"
                                           : /* output */ "=a"(drive_number)
                                           : /* no input */
                                           : /* clobbers */ "v");
    return drive_number;
}

unsigned char select_drive(const unsigned char drive_number)
{
    unsigned char error;
    __attribute__((leaf)) __asm__ volatile("lda #$06  \n"
                                           "sta $d640 \n"
                                           "clv       \n"
                                           : /* output */ "=a"(error)
                                           : /* input */ "x"(drive_number)
                                           : /* clobbers */ "v");
    return error;
}

unsigned char chdirroot(void)
{
    unsigned char error;
    unsigned char drive_number = 0; // hardcoded for now
    __attribute__((leaf)) __asm__ volatile("lda #$3C  \n"
                                           "sta $d640 \n"
                                           "clv       \n"
                                           : /* output */ "=a"(error)
                                           : /* input */ "x"(drive_number)
                                           : /* clobbers */ "v");
    return error;
}

void gethyppoversion(struct hyppo_version* version)
{
    __attribute__((leaf)) __asm__ volatile(
        "lda #$00  \n"
        "sta $d640 \n" // outputs to q = a,x,y,z
        "clv       \n"
        "stq (%0)  \n"
        "ldz #0    \n"
        : /* output */ "=r"(version)
        : /* no input */
        : /* clobbers */ "v", "a", "x", "y");
}
