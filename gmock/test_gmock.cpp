#include <iostream>
#include "gtest/gtest.h"
#include "gmock/gmock.h"

using ::testing::Return;
using ::testing::_;
using ::testing::Throw;

class Foo
{
public:
    virtual bool Add(int data) = 0;
// protected:
//     virtual bool Sub() = 0;
// private:
//     virtual bool Mul() = 0;
};

class MockFoo : public Foo
{
public:
    // Even if base class has functions not in public,
    // mock class should have MOCK_METHOD*() in public
    MOCK_METHOD1(Add, bool(int));
    // MOCK_METHOD0(Sub, bool());
    // MOCK_METHOD0(Mul, bool());
};

class Order
{
public:
    Order(int data) : mydata(data) { }
    bool Calculate(Foo* myFoo)
    {
        try
        {
            return myFoo->Add(mydata);
        }
        catch( ... )
        {
            std::cout << "Exception caught " << std::endl;
            return false;
        }
    }
private:
    int mydata;
};

TEST(OrderTest, Calculate)
{
    MockFoo fooMe;
    EXPECT_CALL(fooMe, Add(55))
        .Times(1)
        .WillOnce(Return(true));
    EXPECT_CALL(fooMe, Add(44))
        .Times(1)
        .WillOnce(Throw(std::bad_alloc()));
    {
        Order od(55);
        ASSERT_TRUE(od.Calculate(&fooMe));
    }

    {
        Order od1(44);
        ASSERT_FALSE(od1.Calculate(&fooMe));
    }
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();

    return 0;
}
