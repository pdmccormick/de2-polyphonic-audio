/**
 * DE2 NIOS II hardware definitions
 *
 * (c) 2013 Peter McCormick (peter@pdmccormick.com)
 */

#ifndef __nios2_hwdefs_h
#define __nios2_hwdefs_h

#include <stdio.h>
#include <stdint.h>

#define NIOS2_NUM_REGISTERS     32
#define NIOS2_NUM_IRQS          32

#define NIOS2_REGS_AT           1
#define NIOS2_REGS_RETURN0      2
#define NIOS2_REGS_RETURN1      3
#define NIOS2_REGS_ARG0         4
#define NIOS2_REGS_ARG1         5
#define NIOS2_REGS_ARG2         6
#define NIOS2_REGS_ARG3         7
#define NIOS2_REGS_ET           24
#define NIOS2_REGS_BT           25
#define NIOS2_REGS_GP           26
#define NIOS2_REGS_SP           27
#define NIOS2_REGS_FP           28
#define NIOS2_REGS_EA           29
#define NIOS2_REGS_BA           30
#define NIOS2_REGS_RA           31

typedef union {
    uint32_t    ur[NIOS2_NUM_REGISTERS];
    int32_t     sr[NIOS2_NUM_REGISTERS];
} nios2_register_file;

#define CTL_STATUS          0
#define CTL_ESTATUS         1
#define CTL_BSTATUS         2
#define CTL_IENABLE         3
#define CTL_IPENDING        4
#define CTL_CPUID           5

#define CTL_STATUS_PIE      0x01
#define CTL_STATUS_U        0x02
#define CTL_STATUS_EH       0x04

#define NIOS2_CTL_READ_STATUS(dest)         do { asm volatile ("rdctl %0, ctl0" /* CTL_STATUS */ : "=r" (dest)) } while(0)
#define NIOS2_CTL_READ_IENABLE(dest)        do { asm volatile ("rdctl %0, ctl3" /* CTL_IENABLE */ : "=r" (dest)) } while(0)

#define NIOS2_CTL_WRITE_STATUS(status)      do { asm volatile ("wrctl ctl0, %0" /* CTL_STATUS */ : : "r"(status)); } while(0)
#define NIOS2_CTL_WRITE_IENABLE(ienable)    do { asm volatile ("wrctl ctl3, %0" /* CTL_IENABLE */ : : "r"(ienable)); } while(0)


/*
 * Red & Green LEDs
 */

#define LEDS_RED                0x10000000
#define LEDS_GREEN              0x10000010

static volatile uint32_t * const leds_red = (uint32_t *) LEDS_RED;
static volatile uint32_t * const leds_green = (uint32_t *) LEDS_GREEN;


/*
 * Sliders
 */

#define SLIDER_SWITCH_BASE      0x10000040

#define SLIDER_0                (1 << 0)
#define SLIDER_1                (1 << 1)
#define SLIDER_2                (1 << 2)
#define SLIDER_3                (1 << 3)
#define SLIDER_4                (1 << 4)
#define SLIDER_5                (1 << 5)
#define SLIDER_6                (1 << 6)
#define SLIDER_7                (1 << 7)
#define SLIDER_8                (1 << 8)
#define SLIDER_9                (1 << 9)
#define SLIDER_10               (1 << 10)
#define SLIDER_11               (1 << 11)
#define SLIDER_12               (1 << 12)
#define SLIDER_13               (1 << 13)
#define SLIDER_14               (1 << 14)
#define SLIDER_15               (1 << 15)
#define SLIDER_16               (1 << 16)
#define SLIDER_17               (1 << 17)

static volatile uint32_t * const slider_switch = (uint32_t *) SLIDER_SWITCH_BASE;


/*
 * Audiocore
 */

#define AUDIOCORE_BASE          0x10003040
#define AUDIOCORE_IRQ           6

#define AUDIOCORE_SAMPLE_RATE   48000

#define AUDIOCORE_FIFO_DEPTH    128
#define AUDIOCORE_FIFO_EMPTY_THRESHOLD      96

#define AUDIOCORE_CONTROL_RE    0x01        /** Read interrupt enable */
#define AUDIOCORE_CONTROL_WE    0x02        /** Write interrupt enable */
#define AUDIOCORE_CONTROL_CR    0x04        /** Clear left & right read FIFO's */
#define AUDIOCORE_CONTROL_CW    0x08        /** Clear left & right write FIFO's */
#define AUDIOCORE_CONTROL_RI    0x10        /** Read interrupt pending indicator */
#define AUDIOCORE_CONTROL_WI    0x12        /** Write interrupt pending indicator */

#define AUDIOCORE_FIFOSPACE_RA_RC   0x000000FF      /** Amount of read data available in right channel */
#define AUDIOCORE_FIFOSPACE_RA_LC   0x0000FF00      /** Amount of read data available in left channel */
#define AUDIOCORE_FIFOSPACE_WS_RC   0x00FF0000      /** Amount of write space left in right channel */
#define AUDIOCORE_FIFOSPACE_WS_LC   0xFF000000      /** Amount of write space left in left channel */

typedef union {
    uint32_t bits;
    struct __attribute__((packed)) {
        uint8_t re : 1;
        uint8_t we : 1;
        uint8_t cr : 1;
        uint8_t cw : 1;
        uint8_t ri : 1;
        uint8_t wi : 1;
    };
} audiocore_control_t;

typedef union {
    uint32_t bits;
    struct __attribute__((packed)) {
        uint8_t ra_rc : 8;
        uint8_t ra_lc : 8;
        uint8_t ws_rc : 8;
        uint8_t ws_lc : 8;
    };
} audiocore_fifospace_t;

static volatile audiocore_control_t * const audiocore_control = (audiocore_control_t *) AUDIOCORE_BASE;
static volatile audiocore_fifospace_t * const audiocore_fifospace = (audiocore_fifospace_t *) (AUDIOCORE_BASE + 4);
static volatile int32_t * const audiocore_leftdata = (int32_t *) (AUDIOCORE_BASE + 8);
static volatile int32_t * const audiocore_rightdata = (int32_t *) (AUDIOCORE_BASE + 12);


#endif /* __nios2_hwdefs_h */

