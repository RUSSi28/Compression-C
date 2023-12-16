#include <stdio.h>

//リストの長さを保持
int length = 0;

//runLengthは語の重複を許す
//huffmanは語の重複を許さない(一文字ずつ構造体で表す)
struct wordInformation
{
    int id;
    char word;
    int symbol; //ハフマン法の際の符号
    int numOfTimes;
    struct wordInformation *next;
};


struct wordInformation *firstElement = NULL;
struct wordInformation *refElement = NULL;

//標準ストリームから受け取った文字列のファイルに対しランレングス法を実行する関数
struct wordInformation runLength(){
    FILE *fpr;
    FILE *fpw;
    int c; //char型にキャストして使う
    char str[FILENAME_MAX];


    printf("ファイル名を入力して下さい(拡張子を含める)");
    scanf("%s",str);


    if (fopen(str, "r") == NULL){
        printf("\aファイルをオープンできません");

    } else {
        fpr = fopen(str, "r");

        while ((c = fgetc(fpr)) != EOF){
            if(firstElement == NULL) {
                //一番はじめの処理
                struct wordInformation wi = {length, c, -1, 1, NULL} ;
                length += 1;
                firstElement = &wi;
                refElement = &wi;

            } else {
                if ((char)c == refElement->word){
                    //以前の文字情報の回数をインクリメント
                    refElement->numOfTimes += 1;

                } else {
                    //新しい文字情報を開始する前に文字情報を出力する
                    fpw = fopen("encode.txt", "a");
                    fprintf(fpw, "%s", &refElement->word);
                    fprintf(fpw, "%d", refElement->numOfTimes);
                    fclose(fpw);

                    //新しい文字情報を開始する
                    struct wordInformation wi = {length, c, -1, 1, NULL} ;
                    length += 1;
                    refElement->next = &wi;
                    refElement = &wi;

                }
            }   
        }
        fpw = fopen("encode.txt", "a");
        fprintf(fpw, "%s", &refElement->word);
        fprintf(fpw, "%d", refElement->numOfTimes);
        fclose(fpw);

        fclose(fpr);
        
    }
};

int main(void) {
    int wayOfCompression;
    printf("圧縮方法を選択してください。");
    printf("1: ランレングス法");
    printf("2: ハフマン法");

    scanf("%d",&wayOfCompression);
    if (wayOfCompression == 1) {
        runLength();
    } else if (wayOfCompression == 2) {
        /* code */
    } else {
        printf("不正な値が入力されました。操作をやり直して下さい。");
    }

}