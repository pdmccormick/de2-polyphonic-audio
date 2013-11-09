/**
 * DE2 NIOS II interrupt handling (assembly level)
 *
 * (c) 2013 Peter McCormick (peter@pdmccormick.com)
 */

.align 4

.global interrupt_save_context
.global interrupt_handler_stack_top
.global interrupt_hardware_handler

/* The system exception handler */

.section .exceptions, "ax"
nios2_exception_entry_point:
    /* Load the address of where we save the context */
    movia et, interrupt_save_context

    /* NB: Ignoring registers at (r1), bt (r25), ba (r30) */
    /* stw r0,    0(et)     since r0 is always zero */
    /* stw r1,    4(et)     since r1==at */
    stw r2,    8(et)
    stw r3,   12(et)
    stw r4,   16(et)
    stw r5,   20(et)
    stw r6,   24(et)
    stw r7,   28(et)
    stw r8,   32(et)
    stw r9,   36(et)
    stw r10,  40(et)
    stw r11,  44(et)
    stw r12,  48(et)
    stw r13,  52(et)
    stw r14,  56(et)
    stw r15,  60(et)
    stw r16,  64(et)
    stw r17,  68(et)
    stw r18,  72(et)
    stw r19,  76(et)
    stw r20,  80(et)
    stw r21,  84(et)
    stw r22,  88(et)
    stw r23,  92(et)
    /* stw r24,  96(et)     since r24==et */
    /* stw r25, 100(et)     since r25==bt */
    stw r26, 104(et)
    stw r27, 108(et)
    stw r28, 112(et)
    stw r29, 116(et)        /* NB: r29==ea */
    /* stw r30, 120(et)     since r30==ba */
    stw r31, 124(et)

    /* Read IPENDING */
    rdctl r4, ctl4
    beq r4, r0, _software_trap

    /* Fall-through to _hardware_interrupt */

_hardware_interrupt:
    /* Adjust EA for correct return & re-save context */
    subi ea, ea, 4
    stw r29, 116(et)        /* NB: r29==ea */

    /* Switch to hardware IRQ handler stack */
    movia et, interrupt_handler_stack_top
    ldw sp, 0(et)

    call interrupt_hardware_handler

    jmpi _restore

_software_trap:
    /* TODO: Handle a software trap, ignoring this for now */

    /* Fall-through to _restore */

_restore:
    /* Restore from the same context */
    movia et, interrupt_save_context

    /* NB: Ignoring registers at (r1), bt (r25), ba (r30) */
    /* ldw r0,    0(et)     since r0 is always zero */
    /* ldw r1,    4(et)     since r1==at */
    ldw r2,    8(et)
    ldw r3,   12(et)
    ldw r4,   16(et)
    ldw r5,   20(et)
    ldw r6,   24(et)
    ldw r7,   28(et)
    ldw r8,   32(et)
    ldw r9,   36(et)
    ldw r10,  40(et)
    ldw r11,  44(et)
    ldw r12,  48(et)
    ldw r13,  52(et)
    ldw r14,  56(et)
    ldw r15,  60(et)
    ldw r16,  64(et)
    ldw r17,  68(et)
    ldw r18,  72(et)
    ldw r19,  76(et)
    ldw r20,  80(et)
    ldw r21,  84(et)
    ldw r22,  88(et)
    ldw r23,  92(et)
    /* ldw r24,  96(et)     since r24==et !!! */
    /* ldw r25, 100(et)     since r25==bt */
    ldw r26, 104(et)
    ldw r27, 108(et)
    ldw r28, 112(et)
    ldw r29, 116(et)        /* NB: r29==ea */
    /* ldw r30, 120(et)     since r30==ba */
    ldw r31, 124(et)

    eret

