/**
 * DE2 NIOS II audiocore perpheral driver
 *
 * (c) 2013 Peter McCormick (peter@pdmccormick.com)
 */

#ifndef __audiocore_h
#define __audiocore_h

/*
 * Set the bits of `audio_tone` according to which notes of a C major scale you
 * want to hear: bit 0 is C4, bit 1 is D4, and all the way up to C6
 */
extern int audio_tone;

void audiocore_init(void);
void audiocore_interrupt_handler(void);

#endif /* __audiocore_h */

