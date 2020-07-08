#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "data.h"
#include "wave.cpp"
#include <windows.h>
//#include "Setting.h"
#include "Setting.cpp"
#define CHARBUFF 124


int main(int argc, char* argv[])
{

    char currentDirectory[CHARBUFF];
    getCurrentDirectory(currentDirectory);



    char info[CHARBUFF];
    char settingFile[CHARBUFF];

    //sprintf_s(settingFile, "%s\\sound.ini", currentDirectory);
    readDouble("wave1", "A", 0, info);

    
  
    MONO_PCM pcm;
    int i;
    double A, f0;
    double ts;
    double time;
    char strBuf[100];
   

    time = 10.0;/* time[sec] */

    pcm.fs = 8000;/* sampling frequency [Hz] */
    pcm.bits = 16;/* quantization bits [bits] */

    ts = 1.0 / pcm.fs;/* sampling period */

    pcm.length = (int)(time / ts + 0.5);/* length of sound data */
    pcm.s = (double*)malloc(pcm.length * sizeof(double));

    A =atof(info);/* amplitude */
    f0 = 400.0;/* the fundamental frequency [Hz] */

    printf("ts = %.16lf\n", ts);
    printf("data length = %d\n", pcm.length);

    //sine curve
    for (i = 0;i < pcm.length;i++) {
        pcm.s[i] = A * sin(2.0 * 3.14 * f0 * i / pcm.fs);
    }

    wave_write(&pcm, "sine3.wav");

    free(pcm.s);

    return 0;
}


