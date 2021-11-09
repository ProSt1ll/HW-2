#include <gtest/gtest.h>
#include "../libs/find_words_forked/include/find_words_forked.h"
#define FILE_PATH "../files/file.txt"
#define WORLD_PATH "../files/words.txt"
#include <ctime>

#define NUM_OF_TESTS 5

int main() {
    double timer = 0;
    const char* path = FILE_PATH;
    const char* word = WORLD_PATH;
    int words_size = find_size_word(word);
    int *ind = (int *) calloc(words_size,sizeof(int));

    for (size_t i = 0; i < NUM_OF_TESTS; i++) {
        clock_t begin = clock();
        ind = find_word_forked(path, word);
        clock_t end = clock();

        timer += (double) (end - begin) / CLOCKS_PER_SEC;

        free(ind);
    }
    double avg_time = timer / NUM_OF_TESTS;
    std::cout << "time: " << avg_time << std::endl;
    return 0;
}