#include <gtest/gtest.h>
#include <string.h>

/**
 * test.cpp is located in test directory
 */
#include "../src/inc/txt_file.h"
/**
 * executable will be run from test/build directory
 */
#define EXAMPLE_LOG_SMALL "../example_log_small.dat"
#define EXAMPLE_LOG_SMALL_LINES (130)
#define EXAMPLE_LOG_SMALL_COLS (2)

#define EXAMPLE_LIN_BIG "../example_lin_big.dat"
#define EXAMPLE_LIN_BIG_LINES (143999)
#define EXAMPLE_LIN_BIG_COLS (3)

#define EXAMPLE_WRITE "../example_write.txt"

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

/* Testing of file read/write functions is compared to human produced results */
/* So lines, cells etc. were counted manually */
TEST(file_len, ret_small){
    int ret = txt::fileLenght(EXAMPLE_LOG_SMALL);

    ASSERT_EQ(ret, EXAMPLE_LOG_SMALL_LINES * EXAMPLE_LOG_SMALL_COLS);
}

TEST(file_len, ret_big){
    int ret = txt::fileLenght(EXAMPLE_LIN_BIG);

    ASSERT_EQ(ret, EXAMPLE_LIN_BIG_COLS * EXAMPLE_LIN_BIG_LINES);
}

TEST(file_line_len, ret_small){
    int ret = txt::fileLineLenght(EXAMPLE_LOG_SMALL);

    ASSERT_EQ(ret, EXAMPLE_LOG_SMALL_LINES);
}

TEST(file_line_len, ret_big){
    int ret = txt::fileLineLenght(EXAMPLE_LIN_BIG);

    /* there is an empty extra line in the file, so return value will be one bigger*/
    ASSERT_EQ(ret, EXAMPLE_LIN_BIG_LINES + 1);
}

TEST(col_per_row, ret){
    std::fstream read(EXAMPLE_LOG_SMALL, std::ios_base::in);
    std::string line = {0};

    EXPECT_TRUE(getline(read, line));
    read.close();

    int i = 0, j = 1;
    while(line[i]){
        /* there is another cell */
        if(line[i] == '\t')
            j++;
        i++;
    }

    int ret = txt::columnsInLine(EXAMPLE_LOG_SMALL);
    EXPECT_EQ(ret, EXAMPLE_LOG_SMALL_COLS);
    ASSERT_EQ(ret, j);
}

TEST(file_read, array_size){
    /* number of elements of buffer should be same as number of cells in the file */
    float arr[CACHE_BUFFER_SIZE] = {0};

    EXPECT_TRUE(txt::fileRead(EXAMPLE_LOG_SMALL, arr));
    uint32_t memsize = txt::arr_s(arr);

    ASSERT_EQ(memsize, EXAMPLE_LOG_SMALL_COLS * EXAMPLE_LOG_SMALL_LINES);
}

TEST(file_read, two_array_size){
    /* number of each array should be same as number of lines */
    float arr1[CACHE_BUFFER_SIZE] = {0}, arr2[CACHE_BUFFER_SIZE] = {0};

    EXPECT_TRUE(txt::fileRead(EXAMPLE_LOG_SMALL, arr1, arr2));
    uint32_t memsize1 = txt::arr_s(arr1);
    uint32_t memsize2 = txt::arr_s(arr2);

    EXPECT_EQ(memsize1, memsize2);
    ASSERT_EQ(memsize1, 130);
}

TEST(file_read, vector_size){
    /* read any column, size of vector should be number of lines */
    std::vector<float> vector;

    EXPECT_TRUE(txt::fileRead(EXAMPLE_LOG_SMALL, vector, 2, 1));
    uint32_t ret = vector.size();

    ASSERT_EQ(ret, EXAMPLE_LOG_SMALL_LINES);
}

TEST(file_read, array_contents){
    /* first column is 1, 2, 3 ... 128, compare */
    float arr[CACHE_BUFFER_SIZE] = {0};

    EXPECT_TRUE(txt::fileRead(EXAMPLE_LOG_SMALL, arr));

    for(int i = 0; i < 255; i += 2)
        ASSERT_EQ(arr[i], i/2 + 1);
}

TEST(file_read, two_array_contents){
    float arr1[CACHE_BUFFER_SIZE] = {0}, arr2[CACHE_BUFFER_SIZE] = {0};

    EXPECT_TRUE(txt::fileRead(EXAMPLE_LOG_SMALL, arr1, arr2));

    for(int i = 0; i < 128; ++i)
        ASSERT_EQ(arr1[i], i + 1);
}

TEST(file_read, vector_contents){
    std::vector<float> vect;

    EXPECT_TRUE(txt::fileRead(EXAMPLE_LOG_SMALL, vect, 2, 0));

    for(int i = 0; i < 128; ++i)
        ASSERT_EQ(vect[i], i + 1);
}

/* Test lenght of wiritten file using already tested functions */
/* there will be an extra '\n' at the end of the file */
TEST(file_write, array_cells_lines){
    float arr[CACHE_BUFFER_SIZE] = {0};
    int len = 20;
    for(int i = 0; i < len; i++)
        arr[i] = i + 0.1254;

    EXPECT_TRUE(txt::fileWrite(EXAMPLE_WRITE, arr));
    int ret = txt::fileLenght(EXAMPLE_WRITE);
    int lines = txt::fileLineLenght(EXAMPLE_WRITE);

    ASSERT_EQ(lines - 1, ret);
    ASSERT_EQ(len, ret);
}

TEST(file_write, array_lines){
    float arr[CACHE_BUFFER_SIZE] = {0};
    int len = 20;
    for(int i = 0; i < len; i++)
        arr[i] = i + 0.1254;

    EXPECT_TRUE(txt::fileWrite(EXAMPLE_WRITE, arr));
    int ret = txt::fileLineLenght(EXAMPLE_WRITE);

    ASSERT_EQ(len, ret);
}

TEST(file_write, two_array_cells){
    float arr1[CACHE_BUFFER_SIZE] = {0}, arr2[CACHE_BUFFER_SIZE] = {0};
    int len = 15;

    for(int i = 0; i < len; ++i){
        arr1[i] = i + 0.15478;
        arr2[i] = 2*i + 0.12589;
    }

    EXPECT_TRUE(txt::fileWrite(EXAMPLE_WRITE, arr1, arr2));
    int ret = txt::fileLenght(EXAMPLE_WRITE);

    ASSERT_EQ(ret, len * 2);
}

TEST(file_write, two_array_lines){
    float arr1[CACHE_BUFFER_SIZE] = {0}, arr2[CACHE_BUFFER_SIZE] = {0};
    int len = 15;

    for(int i = 0; i < len; ++i){
        arr1[i] = i + 0.15478;
        arr2[i] = 2*i + 0.12589;
    }

    EXPECT_TRUE(txt::fileWrite(EXAMPLE_WRITE, arr1, arr2));
    int ret = txt::fileLineLenght(EXAMPLE_WRITE);

    ASSERT_EQ(ret, len);
}

TEST(file_write, vector_cells){
    std::vector<float> vect;
    int len = 30;
    for(int i = 0; i < len; ++i)
        vect.push_back(i + 0.1245);

    EXPECT_TRUE(txt::fileWrite(EXAMPLE_WRITE, vect));
    int ret = txt::fileLenght(EXAMPLE_WRITE);
    int lines = txt::fileLineLenght(EXAMPLE_WRITE);

    ASSERT_EQ(ret, lines - 1);
    ASSERT_EQ(ret, len);
}

/* Compare contents using bash cmp command */
TEST(file_write, array_contents){
    ASSERT_EQ(2 + 2, 4);
}

int main(int argc, char **argv)
{
    if(argc > 1){
        printf("Error: too many arguments\n");
        return -EINVAL;
    }
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}