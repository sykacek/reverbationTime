#include <gtest/gtest.h>
#include <string.h>

#include "../src/inc/txt_file.h"
#define TEST_FILE "test/example_data.dat"

TEST(nameprotect, retwdot){
    std::string name = "hello.";
    std::string ret = txt::nameProtect(name);
    ASSERT_EQ(name, ret);
}

TEST(nameprotect, retndot){
    std::string name = "hello";
    std::string ret = txt::nameProtect(name);
    ASSERT_NE(name, ret);
}

TEST(arr_s, terminate_1){
    float arr[20] = {0};

    for(int i = 0; i < 15; i++)
        arr[i] = i + 0.25147;

    int len = txt::arr_s(arr);
    ASSERT_EQ(*(arr + len), 0);
}

TEST(arr_s, terminate_2){
    float arr[20] = {0};

    for(int i = 0; i < 15; i++)
        arr[i] = i + 0.25147;

    int len = txt::arr_s(arr);
    ASSERT_NE(arr[--len], 0);
}

TEST(file_len, ret){
    int ret = txt::fileLenght(TEST_FILE);
    float arr[CACHE_BUFFER_SIZE] = {0};

    txt::fileRead(TEST_FILE, arr);
    int len  = txt::arr_s(arr);

    ASSERT_EQ(ret, len);
}
TEST(file_line_len, ret){
    int ret = txt::fileLineLenght(TEST_FILE);
    float arr[CACHE_BUFFER_SIZE] = {0};

    txt::fileRead(TEST_FILE, arr);
    int len = txt::arr_s(arr);
    len /= 2;

    ASSERT_EQ(ret, len);
}

TEST(col_per_row, ret){
    std::fstream read(TEST_FILE, std::ios_base::in);
    std::string line = {0};
    EXPECT_TRUE(getline(read, line));
    read.close();

    int i = 0, j = 1;
    while(line[i]){
        if(line[i] == '\t')
            j++;
        i++;
    }

    int ret = txt::columnsInLine(TEST_FILE);
    ASSERT_EQ(ret, j);
}

TEST(file_read, size){
    /* when we are working with values with 6 signifivant digits
    one line of file takes up to 17 bytes (6 + 6 + 2 tabs + NL + 2 (signs))
    store values in 2 floats --> 8 bytes
    */
    float arr[CACHE_BUFFER_SIZE] = {0};
    txt::fileRead(TEST_FILE, arr);
    uint32_t memsize = sizeof(float) * txt::arr_s(arr);
    uint32_t filesize = std::filesystem::file_size(TEST_FILE);

    ASSERT_TRUE(memsize < filesize);
}




int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}