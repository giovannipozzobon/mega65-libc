.global lpoke, lpeek
.section code, "a"
lpoke:
        ; copy 32-bit input address (a, x, rc2-rc3) to rc5-rc8
        sta __rc5
        stx __rc6
        lda __rc2
        sta __rc7
        lda __rc3
        sta __rc8
        ; 8-bit input value (rc4)
        lda __rc4
        ldz #0
        nop
        sta (__rc5), z
        ldz #0
        rts
lpeek:
        ; copy 32-bit input address (a, x, rc2-rc3) to rc4-rc7
        sta __rc4
        stx __rc5
        lda __rc2
        sta __rc6
        lda __rc3
        sta __rc7
        ldz #0
        ldx #0
        nop
        lda (__rc4), z
        ldz #0
        rts
