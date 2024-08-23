#include <gtest/gtest.h>

#include "../src/inc/txt_file.h"

TEST(nameprotect, ret){
    std::string name = "hello.";
    std::string ret = txt_file::nameProtect(name);
    ASSERT_EQ(name, ret);
}


int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}