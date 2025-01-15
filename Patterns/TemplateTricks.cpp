#include "TemplateTricks.h"

void TemplateTricksTest() {
    {
        ClassWithPrivateMembers<TemplateFriend> c;
        TemplateFriend tf;

        tf.print(c);
    }
    {
        TemplateClassWithStaticMember<float> tcwsm1, tcwsm2, tcwsm3;
        TemplateClassWithStaticMember<int> tcwsm4;
        tcwsm1.sz = 3;
        tcwsm4.sz = 4;
        ASSERT_EQUAL(tcwsm1.size(), 3);
        ASSERT_EQUAL(tcwsm2.size(), 3);
        ASSERT_EQUAL(tcwsm3.size(), 3);
        ASSERT_EQUAL(TemplateClassWithStaticMember<float>::size(), 3);
        ASSERT_EQUAL(tcwsm4.size(), 4);
    }
}
