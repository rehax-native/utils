#include <gtest/gtest.h>
#include "../Object.h"
#include <vector>

class ParentTestClass : public rehaxUtils::Object<ParentTestClass>
{
public:
    void parentTest() {}
};

class OtherParentTestClass : public rehaxUtils::Object<ParentTestClass>
{
public:
    void otherParentTest() {}
};

class DerivedTestClass : public ParentTestClass
{
public:
    int derivedTest() {
        return 2;
    }
};

// class OtherDerivedTestClass : virtual public ParentTestClass, virtual public OtherParentTestClass
// {
// public:
//     void otherDerivedTest() {}
// };



TEST(CastTest, BasicAssertions) {

    rehaxUtils::ObjectPointer<ParentTestClass> thing = rehaxUtils::Object<DerivedTestClass>::Create();
    thing->parentTest();

    rehaxUtils::ObjectPointer<DerivedTestClass> derivedThing = rehaxUtils::dynamic_pointer_cast<DerivedTestClass>(thing);
    rehaxUtils::ObjectPointer<ParentTestClass> sameThing = derivedThing;
    int result = derivedThing->derivedTest();

    EXPECT_EQ(result, 2);
    EXPECT_EQ(thing->getReferenceCount(), 3);
    EXPECT_EQ(derivedThing->getReferenceCount(), 3);
    EXPECT_EQ(sameThing->getReferenceCount(), 3);

    // rehaxUtils::ObjectPointer<OtherDerivedTestClass> otherThing = rehaxUtils::Object<OtherDerivedTestClass>::Create();
    // EXPECT_EQ(otherThing->getReferenceCount(), 1);
}
