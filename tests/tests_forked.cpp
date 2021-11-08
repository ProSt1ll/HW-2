#include <gtest/gtest.h>

#include "../libs/find_words_forked/include/find_words_forked.h"
#include "../libs/find_words/include/find_words.h"
#define FILE_PATH "../files/file2.txt"
#define WORLD_PATH "../files/words2.txt"
#define ERROR_FILE_PATH "../files/error.txt"

TEST(test_data, test_data1) {
    const char* path = FILE_PATH;
    const char* word = WORLD_PATH;
    int words_size = find_size_word(word);
    int *ind = find_word_forked(path, word);

    for (int i = 0; i < words_size; i++){
        if (i > 2){
            EXPECT_TRUE(ind[i] == 0);
        } else{
            EXPECT_TRUE(ind[i] > 0 );
        }
    }
    free(ind);

}
TEST(test_eror_data, test_eror_data1){
    const char* word = ERROR_FILE_PATH;
    EXPECT_FALSE(find_size_word(word));
    EXPECT_FALSE(input_words(word,1));
    EXPECT_FALSE(find_size_col_word(word,1));
}
TEST(test_eror_data, test_eror_data2){
    const char* word = NULL;
    EXPECT_FALSE(find_size_word(word));
    EXPECT_FALSE(input_words(word,1));
    EXPECT_FALSE(find_size_col_word(word,1));
}
TEST(test_eror_data, test_eror_data3){
    char* word = NULL;
    EXPECT_FALSE(find_size(word));
    EXPECT_FALSE(word_place(word,word));
}
TEST(test_eror_data, test_eror_data4){
    const char* word = WORLD_PATH;
    EXPECT_FALSE(input_words(word,-2));
    EXPECT_FALSE(find_size_col_word(word,-2));
}





int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
