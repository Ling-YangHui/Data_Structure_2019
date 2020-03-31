/*hash 测试*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#define hash_mod 99991
#define hash_len 6

int hashcode[6] = {'A','y','a','c','h','i'};
void change_to_low(char *word)
{
	for (;*word != '\0';word ++)
		if (isupper(*word))
			*word = tolower(*word);
	return;
}
long long hash(char *word_cache)
{
	change_to_low(word_cache);
	long long hash_code = 0; 
	int len = strlen(word_cache);
	int i;
	/*
	for (i = 0;i < len;i ++)
	{
		hash_code += pow(hashcode[i % hash_len],len - i - 1) * word_cache[i];
		hash_code %= hash_mod;
	}
	*/
	for (i = 0;i < len;i ++)
	{
		hash_code += hashcode[i % hash_len] * word_cache[i] * hashcode[i % hash_len];
		hash_code %= hash_mod;
	}
	return hash_code;
} 

int main()
{
    char str[] = "hello";
    printf("%lld",hash(str));
    return 0;
}