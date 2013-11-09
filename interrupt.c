/**
 * DE2 NIOS II interrupt handling (C level)
 *
 * (c) 2013 Peter McCormick (peter@pdmccormick.com)
 */

#include <stdint.h>

#include "interrupt.h"
#include "audiocore.h"
#include "nios2_hwdefs.h"

#define INTERRUPT_HANDLER_STACK_SIZE        2048

nios2_register_file interrupt_save_context;

static uint8_t handler_stack[INTERRUPT_HANDLER_STACK_SIZE];

/* A pointer to the top of the interrupt handler stack */
uint8_t * const interrupt_handler_stack_top = (uint8_t *) &handler_stack[sizeof (handler_stack)];

static uint32_t status;
static uint32_t ienable;

void interrupt_init()
{
    status = 0;
    ienable = 0;

    NIOS2_CTL_WRITE_STATUS(status);
    NIOS2_CTL_WRITE_IENABLE(ienable);
}

void interrupt_hardware_handler(uint32_t ipending)
{
    if (ipending & (1 << AUDIOCORE_IRQ)) {
        audiocore_interrupt_handler();
    }
}

void interrupt_enable_irq(uint32_t irq)
{
    status |= CTL_STATUS_PIE;
    ienable |= (1 << irq);

    NIOS2_CTL_WRITE_STATUS(status);
    NIOS2_CTL_WRITE_IENABLE(ienable);
}

void interrupt_disable_irq(uint32_t irq)
{
    ienable &= ~(1 << irq);
    status = (status & ~CTL_STATUS_PIE) | (ienable ? CTL_STATUS_PIE : 0);

    NIOS2_CTL_WRITE_STATUS(status);
    NIOS2_CTL_WRITE_IENABLE(ienable);
}

