#include <gtest/gtest.h>
#include <string.h>

#include "../src/inc/txt_file.h"

TEST(nameprotect, retwdot){
    std::string name = "hello.";
    std::string ret = txt_file::nameProtect(name);
    ASSERT_EQ(name, ret);
}

TEST(nameprotect, retndot){
    std::string name = "hello";
    std::string ret = txt_file::nameProtect(name);
    ASSERT_NE(name, ret);
}

TEST(arr_s, terminate_1){
    double arr[20];
    memset(arr, 0, sizeof(double) * 20);
    for(int i = 0; i < 15; i++)
        arr[i] = i + 0.25147;

    int len = txt_file::arr_s(arr);
    ASSERT_EQ(*(arr + len), 0);
}

TEST(arr_s, terminate_2){
    double arr[20];
    memset(arr, 0, sizeof(double) * 20);
    for(int i = 0; i < 15; i++)
        arr[i] = i + 0.25147;

    int len = txt_file::arr_s(arr);
    ASSERT_NE(*(arr + --len), 0);
}




int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}