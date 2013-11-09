DE2 Polyphonic Audio Demo
=========================

Peter McCormick
peter@pdmccormick.com


Introduction
------------

This is a small demo of driving the audio outputs on a DE2 FPGA dev board
running a NIOS II soft core processor, by polyphonically mixing pitches from
over two octaves of a C major scale (with the notes controlled by the slider
switches.)

This code is placed in the public domain, provide 'as is' and without any
warranty whatsoever. The user assumes all risk by running or using it.


Getting Started
---------------

Using the Altera Monitor Program, create a new C language project and add all
the C (*.c) and assembly code (*.s). Under 'Memory Settings', set the "Start
offset in device (hex)" fields to '1000' for both the .text and .data section
(this offset makes room for the exception handler code.) Download to your DE2
board, plug in speakers or headphones, compile and run.

Use the slider switches from right (SW0 as C4) to left (SW17 as F6) to play
scales, chords or melodies.

WARNING: Beware that the audio played is at full volume (amplitude), so either
use speakers with a volume control or do not immediately put your headphones up
to your ears until you know just how loud that is.


Ideas
-----

Change mono output to something interesting in stereo.

Save 48KB of memory by noticing that the second half of the `sine_wave` array
is a reflected, negated version of the first.

Implement a multi-thousand sample software FIFO that feeds into the hardware
FIFO to ease timing restrictions.

Handle audio input and output together (whether in pass-through or simply up to
a higher layer of software.)

Generate harmonically richer tones than pure sine waves.

Implement a mixing strategy more sophisticated than just averaging.

Add effects like chorusing or delay.

