#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "data.h"
#include "wave.cpp"
#include <windows.h>
#include "Setting.h"
//#include "Setting.cpp"
#define CHARBUFF 124


int main(int argc, char* argv[]){
    char info[CHARBUFF];
    char settingFile[CHARBUFF];
  
    //音声情報の宣言
    MONO_PCM pcm;
    int i;
    double A, f0;
    double ts;
    double time;
    char strBuf[100];
   
    time = 10.0;//再生時間

    pcm.fs = 8000;//サンプリング周波数
    pcm.bits = 16;//bit長

    ts = 1.0 / pcm.fs;

    pcm.length = (int)(time / ts + 0.5);//波長
    pcm.s = (double*)malloc(pcm.length * sizeof(double));

    A =1.0;//振幅
    f0 = 400.0;//基本周波数

    //波の情報の出力
    printf("ts = %.16lf\n", ts);
    printf("data length = %d\n", pcm.length);

    //sinカーブの作成
    for (i = 0;i < pcm.length;i++) {
        pcm.s[i] = A * sin(2.0 * 3.14 * f0 * i / pcm.fs);
    }

    wave_write(&pcm, "sine.wav");

    free(pcm.s);

    return 0;
}


