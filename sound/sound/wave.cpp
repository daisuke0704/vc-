#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//wavファイル関数
void wave_write(MONO_PCM* pcm, const char* filename)
{
    

    FILE* fp;
    int i;

    //wavファイル基本変数定義
    char riff_chunk_ID[4];
    int riff_chunk_size;
    char riff_form_type[4];
    char fmt_chunk_ID[4];
    int fmt_chunk_size;
    short int fmt_wave_format_type;
    short int fmt_channel;
    int fmt_samples_per_sec;
    int fmt_bytes_per_sec;
    short int fmt_block_size;
    short int fmt_bits_per_sample;
    char data_chunk_ID[4];
    int data_chunk_size;
    short int data;
    double s;



    riff_chunk_ID[0] = 'R';
    riff_chunk_ID[1] = 'I';
    riff_chunk_ID[2] = 'F';
    riff_chunk_ID[3] = 'F';

    riff_chunk_size = 36 + pcm->length * 2;

    riff_form_type[0] = 'W';
    riff_form_type[1] = 'A';
    riff_form_type[2] = 'V';
    riff_form_type[3] = 'E';

    fmt_chunk_ID[0] = 'f';
    fmt_chunk_ID[1] = 'm';
    fmt_chunk_ID[2] = 't';
    fmt_chunk_ID[3] = ' ';

    fmt_chunk_size = 16;
    fmt_wave_format_type = 1;
    fmt_channel = 1;
    fmt_samples_per_sec = pcm->fs; 
    fmt_bytes_per_sec = pcm->fs * pcm->bits / 8;
    fmt_block_size = pcm->bits / 8;
    fmt_bits_per_sample = pcm->bits;

    data_chunk_ID[0] = 'd';
    data_chunk_ID[1] = 'a';
    data_chunk_ID[2] = 't';
    data_chunk_ID[3] = 'a';

    data_chunk_size = pcm->length * 2;

    fp = fopen(filename, "wb");

    fwrite(riff_chunk_ID, 1, 4, fp);
    fwrite(&riff_chunk_size, 4, 1, fp);
    fwrite(riff_form_type, 1, 4, fp);
    fwrite(fmt_chunk_ID, 1, 4, fp);
    fwrite(&fmt_chunk_size, 4, 1, fp);
    fwrite(&fmt_wave_format_type, 2, 1, fp);
    fwrite(&fmt_channel, 2, 1, fp);
    fwrite(&fmt_samples_per_sec, 4, 1, fp);
    fwrite(&fmt_bytes_per_sec, 4, 1, fp);
    fwrite(&fmt_block_size, 2, 1, fp);
    fwrite(&fmt_bits_per_sample, 2, 1, fp);
    fwrite(data_chunk_ID, 1, 4, fp);
    fwrite(&data_chunk_size, 4, 1, fp);


    for (i = 0;i < pcm->length;i++) {
        s = (pcm->s[i] + 1.0) / 2.0 * 65536.0;
        //リミッター
        if (s > 65535.0) {
            s = 65535.0;
        }
        else if (s < 0.0) {
            s = 0.0;
        }

        data = (short)(s + 0.5) - 32768;
        fwrite(&data, 2, 1, fp);
    }

    fclose(fp);
}