#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int StrLen(const char * str1);
int StrCmp(const char * str1, const char * str2);
char * StrCpy(char * str1, const char * str2);
char * StrCat(char * str1, const char * str2);
const char * StrStr(const char *haystack, const char *needle);
const char * StrChr(const char * str1, int c);
int Atoi(const char * str);
char * Itoa(int n, char str[]);
char * StrDup(const char * str);

int main(void){
    char str1[100] = "AAA";
    char str3[100] = "AAA";
    char str[] = "xxx";
    const char * str2 = "bbbbbaAannnn";
    int n = 'A';
    printf("%d\n", Atoi("1234")+1);
    printf("%s\n", Itoa(123124,str));
    printf("%s\n", StrDup(str2));
}

int StrCmp(const char * str1, const char * str2) {
    int j = 0;

    while((str1[j] != '\0') || (str2[j] != '\0')) {
        if (str1[j] != str2[j]) {
            return (StrLen(str1)-StrLen(str2));
        }
        j++;
    }

    return 0;
}


int StrLen(const char * str){
    int j = 0;
    while(str[j] != '\0'){
        j++;
    }
    return j;
}

char * StrCpy(char * dst, const char * src){
    int j = 0;
     while(src[j] != '\0'){
        dst[j] = src[j];
        j++;
    }
    return dst;
}

const char * StrChr(const char * str1, int c){
    int j = 0;
    while(str1[j] != '\0'){
        if(str1[j] == c){
            return &str1[j];
        }
        j++;
    }
    return NULL;
}
const char * StrStr(const char *haystack, const char *needle){
    int n = 0;
    while(needle[n] != '\0'){
        n++;
    }
    int j = 0;
    int b = 0;
    while(haystack[j] != '\0'){
        if(haystack[j] == needle[0]){
            int i = 0;
            while(needle[i] != '\0'){
                if(needle[i] != haystack[j+i]){
                    b=1;
                }
                i++;
            }
            if (b==1){
                return &haystack[j-n];
            }
            else {
                b=0;
            }
        }
        j++;
    }
    return NULL;
}

char * StrCat(char * dst, const char * src){
    int j = 0;
    int n=StrLen(dst);
    do{
        dst[n+j] = src[j];
    } while(src[j++] != '\0');

    return dst;
}

int Atoi(const char * str){
    int sum = 0;
    int n = StrLen(str);
    for(int i = 0;i<n;i++){
        sum += (str[n-i-1]-48)*pow(10, i);
    }
    return sum;
}

char * Itoa(int n, char str[]){
    int a =n;
    int j=0;
    while(a>10){
        a /= 10;
        j++;
    }
    int i=0;
    while(n>0){
        str[j-i] = n%10 + '0';
        n /= 10;
        i++;
    }
    str[j+1]= '\0';
    return str;
}

char * StrDup(const char * str){
    char * dst  = (char*)calloc(StrLen(str) + 1, sizeof(char));
    StrCpy(dst, str);
    return dst;
}
