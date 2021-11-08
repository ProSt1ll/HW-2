#include <gtest/gtest.h>
#include "find_words.h"
#define FILE_PATH "../files/file.txt"
#define WORLD_PATH "../files/words.txt"
#include <ctime>

#define NUM_OF_TESTS 5

int main() {
    double timer = 0;

    for (size_t i = 0; i < NUM_OF_TESTS; i++) {
        const char* path = FILE_PATH;
        const char* word = WORLD_PATH;
        clock_t begin = clock();
        int *ind = find_word(path, word);
        clock_t end = clock();

        timer += (double) (end - begin) / CLOCKS_PER_SEC;

        free(ind);
    }
    double avg_time = timer / NUM_OF_TESTS;
    std::cout << "average time: " << avg_time << std::endl;
    return 0;
}