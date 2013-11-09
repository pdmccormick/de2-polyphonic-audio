"""
Generates a C array lookup table for a 1Hz sine wave

(c) 2013 Peter McCormick (peter@pdmccormick.com)
"""

from math import pi, sin

# signed 16-bit value
max_value = (0xFFFF >> 1)
num_samples = 48e3

def chunk(data, stride):
    return [ data[i:i + stride] for i in range(0, len(data), stride) ]

if __name__ == '__main__':
    coeff = (2 * pi) / num_samples
    sine_wave = map(sin, [ (coeff * i) for i in range(int(num_samples)) ])
    sine_u = [ int(max_value * k) for k in sine_wave ]

    preamble = "    "
    joiner = "," + "\n" + preamble
    values = preamble + joiner.join([ ", ".join(ys) for ys in ([ map(str, xs) for xs in chunk(sine_u, 8) ]) ])

    print "/* Generated by mksine.py: num_samples=%d, max_value=0x%x */\n" % (num_samples, max_value)
    print "#include <stdint.h>\n"

    fmt = "static const int16_t sine_wave[{num_samples}] = {{\n{values}\n}};\n"
    print fmt.format(num_samples=int(num_samples), values=values)

