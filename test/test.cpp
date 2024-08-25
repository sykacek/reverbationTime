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

/* file to test write functions */
#define EXAMPLE_WRITE "../example_write.txt"

/* need more files to copying etc. */
#define EXAMPLE_COPY "../example_copy.txt"

/* file to match files with 2 columns */
#define EXAMPLE_MATCH2 "../write_match_col2.txt"

/* file to match files with one column */
#define EXAMPLE_MATCH1 "../write_match_col1.txt"

/* how many times repeat the tests*/
#define REPEAT 1000

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
    int ret = txt::file_len(EXAMPLE_LOG_SMALL);

    ASSERT_EQ(ret, EXAMPLE_LOG_SMALL_LINES * EXAMPLE_LOG_SMALL_COLS);
}

TEST(file_len, ret_big){
    int ret = txt::file_len(EXAMPLE_LIN_BIG);

    ASSERT_EQ(ret, EXAMPLE_LIN_BIG_COLS * EXAMPLE_LIN_BIG_LINES);
}

TEST(file_line_len, ret_small){
    int ret = txt::file_line_len(EXAMPLE_LOG_SMALL);

    ASSERT_EQ(ret, EXAMPLE_LOG_SMALL_LINES);
}

TEST(file_line_len, ret_big){
    int ret = txt::file_line_len(EXAMPLE_LIN_BIG);

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

    int ret = txt::col_per_row(EXAMPLE_LOG_SMALL);
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

/* Test length of wiritten file using already tested functions */
/* there will be an extra '\n' at the end of the file */
TEST(file_write, array_cells_lines){
    float arr[CACHE_BUFFER_SIZE] = {0};
    int len = 20;
    for(int i = 0; i < len; i++)
        arr[i] = i + 0.1254;

    EXPECT_TRUE(txt::fileWrite(EXAMPLE_WRITE, arr));
    int ret = txt::file_len(EXAMPLE_WRITE);
    int lines = txt::file_line_len(EXAMPLE_WRITE);

    ASSERT_EQ(lines, ret);
    ASSERT_EQ(len, ret);
}

TEST(file_write, two_array_cells_lines){
    float arr1[CACHE_BUFFER_SIZE] = {0}, arr2[CACHE_BUFFER_SIZE] = {0};
    int len = 15;

    for(int i = 0; i < len; ++i){
        arr1[i] = i + 0.15478;
        arr2[i] = 2*i + 0.12589;
    }

    EXPECT_TRUE(txt::fileWrite(EXAMPLE_WRITE, arr1, arr2));
    int ret = txt::file_len(EXAMPLE_WRITE);
    int lines = txt::file_line_len(EXAMPLE_WRITE);

    ASSERT_EQ(len, lines);
    ASSERT_EQ(ret, len * 2);
}

TEST(file_write, vector_cells_lines){
    std::vector<float> vect;
    int len = 30;
    for(int i = 0; i < len; ++i)
        vect.push_back(i + 0.1245);

    EXPECT_TRUE(txt::fileWrite(EXAMPLE_WRITE, vect));
    int ret = txt::file_len(EXAMPLE_WRITE);
    int lines = txt::file_line_len(EXAMPLE_WRITE);

    ASSERT_EQ(ret, lines);
    ASSERT_EQ(ret, len);
}

/* Compare contents of files using bash cmp command */
int cmp_files(char *file1, char *file2){
    char cmd[50] = "cmp";
    int i = 0;
    while(*(cmd + i))
        i++;

    cmd[i++] = ' ';
    char *p = file1;
    while(*p)
        cmd[i++] = *(p++);

    cmd[i++] = ' ';
    p = file2;
    while(*p)
        cmd[i++] = *(p++);

    return std::system(cmd);
}

TEST(file_write, array_contents){
    float arr[20] = {0};
    for(int i = 0; i < 10; ++i)
        arr[i] = i + 1;

    EXPECT_TRUE(txt::fileWrite(EXAMPLE_WRITE, arr));
    char written[] = EXAMPLE_WRITE;
    char match[] = EXAMPLE_MATCH1;

    ASSERT_EQ(cmp_files(written, match), 0);    
}

TEST(file_write, two_array_contents){
    float arr1[20] = {0}, arr2[10] = {0};
    for(int i = 0; i < 10; ++i){
        arr1[i] = i + 1;
        arr2[i] = i + 1;
    }

    EXPECT_TRUE(txt::fileWrite(EXAMPLE_WRITE, arr1, arr2));
    char written[] = EXAMPLE_WRITE;
    char match[] = EXAMPLE_MATCH2;

    ASSERT_EQ(cmp_files(written, match), 0);
}

TEST(file_write, vector_contents){
    std::vector<float> vect;
    for(int i = 0; i < 10; ++i)
        vect.push_back(i + 1);

    EXPECT_TRUE(txt::fileWrite(EXAMPLE_WRITE, vect));
    char written[] = EXAMPLE_WRITE;
    char match[] = EXAMPLE_MATCH1;
    
    ASSERT_EQ(cmp_files(written, match), 0);
}

TEST(file_write, two_vector_contents){
    std::vector<float> vect1, vect2;
    for(int i = 0; i < 10; ++i){
        vect1.push_back(i + 1);
        vect2.push_back(i + 1);
    }

    EXPECT_TRUE(txt::fileWrite(EXAMPLE_WRITE, vect1, vect2));
    char written[] = EXAMPLE_WRITE;
    char match[] = EXAMPLE_MATCH2;
    
    ASSERT_EQ(cmp_files(written, match), 0);
}

TEST(file_write, two_array_diff_size){
    float arr1[CACHE_BUFFER_SIZE] = {0}, arr2[CACHE_BUFFER_SIZE] = {0};
    for(int i = 0; i < 10; ++i)
        arr1[i] = i + 1;
    for(int i = 0; i < 15; ++i)
        arr2[i] = i + 1;

    EXPECT_TRUE(txt::fileWrite(EXAMPLE_WRITE, arr1, arr2));
    char written[] = EXAMPLE_WRITE;
    char match[] = EXAMPLE_MATCH2;
    
    ASSERT_EQ(cmp_files(written, match), 0);
}

TEST(file_write, two_vector_diff_size){
    std::vector<float> vect1, vect2;
    for(int i = 0; i < 10; ++i)
        vect1.push_back(i + 1);
    for(int i = 0; i < 15; ++i)
        vect2.push_back(i + 1);
    EXPECT_TRUE(txt::fileWrite(EXAMPLE_WRITE, vect1, vect2));
    char written[] = EXAMPLE_WRITE;
    char match[] = EXAMPLE_MATCH2;
    
    ASSERT_EQ(cmp_files(written, match), 0);
}

TEST(file_append_line, contents){
    float arr[CACHE_BUFFER_SIZE] = {0};
    int len = 1000;
    for(int i = 0; i < len; ++i)
        arr[i] = i + 1;
    /* clear file */
    std::fstream read(EXAMPLE_WRITE, std::ios_base::out);
    read.clear();
    read.close();

    EXPECT_TRUE(txt::fileAppendLine(EXAMPLE_WRITE, arr));
    float read_arr[CACHE_BUFFER_SIZE] = {0};
    txt::fileRead(EXAMPLE_WRITE, read_arr);
    int read_len = txt::arr_s(read_arr);

    ASSERT_EQ(len, read_len);
    for(int i = 0; i < len; ++i)
        ASSERT_EQ(arr[i], read_arr[i]);
}

TEST(file_append_line, lines){
    float arr[CACHE_BUFFER_SIZE] = {0};
    int len = 1000;
    for(int i = 0; i < len; ++i)
        arr[i] = i + 1;
    /* clear file */
    std::fstream read(EXAMPLE_WRITE, std::ios_base::out);
    read.clear();
    read.close();

    EXPECT_TRUE(txt::fileAppendLine(EXAMPLE_WRITE, arr));
    int ret = txt::file_line_len(EXAMPLE_WRITE);

    ASSERT_EQ(ret, len);
}

TEST(file_append_line, columns){
    float arr[CACHE_BUFFER_SIZE] = {0};
    int len = 1000;
    for(int i = 0; i < len; ++i)
        arr[i] = i + 1;
    /* clear file */
    std::fstream read(EXAMPLE_WRITE, std::ios_base::out);
    read.clear();
    read.close();

    EXPECT_TRUE(txt::fileAppendLine(EXAMPLE_WRITE, arr));
    int ret = txt::col_per_row(EXAMPLE_WRITE);

    ASSERT_EQ(ret, 1);
}

TEST(file_append_tab, lines){
    float arr[CACHE_BUFFER_SIZE] = {0};
    int len = 1000;
    for(int i = 0; i < len; ++i)
        arr[i] = i + 1;
    /* clear file */
    std::fstream read(EXAMPLE_WRITE, std::ios_base::out);
    read.clear();
    read.close();

    EXPECT_TRUE(txt::fileAppendTab(EXAMPLE_WRITE, arr));
    int ret = txt::file_line_len(EXAMPLE_WRITE);

    ASSERT_EQ(ret, 1);
}

TEST(file_append_tab, columns){
    float arr[CACHE_BUFFER_SIZE] = {0};
    int len = 14512;
    for(int i = 0; i < len; ++i)
        arr[i] = i + 1;
    /* clear file */
    std::fstream read(EXAMPLE_WRITE, std::ios_base::out);
    read.clear();
    read.close();

    EXPECT_TRUE(txt::fileAppendTab(EXAMPLE_WRITE, arr));
    int ret = txt::col_per_row(EXAMPLE_WRITE);

    ASSERT_EQ(ret, len);
}

TEST(file_append_tab, contents){
    float arr[CACHE_BUFFER_SIZE] = {0};
    int len = 1000;
    for(int i = 0; i < len; ++i)
        arr[i] = i + 1;
    /* clear file */
    std::fstream read(EXAMPLE_WRITE, std::ios_base::out);
    read.clear();
    read.close();

    EXPECT_TRUE(txt::fileAppendTab(EXAMPLE_WRITE, arr));
    float read_arr[CACHE_BUFFER_SIZE] = {0};

    txt::fileRead(EXAMPLE_WRITE, read_arr);
    int read_len = txt::arr_s(read_arr);

    ASSERT_EQ(read_len, len);

    for(int i = 0; i < len; ++i)
        ASSERT_EQ(arr[i], read_arr[i]);    
}


/* fix aproximation to be cols independent!!!!*/
TEST(file_aproximate, lines){
    float arr[CACHE_BUFFER_SIZE] = {0};
    int len = 10000;
    for(int i = 0; i < len; ++i)
        arr[i] = i + 1;

    EXPECT_TRUE(txt::fileWrite(EXAMPLE_WRITE, arr));
    int ret = txt::file_line_len(EXAMPLE_WRITE);

    EXPECT_EQ(len, ret);
    int factor = 10;

    EXPECT_TRUE(txt::fileAproximation(EXAMPLE_WRITE, EXAMPLE_COPY, factor));
    ret /= factor;
    int apx_ret = txt::file_line_len(EXAMPLE_COPY);

    ASSERT_EQ(ret, apx_ret);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}