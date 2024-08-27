#include <gtest/gtest.h>
#include <string.h>
#include <unistd.h>

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

#ifndef REPEAT
/* how many times repeat the tests*/
#define REPEAT 10
#endif

#define MAX_ARRAY_RAND 50000

 /* random rounded non zero double number */
 /* also not equal exactly one - log10(1) = 0 */
#define RAND_DOUBLE (ceilf((double)std::rand()/(std::rand()) * 1000)/1000 + 1.12)
#define ROUND_DIFF (0.5)

#define ASSERT_PREC(a, b) ASSERT_NEAR(a, b, ROUND_DIFF)

TEST(nameprotect, ret_with_dot){
    std::string name = "hello.";
    std::string ret = txt::nameProtect(name);
    ASSERT_EQ(name, ret);
}

TEST(nameprotect, ret_without_dot){
    std::string name = "hello";
    std::string ret = txt::nameProtect(name);
    ASSERT_NE(name, ret);
}

TEST(array_size, size_and_terminate){
    /* we need maximum of MAX_ARRAY_RAND numbers to be stored */
    double arr[MAX_ARRAY_RAND] = {0};

    int size;
    for(int j = 0; j < REPEAT; ++j){
        memset(arr, 0, MAX_ARRAY_RAND * sizeof(double));
        size = std::rand() % MAX_ARRAY_RAND;
        for(int i = 0; i < size; i++)
            arr[i] = RAND_DOUBLE;

        uint32_t len = txt::arraySize(arr);
        ASSERT_EQ(len, size);
        ASSERT_EQ(*(arr + len), 0);
        ASSERT_NE(arr[--len], 0);
    }
}

/* Testing of file read/write functions is compared to human produced results, */
/* lines, cells etc. were counted manually */
TEST(fileLen, ret_small){
    int ret = txt::fileLen(EXAMPLE_LOG_SMALL);

    ASSERT_EQ(ret, EXAMPLE_LOG_SMALL_LINES * EXAMPLE_LOG_SMALL_COLS);
}

TEST(fileLen, ret_big){
    int ret = txt::fileLen(EXAMPLE_LIN_BIG);

    ASSERT_EQ(ret, EXAMPLE_LIN_BIG_COLS * EXAMPLE_LIN_BIG_LINES);
}

TEST(fileLineLen, ret_small){
    int ret = txt::fileLineLen(EXAMPLE_LOG_SMALL);

    ASSERT_EQ(ret, EXAMPLE_LOG_SMALL_LINES);
}

TEST(fileLineLen, ret_big){
    int ret = txt::fileLineLen(EXAMPLE_LIN_BIG);

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

    int ret = txt::colsPerRow(EXAMPLE_LOG_SMALL);
    EXPECT_EQ(ret, EXAMPLE_LOG_SMALL_COLS);
    ASSERT_EQ(ret, j);
}

TEST(file_read, array_size){
    /* number of elements of buffer should be same as number of cells in the file */
    double arr[MAX_ARRAY_RAND] = {0};

    EXPECT_TRUE(txt::fileRead(EXAMPLE_LOG_SMALL, arr));
    uint32_t memsize = txt::arraySize(arr);

    ASSERT_EQ(memsize, EXAMPLE_LOG_SMALL_COLS * EXAMPLE_LOG_SMALL_LINES);
}

TEST(file_read, two_array_size){
    /* number of each array should be same as number of lines */
    double arr1[MAX_ARRAY_RAND] = {0}, arr2[MAX_ARRAY_RAND] = {0};

    EXPECT_TRUE(txt::fileRead(EXAMPLE_LOG_SMALL, arr1, arr2));
    uint32_t memsize1 = txt::arraySize(arr1);
    uint32_t memsize2 = txt::arraySize(arr2);

    EXPECT_EQ(memsize1, memsize2);
    ASSERT_EQ(memsize1, 130);
}

TEST(file_read, vector_size){
    /* read any column, size of vector should be number of lines */
    std::vector<double> vector;

    EXPECT_TRUE(txt::fileRead(EXAMPLE_LOG_SMALL, vector, 2, 1));
    uint32_t ret = vector.size();

    ASSERT_EQ(ret, EXAMPLE_LOG_SMALL_LINES);
}

TEST(file_read, array_contents){
    /* first column is 1, 2, 3 ... 128, compare */
    double arr[MAX_ARRAY_RAND] = {0};

    EXPECT_TRUE(txt::fileRead(EXAMPLE_LOG_SMALL, arr));

    for(int i = 0; i < 255; i += 2)
        ASSERT_EQ(arr[i], i/2 + 1);
}

TEST(file_read, two_array_contents){
    double arr1[MAX_ARRAY_RAND] = {0}, arr2[MAX_ARRAY_RAND] = {0};

    EXPECT_TRUE(txt::fileRead(EXAMPLE_LOG_SMALL, arr1, arr2));

    for(int i = 0; i < 128; ++i)
        ASSERT_EQ(arr1[i], i + 1);
}

TEST(file_read, vector_contents){
    std::vector<double> vect;

    EXPECT_TRUE(txt::fileRead(EXAMPLE_LOG_SMALL, vect, 2, 0));

    for(int i = 0; i < 128; ++i)
        ASSERT_EQ(vect[i], i + 1);
}

/* Test length of wiritten file using already tested functions */
/* there will be an extra '\n' at the end of the file */
TEST(file_write, array_cells_lines){
    double arr[MAX_ARRAY_RAND] = {0};
    int len;
    for(int j = 0; j < REPEAT; ++j){
        memset(arr, 0, MAX_ARRAY_RAND * sizeof(double));
        len = std::rand() % MAX_ARRAY_RAND;

        for(int i = 0; i < len; i++)
            arr[i] = RAND_DOUBLE;

        EXPECT_TRUE(txt::fileWrite(EXAMPLE_WRITE, arr));
        int ret = txt::fileLen(EXAMPLE_WRITE);
        int lines = txt::fileLineLen(EXAMPLE_WRITE);

        ASSERT_EQ(lines, ret);
        ASSERT_EQ(len, ret);
    }
}

char wr[] = EXAMPLE_WRITE;

TEST(file_write, two_array_cells_lines){
    double arr1[MAX_ARRAY_RAND] = {0}, arr2[MAX_ARRAY_RAND] = {0};
    int len;

    for(int j = 0; j < REPEAT; ++j){
        memset(arr1, 0, MAX_ARRAY_RAND * sizeof(double));
        memset(arr2, 0, MAX_ARRAY_RAND * sizeof(double));
        len = std::rand() % MAX_ARRAY_RAND;

        for(int i = 0; i < len; ++i){
            arr1[i] = RAND_DOUBLE;
            arr2[i] = RAND_DOUBLE;
        }

        EXPECT_TRUE(txt::fileWrite(EXAMPLE_WRITE, arr1, arr2));
        //usleep(100);
        int ret = txt::fileLen(EXAMPLE_WRITE);
        int lines = txt::fileLineLen(EXAMPLE_WRITE);

        ASSERT_EQ(len, lines);
        ASSERT_EQ(ret, len * 2);
    }
}

TEST(file_write, vector_cells_lines){
    std::vector<double> vect;
    int len;

    for(int j = 0; j < REPEAT; ++j){
        vect.clear();
        len = std::rand() % MAX_ARRAY_RAND;
     
        for(int i = 0; i < len; ++i)
            vect.push_back(i + 0.1245);

        EXPECT_TRUE(txt::fileWrite(EXAMPLE_WRITE, vect));
        int ret = txt::fileLen(EXAMPLE_WRITE);
        int lines = txt::fileLineLen(EXAMPLE_WRITE);

        ASSERT_EQ(ret, lines);
        ASSERT_EQ(ret, len);
    }
}

TEST(file_write, two_vector_cells_lines){
    std::vector<double> vect1, vect2;
    int len;

    for(int j = 0; j < REPEAT; ++j){
        vect1.clear();
        vect2.clear();
        len = std::rand() % MAX_ARRAY_RAND;

        for(int i = 0; i < len; ++i){
            vect1.push_back(i + 0.12172);
            vect2.push_back(i + 0.1778);
        }

        EXPECT_TRUE(txt::fileWrite(EXAMPLE_WRITE, vect1, vect2));
        int ret = txt::fileLen(EXAMPLE_WRITE);
        int lines = txt::fileLineLen(EXAMPLE_WRITE);

        ASSERT_EQ(len, lines);
        ASSERT_EQ(ret, lines * 2);
    }
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

TEST(file_write, array_match){
    double arr[20] = {0};
    for(int i = 0; i < 10; ++i)
        arr[i] = i + 1;

    EXPECT_TRUE(txt::fileWrite(EXAMPLE_WRITE, arr));
    char written[] = EXAMPLE_WRITE;
    char match[] = EXAMPLE_MATCH1;

    ASSERT_EQ(cmp_files(written, match), 0);    
}

TEST(file_write, two_array_match){
    double arr1[20] = {0}, arr2[10] = {0};
    for(int i = 0; i < 10; ++i){
        arr1[i] = i + 1;
        arr2[i] = i + 1;
    }

    EXPECT_TRUE(txt::fileWrite(EXAMPLE_WRITE, arr1, arr2));
    char written[] = EXAMPLE_WRITE;
    char match[] = EXAMPLE_MATCH2;

    ASSERT_EQ(cmp_files(written, match), 0);
}

TEST(file_write, vector_match){
    std::vector<double> vect;
    for(int i = 0; i < 10; ++i)
        vect.push_back(i + 1);

    EXPECT_TRUE(txt::fileWrite(EXAMPLE_WRITE, vect));
    char written[] = EXAMPLE_WRITE;
    char match[] = EXAMPLE_MATCH1;
    
    ASSERT_EQ(cmp_files(written, match), 0);
}

TEST(file_write, two_vector_match){
    std::vector<double> vect1, vect2;
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
    double arr1[MAX_ARRAY_RAND] = {0}, arr2[MAX_ARRAY_RAND] = {0};
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
    std::vector<double> vect1, vect2;
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
    double arr[MAX_ARRAY_RAND] = {0}, read_arr[MAX_ARRAY_RAND] = {0};
    int len;

    for(int j = 0; j < REPEAT; ++j){
        memset(arr, 0, MAX_ARRAY_RAND * sizeof(double));
        memset(read_arr, 0, MAX_ARRAY_RAND * sizeof(double));
        len = std::rand() % MAX_ARRAY_RAND;

        for(int i = 0; i < len; ++i)
            arr[i] = RAND_DOUBLE;
        /* clear file */
        std::fstream read(EXAMPLE_WRITE, std::ios_base::out);
        read.clear();
        read.close();

        EXPECT_TRUE(txt::fileAppendLine(EXAMPLE_WRITE, arr));
        txt::fileRead(EXAMPLE_WRITE, read_arr);
        int read_len = txt::arraySize(read_arr);

        ASSERT_EQ(len, read_len);
        for(int i = 0; i < len; ++i)
            ASSERT_PREC(arr[i], read_arr[i]);
    }
}

TEST(file_append_line, lines){
    double arr[MAX_ARRAY_RAND] = {0};
    int len;

    for(int j = 0; j < REPEAT; ++j){
        memset(arr, 0, MAX_ARRAY_RAND * sizeof(double));
        len = std::rand() % MAX_ARRAY_RAND;

        for(int i = 0; i < len; ++i)
            arr[i] = RAND_DOUBLE;
        /* clear file */
        std::fstream read(EXAMPLE_WRITE, std::ios_base::out);
        read.clear();
        read.close();

        EXPECT_TRUE(txt::fileAppendLine(EXAMPLE_WRITE, arr));
        int ret = txt::fileLineLen(EXAMPLE_WRITE);

        ASSERT_EQ(ret, len);
    }    
}

TEST(file_append_line, columns){
    double arr[MAX_ARRAY_RAND] = {0};
    int len = 1000;
    
    for(int j = 0; j < REPEAT; ++j){
        memset(arr, 0, MAX_ARRAY_RAND * sizeof(double));
        len = std::rand() % MAX_ARRAY_RAND;

        for(int i = 0; i < len; ++i)
            arr[i] = RAND_DOUBLE;
        /* clear file */
        std::fstream read(EXAMPLE_WRITE, std::ios_base::out);
        read.clear();
        read.close();

        EXPECT_TRUE(txt::fileAppendLine(EXAMPLE_WRITE, arr));
        int ret = txt::colsPerRow(EXAMPLE_WRITE);

        ASSERT_EQ(ret, 1);
    }
}

TEST(file_append_tab, lines){
    double arr[MAX_ARRAY_RAND] = {0};
    int len;

    for(int j = 0; j < REPEAT; ++j){
        memset(arr, 0, MAX_ARRAY_RAND * sizeof(double));
        len = std::rand() % MAX_ARRAY_RAND;

        for(int i = 0; i < len; ++i)
            arr[i] = RAND_DOUBLE;
        /* clear file */
        std::fstream read(EXAMPLE_WRITE, std::ios_base::out);
        read.clear();
        read.close();

        EXPECT_TRUE(txt::fileAppendTab(EXAMPLE_WRITE, arr));
        int ret = txt::fileLineLen(EXAMPLE_WRITE);

        ASSERT_EQ(ret, 1);
    }
}

TEST(file_append_tab, columns){
    double arr[MAX_ARRAY_RAND] = {0};
    int len;

    for(int j = 0; j < REPEAT; ++j){
        memset(arr, 0, MAX_ARRAY_RAND * sizeof(double));
        len = std::rand() % MAX_ARRAY_RAND;

        for(int i = 0; i < len; ++i)
            arr[i] = RAND_DOUBLE;
        /* clear file */
        std::fstream read(EXAMPLE_WRITE, std::ios_base::out);
        read.clear();
        read.close();

        EXPECT_TRUE(txt::fileAppendTab(EXAMPLE_WRITE, arr));
        int ret = txt::colsPerRow(EXAMPLE_WRITE);

        ASSERT_EQ(ret, len);
    }
}
TEST(file_append_tab, contents){
    double arr[MAX_ARRAY_RAND] = {0};
    int len;

    for(int j = 0; j < REPEAT; ++j){
        memset(arr, 0, MAX_ARRAY_RAND * sizeof(double));
        len = std::rand() % MAX_ARRAY_RAND;

        for(int i = 0; i < len; ++i)
            arr[i] = RAND_DOUBLE;
        /* clear file */
        std::fstream read(EXAMPLE_WRITE, std::ios_base::out);
        read.clear();
        read.close();

        EXPECT_TRUE(txt::fileAppendTab(EXAMPLE_WRITE, arr));
        double read_arr[MAX_ARRAY_RAND] = {0};

        txt::fileRead(EXAMPLE_WRITE, read_arr);
        int read_len = txt::arraySize(read_arr);

        ASSERT_EQ(read_len, len);

        for(int i = 0; i < len; ++i)
            ASSERT_PREC(arr[i], read_arr[i]);
    }
}

TEST(file_aproximate, lines_col){
    double arr1[MAX_ARRAY_RAND] = {0}, arr2[MAX_ARRAY_RAND] = {0};
    int len, cols;

    for(int j = 0; j < REPEAT; ++j){
        memset(arr1, 0, MAX_ARRAY_RAND * sizeof(double));
        memset(arr2, 0, MAX_ARRAY_RAND * sizeof(double));
        len = std::rand() % MAX_ARRAY_RAND;

        /* test */
        if(len % 2){
            cols = 1;
            for(int i = 0; i < len; ++i)
                arr1[i] = RAND_DOUBLE;

            EXPECT_TRUE(txt::fileWrite(EXAMPLE_WRITE, arr1));
        } else {
            cols = 2;
            for(int i = 0; i < len; ++i){
                arr1[i] = RAND_DOUBLE;
                arr2[i] = RAND_DOUBLE;
            }

            EXPECT_TRUE(txt::fileWrite(EXAMPLE_WRITE, arr1, arr2));
        }
        int ret = txt::fileLineLen(EXAMPLE_WRITE);

        EXPECT_EQ(len, ret);
        int factor = 10;

        EXPECT_TRUE(txt::fileAproximation(EXAMPLE_WRITE, EXAMPLE_COPY, factor));
        ret /= factor;
        int apx_lines = txt::fileLineLen(EXAMPLE_COPY);
        int apx_cols = txt::colsPerRow(EXAMPLE_COPY);

        ASSERT_EQ(apx_cols, cols);
        ASSERT_EQ(ret, apx_lines);
    }
}

TEST(log_value, values){
    std::vector<double> vect, check;
    int len = 0;

    for(int j = 0; j < REPEAT; ++j){
        vect.clear();
        check.clear();
        len = std::rand() % MAX_ARRAY_RAND;

        for(int i = 0; i < len; ++i){
            vect.push_back(RAND_DOUBLE);
            check.push_back(vect[i]);
        }

        EXPECT_TRUE(txt::logValue(vect));

        ASSERT_EQ(vect.size(), check.size());
        for(int i = 0; i < len; ++i)
            ASSERT_PREC(vect[i], 20*log10(check[i]));
    }
}

TEST(file_clear, cells_lines_cols){
    double arr[MAX_ARRAY_RAND] = {0};
    int len = 0;

    for(int j = 0; j < REPEAT; ++j){
        memset(arr, 0, MAX_ARRAY_RAND * sizeof(double));
        len = std::rand() % MAX_ARRAY_RAND;
        for(int i = 0; i < len; ++i)
            arr[i] = static_cast <double> (rand() / static_cast <double> (RAND_MAX)) + 1;
        EXPECT_TRUE(txt::fileWrite(EXAMPLE_WRITE, arr));
        EXPECT_TRUE(txt::fileClear(EXAMPLE_WRITE));
        int cells = txt::fileLen(EXAMPLE_WRITE);
        int lines = txt::fileLineLen(EXAMPLE_WRITE);
        int cols = txt::colsPerRow(EXAMPLE_WRITE);

        ASSERT_EQ(cells, 0);
        /* there will always be one line */
        ASSERT_EQ(lines, 1);
        ASSERT_EQ(cols, 0);
    }
}

TEST(file_copy, contents_and_format){
    double arr[4][MAX_ARRAY_RAND] = {0};
    int len, cols;

    for(int j = 0; j < REPEAT; ++j){
        for(int i = 0; i < 4; ++i)
            memset(arr[i], 0, MAX_ARRAY_RAND * sizeof(double));
        len = std::rand() % MAX_ARRAY_RAND;

        if(len % 2){
            cols = 2;
            for(int i = 0; i < len; ++i){
                arr[0][i] = RAND_DOUBLE;
                arr[1][i] = RAND_DOUBLE;
            }
            
            EXPECT_TRUE(txt::fileWrite(EXAMPLE_WRITE, arr[0], arr[1]));
        } else {
            cols = 1;
            for(int i = 0; i < len; ++i)
                arr[0][i] = RAND_DOUBLE;
            
            EXPECT_TRUE(txt::fileWrite(EXAMPLE_WRITE, arr[0]));
        }

        EXPECT_TRUE(txt::fileCopy(EXAMPLE_WRITE, EXAMPLE_COPY, 2));

        int lines = txt::fileLineLen(EXAMPLE_COPY);
        int cols_ret = txt::colsPerRow(EXAMPLE_COPY);

        ASSERT_EQ(cols_ret, cols);
        ASSERT_EQ(lines, len);

        if(cols == 2){
            EXPECT_TRUE(txt::fileRead(EXAMPLE_COPY, arr[2], arr[3]));
            int size1 = txt::arraySize(arr[2]);
            int size2 = txt::arraySize(arr[3]);

            ASSERT_EQ(size1, size2);
            ASSERT_EQ(size1, len);

            for(int i = 0; i < len; ++i){
                /* they may not be really same, because of */
                ASSERT_PREC(arr[0][i], arr[2][i]) << i << "\n";
                ASSERT_PREC(arr[1][i], arr[3][i]) << i << "\n";
            }
        } else {
            EXPECT_TRUE(txt::fileRead(EXAMPLE_COPY, arr[1]));
            int size = txt::arraySize(arr[1]);

            ASSERT_EQ(size, len);

            for(int i = 0; i < len; ++i)
                ASSERT_PREC(arr[1][i], arr[0][i]) << i << "\n";
        }
    }
}

TEST(file_log_copy, format_and_contents){
    double arr[4][MAX_ARRAY_RAND] = {0};
    int len;

    for(int j = 0; j < REPEAT; ++j){
        for(int i = 0; i < 4; ++i)
            memset(arr[i], 0, MAX_ARRAY_RAND * sizeof(double));
        len = std::rand() % MAX_ARRAY_RAND;

        for(int i = 0; i < len; ++i){
            arr[0][i] = RAND_DOUBLE;
            arr[1][i] = RAND_DOUBLE;
        }
        
        EXPECT_TRUE(txt::fileWrite(EXAMPLE_WRITE, arr[0], arr[1]));


        EXPECT_TRUE(txt::fileLogCopy(EXAMPLE_WRITE, EXAMPLE_COPY));
        int lines = txt::fileLineLen(EXAMPLE_COPY);
        int read_cols = txt::colsPerRow(EXAMPLE_COPY);

        ASSERT_EQ(lines, len);
        ASSERT_EQ(read_cols, 2);

        EXPECT_TRUE(txt::fileRead(EXAMPLE_COPY, arr[2], arr[3]));
        int size[2];
        size[0] = txt::arraySize(arr[2]);
        size[1] = txt::arraySize(arr[3]);

        ASSERT_EQ(size[0], size[1]);
        ASSERT_EQ(size[0], len);

        for(int i = 0; i < len; ++i){
            ASSERT_PREC(arr[0][i], arr[2][i]);
            ASSERT_PREC(20*log10(arr[1][i]), arr[3][i]);
        }
        
    }
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}