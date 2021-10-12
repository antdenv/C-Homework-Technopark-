#include <gtest/gtest.h>

extern "C" {
    #include "Org_struct.h"
    #include "Read_write.h"
}

TEST(Organization, OneOrg) {
    date* a_date = create_date(14, 6, 2001);
    EXPECT_NE(a_date, nullptr);

    date* w_date = create_date(31, 5, 2008);
    EXPECT_NE(w_date, nullptr);

    organization* org = create_organization("ISO", "standart", "International_Standartization_Organization", 1, a_date, w_date);
    EXPECT_NE(org, nullptr);

    size_t size = 1;
    organization** orgs = create_orgs(size);

    orgs[0] = org;
    EXPECT_STREQ(orgs[0]->name, "ISO");
    EXPECT_STREQ(orgs[0]->type, "standart");
    EXPECT_STREQ(orgs[0]->full_name, "International_Standartization_Organization");
    EXPECT_EQ(orgs[0]->rus, 1);
    EXPECT_EQ(orgs[0]->date_accept->day, 14);
    EXPECT_EQ(orgs[0]->date_accept->month, 6);
    EXPECT_EQ(orgs[0]->date_accept->year, 2001);
    EXPECT_EQ(orgs[0]->date_work->day, 31);
    EXPECT_EQ(orgs[0]->date_work->month, 5);
    EXPECT_EQ(orgs[0]->date_work->year, 2008);

    free_orgs(orgs, 1);
}

TEST(Organization, ManyOrgs) {
    size_t size = 3;
    organization** orgs = create_orgs(size);
    ASSERT_NE(orgs, nullptr);

    date** a_dates = create_dates(size);
    ASSERT_NE(a_dates, nullptr);

    date** w_dates = create_dates(size);
    ASSERT_NE(w_dates, nullptr);

    a_dates[0] = create_date(11, 5, 1995);
    a_dates[1] = create_date(10, 7, 1999);
    a_dates[2] = create_date(5, 2, 1992);

    w_dates[0] = create_date(17, 4, 1997);
    w_dates[1] = create_date(18, 5, 2000);
    w_dates[2] = create_date(19, 7, 1995);

    orgs[0] = create_organization("ITU", "union", "International_Telecommunication_Union", 0, a_dates[0], w_dates[0]);
    EXPECT_NE(orgs[0], nullptr);

    orgs[1] = create_organization("ASTM", "test", "American_Society_for_Testing_and_Materials", 0, a_dates[1], w_dates[1]);
    EXPECT_NE(orgs[1], nullptr);

    orgs[2] = create_organization("ICC", "code", "International_Code_Council", 1, a_dates[2], w_dates[2]);
    EXPECT_NE(orgs[2], nullptr);

    size_t n_size = 3;
    EXPECT_EQ(size, n_size);
    
    EXPECT_EQ(orgs[0]->rus, 0);
    EXPECT_STREQ(orgs[0]->name, "ITU");
    EXPECT_EQ(orgs[0]->date_accept->day, 11);

    EXPECT_EQ(orgs[1]->rus, 0);
    EXPECT_STREQ(orgs[1]->name, "ASTM");
    EXPECT_EQ(orgs[1]->date_accept->day, 10);

    EXPECT_EQ(orgs[2]->rus, 1);
    EXPECT_STREQ(orgs[2]->name, "ICC");
    EXPECT_EQ(orgs[2]->date_accept->day, 5);

    free_orgs(orgs, size);
}

TEST(Create_orgs, Check_null) {
    organization** orgs = nullptr;
    size_t size = 0;

    orgs = create_orgs(size);

    EXPECT_EQ(orgs, nullptr);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}