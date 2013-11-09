/**
 * DE2 NIOS II audio demo
 *
 * (c) 2013 Peter McCormick (peter@pdmccormick.com)
 */

#include <stdio.h>
#include <stdint.h>

#include "audiocore.h"
#include "nios2_hwdefs.h"

int main()
{
    interrupt_init();
    audiocore_init();

    *leds_red = 0;
    int current, last;
   
    current = *slider_switch;
    last = ~current;

    /* A very busy loop */
    for (;;) {
        current = *slider_switch;

        if (last != current) {
            audio_tone = *slider_switch;
            *leds_red = audio_tone;

            printf("audio_tone 0x%x\n", audio_tone);
        }

        last = current;
    }
}

