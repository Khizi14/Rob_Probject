#include <stdio.h>
#include <webots/motor.h>
#include <webots/robot.h>
#include <webots/touch_sensor.h>

#define SPEED 4
#define TIME_STEP 64
#define TURN_TIME_STEP 16

int main() {
  WbDeviceTag bumper;
  WbDeviceTag left_motor, right_motor;
  int left_speed, right_speed;

  wb_robot_init();

  bumper = wb_robot_get_device("bumper");
  wb_touch_sensor_enable(bumper, TIME_STEP);

  left_motor = wb_robot_get_device("left wheel motor");
  right_motor = wb_robot_get_device("right wheel motor");
  wb_motor_set_position(left_motor, INFINITY);
  wb_motor_set_position(right_motor, INFINITY);
  wb_motor_set_velocity(left_motor, 0.0);
  wb_motor_set_velocity(right_motor, 0.0);

  while (wb_robot_step(TIME_STEP) != -1) {
    if (wb_touch_sensor_get_value(bumper) > 0) {
      // Bumper is hit, turn 90 degrees
      left_speed = -SPEED;
      right_speed = SPEED;
      wb_motor_set_velocity(left_motor, left_speed);
      wb_motor_set_velocity(right_motor, right_speed);

      // Wait for the turn to complete
      int turn_steps = 90 / SPEED;
      for (int i = 0; i < turn_steps; ++i) {
        wb_robot_step(TURN_TIME_STEP);
      }

      // Stop the motors after turning
      wb_motor_set_velocity(left_motor, 0.0);
      wb_motor_set_velocity(right_motor, 0.0);
    } else {
      // No obstacle, move straight
      left_speed = SPEED;
      right_speed = SPEED;
      wb_motor_set_velocity(left_motor, left_speed);
      wb_motor_set_velocity(right_motor, right_speed);
    }
  }

  wb_robot_cleanup();

  return 0;
}
