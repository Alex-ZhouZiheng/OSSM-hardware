#include <unity.h>

#include "controller_position_logic.h"

void setUp(void) {}
void tearDown(void) {}

void test_position_zero_places_window_at_shallow_end(void) {
    TEST_ASSERT_EQUAL_INT(
        50, controller_position_logic::depthFromPosition(0.0f, 50.0f));
}

void test_position_middle_moves_window_halfway(void) {
    TEST_ASSERT_EQUAL_INT(
        75, controller_position_logic::depthFromPosition(50.0f, 50.0f));
}

void test_position_full_places_window_at_deep_end(void) {
    TEST_ASSERT_EQUAL_INT(
        100, controller_position_logic::depthFromPosition(100.0f, 50.0f));
}

void test_full_stroke_never_exceeds_depth_range(void) {
    TEST_ASSERT_EQUAL_INT(
        100, controller_position_logic::depthFromPosition(0.0f, 100.0f));
    TEST_ASSERT_EQUAL_INT(
        100, controller_position_logic::depthFromPosition(100.0f, 100.0f));
}

void test_position_from_depth_round_trips(void) {
    TEST_ASSERT_EQUAL_INT(
        50, controller_position_logic::positionFromDepth(75.0f, 50.0f));
}

void test_position_from_depth_clamps_when_depth_is_less_than_stroke(void) {
    TEST_ASSERT_EQUAL_INT(
        0, controller_position_logic::positionFromDepth(25.0f, 50.0f));
}

void test_position_from_depth_handles_full_stroke(void) {
    TEST_ASSERT_EQUAL_INT(
        0, controller_position_logic::positionFromDepth(100.0f, 100.0f));
}

int main(int argc, char** argv) {
    UNITY_BEGIN();

    RUN_TEST(test_position_zero_places_window_at_shallow_end);
    RUN_TEST(test_position_middle_moves_window_halfway);
    RUN_TEST(test_position_full_places_window_at_deep_end);
    RUN_TEST(test_full_stroke_never_exceeds_depth_range);
    RUN_TEST(test_position_from_depth_round_trips);
    RUN_TEST(test_position_from_depth_clamps_when_depth_is_less_than_stroke);
    RUN_TEST(test_position_from_depth_handles_full_stroke);

    return UNITY_END();
}
