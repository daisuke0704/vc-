//変数の構造体

typedef struct
{
    int fs; //サンプリング周波数
    int bits; //bit長
    int length; //波長
    double* s; //波のデータ
}MONO_PCM;