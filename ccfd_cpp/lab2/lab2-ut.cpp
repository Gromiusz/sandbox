#include <gtest/gtest.h>
#include "lab2.hpp"

class VectorEmptyTest : public testing::Test {
protected:
    Vector vector;

    VectorEmptyTest(): vector{4} {
        //vector.print();
    }
};

class VectorNonZeroTest : public testing::Test {
protected:
    Vector vector;

    VectorNonZeroTest(): vector{4} {
        vector[3] = 4;
        vector[1] = 1.25;
    }
};

TEST_F(VectorEmptyTest, BuckleOperator)
{
    vector[3] = 4;
    EXPECT_EQ(vector[0],0);
    EXPECT_EQ(vector[1],0);
    EXPECT_EQ(vector[2],0);
    EXPECT_EQ(vector[3],4);
}

TEST_F(VectorNonZeroTest, Resize)
{
    vector.resize(10);
    EXPECT_EQ(vector[0],0);
    EXPECT_EQ(vector[1],1.25);
    EXPECT_EQ(vector[2],0);
    EXPECT_EQ(vector[3],4);
    for(int i=4; i<10; i++)
    {
        EXPECT_EQ(vector[i],0);
    }
}

TEST_F(VectorNonZeroTest, CopyConstructor)
{
    Vector new_vector{vector};

    EXPECT_EQ(new_vector[0],0);
    EXPECT_EQ(new_vector[1],1.25);
    EXPECT_EQ(new_vector[2],0);
    EXPECT_EQ(new_vector[3],4);

    EXPECT_EQ(vector[0],0);
    EXPECT_EQ(vector[1],1.25);
    EXPECT_EQ(vector[2],0);
    EXPECT_EQ(vector[3],4);
}

TEST_F(VectorNonZeroTest, AssignmentOperator)
{
    Vector new_vector{2};
    new_vector[1] = 3.2;

    new_vector = vector;

    EXPECT_EQ(new_vector[0],0);
    EXPECT_EQ(new_vector[1],1.25);
    EXPECT_EQ(new_vector[2],0);
    EXPECT_EQ(new_vector[3],4);

    EXPECT_EQ(vector[0],0);
    EXPECT_EQ(vector[1],1.25);
    EXPECT_EQ(vector[2],0);
    EXPECT_EQ(vector[3],4);
}

TEST_F(VectorNonZeroTest, AssignmentOperatorAtSameElement)
{
    vector = vector;

    EXPECT_EQ(vector[0],0);
    EXPECT_EQ(vector[1],1.25);
    EXPECT_EQ(vector[2],0);
    EXPECT_EQ(vector[3],4);
}

TEST_F(VectorNonZeroTest, MovingCopyConstructor)
{
    Vector new_vector{std::move(vector)};

    EXPECT_EQ(new_vector[0],0);
    EXPECT_EQ(new_vector[1],1.25);
    EXPECT_EQ(new_vector[2],0);
    EXPECT_EQ(new_vector[3],4);
}

TEST_F(VectorNonZeroTest, MovingAssignmentOperator)
{
    Vector new_vector{2};
    new_vector[1] = 3.2;

    new_vector = std::move(vector);

    EXPECT_EQ(new_vector[0],0);
    EXPECT_EQ(new_vector[1],1.25);
    EXPECT_EQ(new_vector[2],0);
    EXPECT_EQ(new_vector[3],4);

}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}