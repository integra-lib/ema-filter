#include <gtest/gtest.h>

#include <integra/ema_filter.hpp>

namespace
{

TEST(EmaFilterTest, FirstUpdateHasNoLag)
{
    integra::EmaFilter filter{0.1F};
    EXPECT_FLOAT_EQ(filter.Update(10.0F), 10.0F);
}

TEST(EmaFilterTest, BlendsWithTheAlphaWeight)
{
    integra::EmaFilter filter{0.25F};
    EXPECT_FLOAT_EQ(filter.Update(100.0F), 100.0F);
    // 0.25 * 0 + 0.75 * 100
    EXPECT_FLOAT_EQ(filter.Update(0.0F), 75.0F);
    // 0.25 * 0 + 0.75 * 75
    EXPECT_FLOAT_EQ(filter.Update(0.0F), 56.25F);
}

TEST(EmaFilterTest, ConvergesTowardsAConstantInput)
{
    integra::EmaFilter filter{0.5F};
    std::ignore = filter.Update(0.0F);
    float last  = 0.0F;
    for (int i = 0; i < 40; ++i)
    {
        last = filter.Update(10.0F);
    }
    EXPECT_NEAR(last, 10.0F, 0.001F);
}

TEST(EmaFilterTest, AlphaOneFollowsTheInputExactly)
{
    integra::EmaFilter filter{1.0F};
    EXPECT_FLOAT_EQ(filter.Update(3.0F), 3.0F);
    EXPECT_FLOAT_EQ(filter.Update(9.0F), 9.0F);
}

TEST(EmaFilterTest, ResetMakesTheNextUpdateLagFree)
{
    integra::EmaFilter filter{0.25F};
    std::ignore = filter.Update(100.0F);
    std::ignore = filter.Update(0.0F);

    filter.Reset();
    EXPECT_FLOAT_EQ(filter.Update(42.0F), 42.0F);
}

} // namespace
