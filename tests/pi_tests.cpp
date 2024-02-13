#include "gtest/gtest.h"
#include "bigfloat.h"
#include "pi.h"


TEST(PI, PI100){
    EXPECT_EQ(PI.to_string(100), pi(100).to_string(100));
}

TEST(PI, PI500){
    EXPECT_EQ(PI.to_string(500), pi(500).to_string(500));
}

TEST(PI, PI1000){
    EXPECT_EQ(PI.to_string(1000), pi(1000).to_string(1000));
}