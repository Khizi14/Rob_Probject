#include <stdio.h>
#include <webots/motor.h>
#include <webots/robot.h>
#include <webots/touch_sensor.h>
#include <webots/camera.h>
#include <webots/camera_recognition_object.h>

#define SPEED 4
#define TIME_STEP 64

int main() {
  WbDeviceTag bumper, camera;
  WbDeviceTag left_motor, right_motor;
  int movement_counter = 0;
  int j=0, m=0;
  int k=0, i=0;
  wb_robot_init();

  /* get a handle the the bumper and activate it. */
  bumper = wb_robot_get_device("bumper");
  wb_touch_sensor_enable(bumper, TIME_STEP);
  camera = wb_robot_get_device("camera");
  wb_camera_enable(camera, TIME_STEP);
  wb_camera_recognition_enable(camera, TIME_STEP);

  left_motor = wb_robot_get_device("left wheel motor");
  right_motor = wb_robot_get_device("right wheel motor");
  wb_motor_set_position(left_motor, INFINITY);
  wb_motor_set_position(right_motor, INFINITY);
  wb_motor_set_velocity(left_motor,  SPEED);
  wb_motor_set_velocity(right_motor, SPEED);


  while (wb_robot_step(TIME_STEP) != -1) {

   const WbCameraRecognitionObject *objects = wb_camera_recognition_get_objects(camera);
   if (k < 2)
   {
    if (objects[i].id > 0 && k < 1)
    {
     j++;
    }
    if (objects[i].id > 0 && k >= 1)
    {
     m++;
    }
    if (wb_touch_sensor_get_value(bumper) > 0)
    {
     movement_counter = 25;
     k=k + wb_touch_sensor_get_value(bumper);
    }
     if (movement_counter == 0) 
     {
      wb_motor_set_velocity(left_motor,  SPEED);
      wb_motor_set_velocity(right_motor, SPEED);
      } 
      else if (movement_counter >= 17) 
      {
      wb_motor_set_velocity(left_motor,  -SPEED);
      wb_motor_set_velocity(right_motor, -SPEED);
      movement_counter--;
      } 
      else 
      {
      wb_motor_set_velocity(left_motor,  -SPEED/2);
      wb_motor_set_velocity(right_motor, SPEED);
      movement_counter--;
      }
    }
    else
    {
      wb_motor_set_velocity(left_motor,  0.0);
      wb_motor_set_velocity(right_motor, 0.0);
    }
  }

  wb_robot_cleanup();

  return 0;
}