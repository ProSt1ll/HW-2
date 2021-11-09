#ifndef HW_2_FIND_WORDS_H
#define HW_2_FIND_WORDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <sys/msg.h>
#include <string.h>

int* find_word(const char *file_path,const char *file_word);
char *input_words(const char *file_path,int i);
int find_size(const char * word);
int find_size_word(const char *file_path);
int find_size_col_word(const char *file_path, int num);
int word_place(char *file, char *word);

#if defined(__cplusplus)
}
#endif

#endif //HW_2_FIND_WORDS_H