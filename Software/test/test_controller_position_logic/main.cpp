#include <unity.h>

#include "controller_position_logic.h"

void setUp(void) {}
void tearDown(void) {}

void test_deep_from_window_adds_position_and_depth(void) {
    TEST_ASSERT_EQUAL_INT(
        50, controller_position_logic::deepFromWindow(20.0f, 30.0f));
}

void test_position_is_clamped_to_keep_window_inside_range(void) {
    TEST_ASSERT_EQUAL_INT(
        70, controller_position_logic::clampPositionForDepth(80.0f, 30.0f));
    TEST_ASSERT_EQUAL_INT(
        100, controller_position_logic::deepFromWindow(80.0f, 30.0f));
}

void test_depth_is_clamped_to_keep_window_inside_range(void) {
    TEST_ASSERT_EQUAL_INT(
        20, controller_position_logic::clampDepthForPosition(30.0f, 80.0f));
    TEST_ASSERT_EQUAL_INT(
        100, controller_position_logic::deepFromWindow(80.0f, 30.0f));
}

void test_full_depth_forces_position_to_zero(void) {
    TEST_ASSERT_EQUAL_INT(
        0, controller_position_logic::clampPositionForDepth(50.0f, 100.0f));
    TEST_ASSERT_EQUAL_INT(
        100, controller_position_logic::deepFromWindow(50.0f, 100.0f));
}

void test_zero_depth_can_stop_at_any_position(void) {
    TEST_ASSERT_EQUAL_INT(
        80, controller_position_logic::clampPositionForDepth(80.0f, 0.0f));
    TEST_ASSERT_EQUAL_INT(
        80, controller_position_logic::deepFromWindow(80.0f, 0.0f));
}

void test_position_from_window_settings_uses_deep_minus_stroke(void) {
    TEST_ASSERT_EQUAL_INT(
        20, controller_position_logic::positionFromWindowSettings(50.0f, 30.0f));
}

void test_position_from_window_settings_clamps_negative(void) {
    TEST_ASSERT_EQUAL_INT(
        0, controller_position_logic::positionFromWindowSettings(20.0f, 50.0f));
}

int main(int argc, char** argv) {
    UNITY_BEGIN();

    RUN_TEST(test_deep_from_window_adds_position_and_depth);
    RUN_TEST(test_position_is_clamped_to_keep_window_inside_range);
    RUN_TEST(test_depth_is_clamped_to_keep_window_inside_range);
    RUN_TEST(test_full_depth_forces_position_to_zero);
    RUN_TEST(test_zero_depth_can_stop_at_any_position);
    RUN_TEST(test_position_from_window_settings_uses_deep_minus_stroke);
    RUN_TEST(test_position_from_window_settings_clamps_negative);

    return UNITY_END();
}
