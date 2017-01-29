// copyright Mihai Oltean, mihai.oltean@gmail.com
// www.jenny5.org
// www.tcreate.org
// source code: https://github.com/jenny5-robot

// MIT License
// ---------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------

#define HEAD_MOTOR_NECK 0
#define HEAD_MOTOR_FACE 1

#define HEAD_POTENTIOMETER_NECK_INDEX 0
#define HEAD_POTENTIOMETER_FACE_INDEX 1
#define HEAD_ULTRASONIC_FACE_INDEX 0

#define LEFT_ARM_BODY_MOTOR 0
#define LEFT_ARM_SHOULDER_UP_DOWN_MOTOR 1
#define LEFT_ARM_SHOULDER_LEFT_RIGHT_MOTOR 2
#define LEFT_ARM_ELBOW_MOTOR 3
#define LEFT_ARM_FOREARM_MOTOR 4
#define LEFT_ARM_GRIPPER_MOTOR 5

#define LEFT_ARM_BODY_POTENTIOMETER_INDEX 0
#define LEFT_ARM_SHOULDER_UP_DOWN_POTENTIOMETER_INDEX 1
#define LEFT_ARM_SHOULDER_LEFT_RIGHT_POTENTIOMETER_INDEX 2
#define LEFT_ARM_ELBOW_POTENTIOMETER_INDEX 3
#define LEFT_ARM_FOREARM_POTENTIOMETER_INDEX 4
#define LEFT_ARM_GRIPPER_BUTTON_INDEX 0
#define LEFT_ARM_GRIPPER_INFRARED_INDEX 0

#define LEFT_ARM_GRIPPER_BUTTON_PIN 15

#define NUM_SECONDS_TO_WAIT_FOR_CONNECTION 3

#define CAM_PIXELS_TOLERANCE 20

#define DOES_NOTHING_SLEEP 10

#define LIDAR_NUM_STEPS 200

#define HEAD_RADIUS_TO_REVERT 70

#define HEAD_CAMERA_INDEX 0
#define LEFT_ARM_CAMERA_INDEX 1

// head
#define _head_horizontal_motor_potentiometer_min 329
#define _head_horizontal_motor_potentiometer_max 829
#define _head_horizontal_motor_potentiometer_home 529

#define _head_vertical_motor_potentiometer_min 332
#define _head_vertical_motor_potentiometer_max 832
#define _head_vertical_motor_potentiometer_home 632


// left arm
#define _potentiometer_min_LEFT_ARM_BODY_MOTOR 380
#define _potentiometer_max_LEFT_ARM_BODY_MOTOR 800
#define _potentiometer_home_LEFT_ARM_BODY_MOTOR 640

#define _potentiometer_min_LEFT_ARM_SHOULDER_UP_DOWN_MOTOR 170
#define _potentiometer_max_LEFT_ARM_SHOULDER_UP_DOWN_MOTOR 600
#define _potentiometer_home_LEFT_ARM_SHOULDER_UP_DOWN_MOTOR 500

#define _potentiometer_min_LEFT_ARM_SHOULDER_LEFT_RIGHT_MOTOR 230
#define _potentiometer_max_LEFT_ARM_SHOULDER_LEFT_RIGHT_MOTOR 750
#define _potentiometer_home_LEFT_ARM_SHOULDER_LEFT_RIGHT_MOTOR 740

#define _potentiometer_min_LEFT_ARM_ELBOW_MOTOR 480
#define _potentiometer_max_LEFT_ARM_ELBOW_MOTOR 830
#define _potentiometer_home_LEFT_ARM_ELBOW_MOTOR 630

#define _potentiometer_min_LEFT_ARM_FOREARM_MOTOR 230
#define _potentiometer_max_LEFT_ARM_FOREARM_MOTOR 720
#define _potentiometer_home_LEFT_ARM_FOREARM_MOTOR 440

#define DC_MOTOR_SPEED 3000
#define DC_MOTOR_SPEED_ROTATE 3000

//----------------------------------------------------------------
