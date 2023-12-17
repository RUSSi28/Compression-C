#include <stdio.h>
#define FILE_MAX 64

//リストの長さを保持
int length = 0;

//runLengthは語の重複を許す
//huffmanは語の重複を許さない(一文字ずつ構造体で表す)
struct wordInfo
{
    int id;
    char word;
    int symbol; //ハフマン法の際の符号
    int numOfTimes;
    struct wordInfo *next;
};


struct wordInfo *firstElement = NULL;
struct wordInfo *refElement = NULL;
struct wordInfo *iteration = NULL;

//標準ストリームから受け取った文字列のファイルに対しランレングス法を実行する関数
struct wordInfo runLength()
{
    FILE *fpr;
    FILE *fpw;
    int c; //char型にキャストして使う
    char str[FILE_MAX];


    printf("ファイル名を入力して下さい(拡張子を含める)\n");
    scanf("%s",str);


    if (fopen(str, "r") == NULL)
    {
        printf("\aファイルをオープンできません");
        
    } else 
    {
        fpr = fopen(str, "r");

        while ((c = fgetc(fpr)) != EOF)
        {
            if(firstElement == NULL) 
            {
                //一番はじめの処理
                struct wordInfo wi = {
                    length, c, -1, 1, NULL
                    };
                length ++;
                firstElement = &wi;
                refElement = &wi;

            } else 
            {
                if ((char)c == refElement->word)
                {
                    //以前の文字情報の回数をインクリメント
                    refElement->numOfTimes += 1;

                } else 
                {
                    //新しい文字情報を開始する前に文字情報を出力する
                    fpw = fopen("encode.txt", "a");
                    fprintf(fpw, "%s", &refElement->word);
                    fprintf(fpw, "%d", refElement->numOfTimes);
                    fclose(fpw);

                    //新しい文字情報を開始する
                    struct wordInfo wi = {
                        length, c, -1, 1, NULL
                        };
                    length ++;
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


//以下ハフマン法のための関数群
//ファイル内の文字数を返す
// int numOfAllWord(char str[FILE_MAX], FILE *fp)
// {
//     int total = 0;
//     int c1;

//     while ((c1 = fgetc(fp)) != EOF)
//     {
//         total ++;
//     }

//     return total;
// }


//文字の出現率を返す
float wordRateOfAll(float allWord, float partOfWord)
{
    return partOfWord/allWord;
}


struct wordInfo huffman() 
{
    FILE *fpr;
    FILE *fpw;
    int total = 0;
    int c; //char型にキャストして使う
    char str[FILE_MAX];
    int bool = 1; //0, 1でfalse, true 一度出てきた文字か否かを調べる

    
    printf("ファイル名を入力して下さい(拡張子を含める)\n");
    scanf("%s",str);
    fpr = fopen(str, "r");
    while ((c = fgetc(fpr)) != EOF)
    {
        total ++;
    }
    fclose(fpr);
    

    if (fopen(str, "r") == NULL)
    {
        printf("\aファイルをオープンできません");
        
    } else 
    {
        fpr = fopen(str, "r");
        //ファイル中のそれぞれの文字の出現率を調べ、ハフマン符号をつくる
        while ((c = fgetc(fpr)) != EOF)
        {
            if (firstElement == NULL)
            {
                struct wordInfo wi = {
                    length, c, -1, 1, NULL 
                };
                length ++;
                firstElement = &wi;
                refElement = &wi;
            } else 
            {
                iteration = firstElement;
                bool = 1;
                while (iteration->next != NULL)
                {
                    printf("aho");
                    if (iteration->word == (char)c)
                    {
                        iteration->numOfTimes ++;
                        bool = 0;
                        break;
                    }
                    // iteration = iteration->next;
                }


                //wordInfoのリストをすべて見終わったあとでリストの後部に新しい要素を付け足す
                if (bool == 1)
                {
                    struct wordInfo wi = {
                        length, c, -1, 1, NULL
                    };
                    iteration->next = &wi;
                }
                
                
            }
        }
        // iteration = firstElement;
        // while (iteration != NULL)
        // {
        //     float wordRate = wordRateOfAll((float)total, (float)(iteration->numOfTimes));
        //     printf("%s", &iteration->word);
        //     printf("%f", wordRate);
        //     iteration = iteration->next;
        // }
        
        // fpw = fopen("encode.txt", "a");
        // fclose(fpw);

        fclose(fpr);
        
    }
};




int main(void) 
{
    int wayOfCompression;
    printf("圧縮方法を選択してください。\n");
    printf("1: ランレングス法\n");
    printf("2: ハフマン法\n\n");

    scanf("%d",&wayOfCompression);
    if (wayOfCompression == 1) 
    {
        //ランレングス法の呼び出し(同じ値の並ぶ画像データ(特に白黒二値)の圧縮)
        runLength();
    } else if (wayOfCompression == 2) 
    {
        //ハフマン法の呼び出し(可逆圧縮でテキストの圧縮等)
        huffman();
    } else 
    {
        printf("不正な値が入力されました。操作をやり直して下さい。\n");
    }

}