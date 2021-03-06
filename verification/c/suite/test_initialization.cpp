/*
 * Copyright 2020 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * Sanity tests.
 */
#include "gmock/gmock.h"
#include "uavcan/primitive/Empty_1_0.h"
#include "uavcan/si/unit/force/Vector3_1_0.h"
#include "uavcan/_register/Name_1_0.h"
#include "regulated/zubax/sensor/bms/BatteryPackParams_0_1.h"

/**
 * Verify an empty, complex type compiles and initializes.
 */
TEST(InitializationTests, InitEmpty)
{
    uavcan_primitive_Empty_1_0 subject;
    // Doesn't crash == pass
    uavcan_primitive_Empty_1_0_init(nullptr);
    uavcan_primitive_Empty_1_0_init(&subject);
    ASSERT_EQ(0U, subject._dummy_);
}

/**
 * Verify initialization of a primitive with a static array.
 */
TEST(InitializationTests, InitWithPrimitiveArray)
{
    uavcan_si_unit_force_Vector3_1_0 subject;
    uavcan_si_unit_force_Vector3_1_0_init(nullptr);
    uavcan_si_unit_force_Vector3_1_0_init(&subject);
    ASSERT_EQ(3U, uavcan_si_unit_force_Vector3_1_0_newton_array_capacity());
    ASSERT_FALSE(uavcan_si_unit_force_Vector3_1_0_newton_array_is_variable_length());
    for (std::size_t i = 0; i < uavcan_si_unit_force_Vector3_1_0_newton_array_length(&subject); ++i)
    {
        ASSERT_FLOAT_EQ(0.0f, subject.newton[i]);
    }
}

/**
 * Verify initialization of a primitive with a variable-length array.
 */
TEST(InitializationTests, InitWithVariableLengthArray)
{
    uavcan_register_Name_1_0 subject;
    uavcan_register_Name_1_0_init(nullptr);
    uavcan_register_Name_1_0_init(&subject);
    ASSERT_TRUE(uavcan_register_Name_1_0_name_array_is_variable_length());
    ASSERT_EQ(0U, uavcan_register_Name_1_0_name_array_length(&subject));
}

/**
 * Verify fix of issue #130 where C initialization generated incorrect code for arrays of compound types.
 */
TEST(InitializationTests, InitZubaxBMSParams)
{
    regulated_zubax_sensor_bms_BatteryPackParams_0_1 subject;
    subject.design_cell_voltage_min_typ_max[0].volt = 99.0f;
    regulated_zubax_sensor_bms_BatteryPackParams_0_1_init(&subject);
    ASSERT_EQ(3U, regulated_zubax_sensor_bms_BatteryPackParams_0_1_design_cell_voltage_min_typ_max_array_length(&subject));
    ASSERT_FLOAT_EQ(0.0f, subject.design_cell_voltage_min_typ_max[0].volt);
}
