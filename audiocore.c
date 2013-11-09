/**
 * DE2 NIOS II audiocore peripheral driver
 *
 * (c) 2013 Peter McCormick (peter@pdmccormick.com)
 */

#include <stdint.h>

#include "nios2_hwdefs.h"
#include "audiocore.h"
#include "sine_wave.h"

int audio_tone = 0;

static void fill_fifo(int how_much);

void audiocore_init(void)
{
    audio_tone = 0;

    // Clear out all read & write FIFO's for both channels
    audiocore_control->bits = AUDIOCORE_CONTROL_CR | AUDIOCORE_CONTROL_CW;
    
    fill_fifo(AUDIOCORE_FIFO_DEPTH);

    // Enable write interrupt
    audiocore_control->bits = AUDIOCORE_CONTROL_WE;

    interrupt_enable_irq(AUDIOCORE_IRQ);
}

void audiocore_interrupt_handler()
{
    /* Do we need to top up the FIFO again? */
    if (audiocore_control->bits & AUDIOCORE_CONTROL_WI) {
        /* NB: We are always filling left and right equally */
        fill_fifo(audiocore_fifospace->ws_rc);
    }
}

#define NUM_PITCH   18

/**
 * 18 notes worth of ascending C major scale notes (C4-F6)
 *
 * Thanks to http://www.phy.mtu.edu/~suits/notefreqs.html
 */
static const int freqs[] = {
    /* C4 through to B4 */
    261, 293, 329, 349, 392, 440, 493,
   
    /* C5 through B5 */
    523, 587, 659, 698, 784, 880, 988,

    /* C6 through F6 */
    1046, 1175, 1319, 1396,
};

static int sine_i[NUM_PITCH] = {};

/**
 * Fill the left & right channel output FIFO according to the desired tones.
 *
 * Based on the frequencies in the `freqs` array, we super-sample a 1Hz sine
 * wave (with data from the `sine_wave` array), averaging multiple pitches
 * together to create the desired polyphonic output.
 */
static void fill_fifo(int how_much)
{
    int i;
    for (i = 0; i < how_much; i++) {
        int32_t sample = 0;
        int num_unique = 0;

        int mask = 1;
        int j;
        for (j = 0; j < NUM_PITCH; j++, mask <<= 1) {
            if (!(audio_tone & mask))
                continue;

            sample += sine_wave[sine_i[j]];
            num_unique++;
        }

        // Fit the mixed sample into a signed 16-bit value
        sample /= num_unique;

        // Shift the sample into the high order bits and write to FIFO
        sample <<= 16;
        *audiocore_leftdata = sample;
        *audiocore_rightdata = sample;
      
        // Advance the index counters by their super-sampled frequency 
        mask = 1; 
        for (j = 0; j < NUM_PITCH; j++, mask <<= 1) {
            if (!(audio_tone & mask))
                continue;
            
            int freq_step = freqs[j];
            sine_i[j] = (sine_i[j] + freq_step) % AUDIOCORE_SAMPLE_RATE;
        }
    }
}

