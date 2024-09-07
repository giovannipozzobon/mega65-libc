#include <mega65/memory.h>
#include <mega65/debug.h>

#ifdef __CC65__
unsigned char the_char;
#endif

void debug_msg(char* msg)
{
    while (msg != NULL && *msg != 0) {
#ifdef __CC65__
        the_char = *msg;
        __asm__("LDA %v", the_char);
        __asm__("STA $D643");
        __asm__("CLV");
#else
        __attribute__((leaf)) asm volatile("st%0 $d643\n"
                                           "clv\n"
                                           :           /* no output operands */
                                           : "a"(*msg) /* input operands */
                                           : "p" /* clobber list */);
#endif
        msg++;
    }
#ifdef __CC65__
    __asm__("LDA #$0d");
    __asm__("STA $D643");
    __asm__("CLV");
    __asm__("LDA #$0a");
    __asm__("STA $D643");
    __asm__("CLV");
#else
    // clearing Z seems to fix occasional xemu freeze. Why?
    __attribute__((leaf)) asm volatile("lda #$0d  \n"
                                       "sta $d643 \n"
                                       "clv       \n"
                                       "lda #$0a  \n"
                                       "sta $d643 \n"
                                       "clv       \n"
                                       "ldz #0    \n"
                                       : /* no output operands */
                                       : /* no input operands*/
                                       : "a", "p" /* clobber list */);
#endif
}
