#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "data.h"
#include "wave.cpp"
#include <windows.h>

int main(int argc, char* argv[])
{
    MONO_PCM pcm;
    int i;
    double A, f0;
    double ts;
    double time;

    time = 10.0;/* time[sec] */

    pcm.fs = 8000;/* sampling frequency [Hz] */
    pcm.bits = 16;/* quantization bits [bits] */

    ts = 1.0 / pcm.fs;/* sampling period */

    pcm.length = (int)(time / ts + 0.5);/* length of sound data */
    pcm.s = (double*)malloc(pcm.length * sizeof(double));

    A = 1.0;/* amplitude */
    f0 = 400.0;/* the fundamental frequency [Hz] */

    printf("ts = %.16lf\n", ts);
    printf("data length = %d\n", pcm.length);

    //sine curve
    for (i = 0;i < pcm.length;i++) {
        pcm.s[i] = A * sin(2.0 * 3.14 * f0 * i / pcm.fs);
    }

    wave_write(&pcm, "sine.wav");

    free(pcm.s);

    return 0;
}