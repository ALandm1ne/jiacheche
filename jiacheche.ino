/*
 * Bigfish扩展板舵机口: 4, 7, 11, 3, 8, 12, 14, 15, 16, 17, 18, 19
 * 使用软件调节舵机时请拖拽对应序号的控制块
 */

/*
 * 180度舵机从0到180是顺时针旋转，反之逆时针旋转
 * 270度舵机从0到180是逆时针旋转，反之顺时针旋转
 * 360度舵机从90到0是顺时针旋转，反之逆时针旋转，且在90度位置停止不动
 */

#include <Servo.h>

#define ANGLE_VALUE_MIN 0
#define ANGLE_VALUE_MAX 180
#define PWM_VALUE_MIN   500
#define PWM_VALUE_MAX   2500

#define PIN_FOREARM   12   // 小臂舵机
#define PIN_UPPERARM  3    // 大臂舵机
#define PIN_YAW       8    // yaw舵机
#define PIN_GRIPPER   4    // 夹爪舵机

// yaw舵机角度姿态
#define YAW_ANGLE_LEFT   115  // 左
#define YAW_ANGLE_RIGHT  47   // 右
#define YAW_ANGLE_BACK   165  // 后

// 夹爪舵机角度姿态
#define GRIPPER_ANGLE_OPEN  165  // 张开
#define GRIPPER_ANGLE_CLOSE 120  // 夹紧

Servo forearmServo;
Servo upperarmServo;
Servo yawServo;
Servo gripperServo;

void setup() {
  Serial.begin(9600);

  // 初始化舵机引脚并设置脉冲宽度范围
  forearmServo.attach(PIN_FOREARM, PWM_VALUE_MIN, PWM_VALUE_MAX);
  upperarmServo.attach(PIN_UPPERARM, PWM_VALUE_MIN, PWM_VALUE_MAX);
  yawServo.attach(PIN_YAW, PWM_VALUE_MIN, PWM_VALUE_MAX);
  gripperServo.attach(PIN_GRIPPER, PWM_VALUE_MIN, PWM_VALUE_MAX);

  // 初始化位置为定义的起始角度
  forearmServo.write(FOREARM_ANGLE_START);
  upperarmServo.write(UPPERARM_ANGLE_START);
  yawServo.write(YAW_ANGLE_LEFT);
  gripperServo.write(GRIPPER_ANGLE_OPEN);
}

void Pos_init() {
  yawServo.write(YAW_ANGLE_LEFT);

}

void Pos_begin() {
  yawServo.write(YAW_ANGLE_LEFT);
  gripperServo.write(GRIPPER_ANGLE_OPEN);
  forearmServo.write(FOREARM_ANGLE_START);
}

void Pos_catch() {
  yawServo.write(YAW_ANGLE_LEFT);
  gripperServo.write(GRIPPER_ANGLE_OPEN);
  delay(1000);
  forearmServo.write(170);
  upperarmServo.write(100);
  delay(1000);
  gripperServo.write(GRIPPER_ANGLE_CLOSE);
  delay(1000);
  forearmServo.write(145);
  upperarmServo.write(180);

}

void loop() {
  Pos_begin();
  delay(1000);
  Pos_catch();
  delay(1000);
  
}
