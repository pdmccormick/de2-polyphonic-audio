/**
 * DE2 NIOS II interrupt handling (C level)
 *
 * (c) 2013 Peter McCormick (peter@pdmccormick.com)
 */

#ifndef __interrupt_h
#define __interrupt_h

#include <stdint.h>

#include "nios2_hwdefs.h"

extern nios2_register_file interrupt_save_context;
extern uint8_t * const interrupt_handler_stack_top;

void interrupt_init(void);
void interrupt_hardware_handler(uint32_t ipending);
void interrupt_enable_irq(uint32_t irq);
void interrupt_disable_irq(uint32_t irq);

#endif /* __interrupt_h */

