#include <gtest/gtest.h>

#include "../src/headers/myFile.h"

TEST(nameprotect, ret){
    std::string name = "hello.";
    std::string ret = fileLib::nameProtect(name);
    ASSERT_STREQ(name, ret);
}


int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}