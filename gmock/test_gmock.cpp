#include <iostream>
#include "gtest/gtest.h"
#include "gmock/gmock.h"

using ::testing::Return;
using ::testing::_;
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
        return myFoo->Add(mydata);
    }
private:
    int mydata;
};

TEST(OrderTest, Calculate)
{
    MockFoo fooMe;
    Order od(55);
    EXPECT_CALL(fooMe, Add(55))
        .Times(1)
        .WillOnce(Return(true));
    bool d = od.Calculate(&fooMe);
    std::cout << "return from Add " << d << std::endl;
    ASSERT_FALSE(d);
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();

    return 0;
}
