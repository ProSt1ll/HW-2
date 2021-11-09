#include "find_words.h"


int *find_word(const char *file_path, const char *file_word) {
    if (file_path == NULL) {
        return 0;
    }

    char *ptr = input_words(file_path, 1);
    if (ptr == NULL) {
        return NULL;
    }

    int words_size = find_size_word(file_word);
    int *ind = (int *) calloc(words_size, sizeof(int));

    for (int i = 0; i < words_size; i++) {
        char *cur_word = input_words(file_word, i + 1);
        ind[i] = word_place(ptr, cur_word);
        free(cur_word);
    }

    free(ptr);
    return ind;
}


int find_size(const char *word) {
    if (word == NULL) {
        return 0;
    }
    int i = 0;
    while (word[i] != '\0') {
        i++;
    }
    return i;

}


char *input_words(const char *file_path, int num) {
    if ((file_path == NULL) || (num < 1)) {
        return NULL;
    }
    FILE *ptr = fopen(file_path, "r");

    if (ptr == NULL) {
        return NULL;
    }

    size_t i;
    int size_col = find_size_col_word(file_path, num);
    char *array = (char *) calloc(size_col,sizeof(char *));

    if (array == NULL) {
        fclose(ptr);
        return NULL;
    }
    char c =0;
    for (i = 0; i < num - 1; i++) {
        while ((fscanf(ptr, "%c", &c) == 1) && (c != '\n')) {
        }
    }
    for (i = 0; i < size_col; i++) {
        if (fscanf(ptr, "%c", &array[i]) != 1) {
            return NULL;
        }
    }

    fclose(ptr);
    return array;

}

int find_size_word(const char *file_path) {
    if (file_path == NULL) {
        return 0;
    }
    FILE *ptr = fopen(file_path, "r");

    if (ptr == NULL) {
        return 0;
    }
    int i = 0;
    char c = 1;
    while (fscanf(ptr, "%c", &c) == 1) {
        if (c == '\n') {
            i++;
        }
    }
    i++;
    fclose(ptr);
    return i;

}

int find_size_col_word(const char *file_path, int num) {

    FILE *ptr = fopen(file_path, "r");

    if ((ptr == NULL) || (num < 0)) {
        return 0;
    }
    char c = 1;

    int i;

    for (i = 0; i < num - 1; i++) {
        while ((fscanf(ptr, "%c", &c) == 1) && (c != '\n')) {
        }
    }
    i = 0;

    while ((fscanf(ptr, "%c", &c) == 1) && (c != '\n')) {
        i++;
    }
    return i;
}

int word_place(char *file, char *word) {
    if ((file == NULL) || (word == NULL)) {
        return 0;
    }
    int sizefile = find_size(file);

    int sizeword = find_size(word);

    for (int i = 0; i < sizefile - sizeword; i++) {
        for (int j = 0; j < sizeword; j++) {
            if (word[j] == file[i + j]) {
                if (j == sizeword - 1) {
                    return i;
                }
            } else {
                break;
            }
        }
    }
    return 0;
}


