#include "gtest/gtest.h"
#include "bigfloat.h"
#include "pi.h"


TEST(PI, PI100){
    bigfloat::precision() = 100;
    bigfloat _pi=PI;
//    std::cout<<PI<<std::endl;
    EXPECT_EQ(1, pi());
}

TEST(PI, PI500){
    bigfloat::precision() = 500;
    EXPECT_EQ(PI.to_string().substr(0,500), pi());
}

TEST(PI, PI1000){
    bigfloat::precision() = 1000;
    EXPECT_EQ(PI.to_string().substr(0,1000), pi());
}