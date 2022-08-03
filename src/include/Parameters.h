/**
 * @file Parameters.h
 * @author Nick Berezny
 * @date 13 Apr 2022
 * @brief Parameter macros
 *
 */

#define NUMBER_OF_THREADS 3
#define NSEC_IN_SEC 1000000000
#define BUFFER_SIZE 10
#define STEP_SIZE_MS 1
#define DAQ_NUM_OF_CH 6
#define MAT_EXP_ITERATIONS 50

#define WAIT_STATE 0
#define HOME_STATE 1
#define CALIBRATE_STATE 2
#define SET_STATE 3
#define READY_STATE 4
#define RUN_STATE 5
#define STOP_STATE 6
#define SHUTDOWN_STATE 7

#define ADDR "127.0.0.1" //"192.168.0.93"

#define FT_GAIN_g 16017.6
#define FT_OFFSET_g 98.17

#define CMD_GAIN 0.2516
#define CMD_OFFSET 2.51
#define MOTOR_KT 38.5 //mNm 

#define ENC_TO_M 0.0000046 //0.00115

#define MD_TEST 5.0
#define BD_TEST 10.0
#define KD_TEST 100.0

//TODO
#define MOTOR_ZERO 0
#define MOTOR_SLOW_BWD 0
#define MOTOR_SLOW_FWD 0