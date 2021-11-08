#include "find_words_forked.h"
#include <string.h>


int *find_word_forked(const char *file_path, const char *file_word) {
    if (file_path == NULL) {
        return 0;
    }

    char *ptr = input_file(file_path, 1);
    if (ptr == NULL) {
        return NULL;
    }

    int words_size = find_size_word(file_word);
    int *ind = (int *) mmap(NULL, sizeof(int ) * words_size, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, 0,0);

    struct mymsgbuf {
        size_t mtype;
        size_t numb;
    };

    struct mymsgbuf qbuf = {1, 0};
    pid_t q_id = msgget(IPC_PRIVATE, IPC_CREAT | 0660);
    pid_t pid = fork();
    if (pid == 0) {
        for (size_t i = 0; i < words_size; ++i) {
            qbuf.numb = i;
            msgsnd(q_id, &qbuf, sizeof(size_t), 0);
        }
        exit(1);
    }

    size_t max_forks = sysconf(_SC_NPROCESSORS_ONLN);


    pid_t pids[max_forks];

    for (size_t k = 0; k < max_forks; ++k) {
        pids[k] = fork();
        if (pids[k] == 0) {
            while (msgrcv(q_id, &qbuf, sizeof(size_t), qbuf.mtype, IPC_NOWAIT) == sizeof(size_t)) {
                char *cur_word = input_words(file_word, qbuf.numb + 1);
                ind[qbuf.numb] = word_place(ptr, cur_word);
                free(cur_word);
            }
            exit(1);
        }
    }

    waitpid(pid, 0, 0);
    for (size_t k = 0; k < max_forks; ++k) {
        waitpid(pids[k], 0, 0);
    }
    msgctl(q_id, IPC_RMID, NULL);
    munmap(ptr, sizeof(char) * words_size);

    int *ret_ind = (int *) calloc(words_size, sizeof(int));

    for(size_t i = 0;i < words_size;i++){
        ret_ind[i] = ind[i];
    }
    munmap(ind, sizeof(int) * words_size);

    return ret_ind;
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

char *input_file(const char *file_path, int num) {
    if ((file_path == NULL) || (num < 1)) {
        return NULL;
    }
    FILE *ptr = fopen(file_path, "r");

    if (ptr == NULL) {
        return NULL;
    }
    size_t i;

    int size_col = find_size_col_word(file_path, num);


    char *array = (char *) mmap(NULL, sizeof(char) * size_col, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, 0,
                                0);

    if (array == NULL) {
        return NULL;
    }
    size_t size;
    for (i = 0; i < num - 1; i++) {
        if (fscanf(ptr, "%zu \n", &size) != 1) {
            fclose(ptr);
            return NULL;
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

