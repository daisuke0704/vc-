typedef struct
{
    int fs; /* sampling frequency (1.0/Ts)*/
            /* Ts : sampling period */
    int bits; /* quantization bit length */
    int length; /* length of a sound data */
    double* s; /* sound data */
}MONO_PCM;

void wave_write(MONO_PCM* pcm, const char* filename);