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

#define PIN_YAW       8    // yaw舵机
#define PIN_UPPERARM  3    // 大臂舵机
#define PIN_FOREARM   12   // 小臂舵机
#define PIN_GRIPPER   4    // 夹爪舵机

// yaw舵机姿态
#define YAW_ANGLE_LEFT   115  // 左
#define YAW_ANGLE_RIGHT  47   // 右
#define YAW_ANGLE_BACK   165  // 后

// 大臂舵机姿态（这里全都需要重新设置）
#define UPPERARM_ANGLE_START  90  // 竖直（滑丝损坏，未归零）
#define UPPERARM_ANGLE_CATCH  0   // 夹取姿态
#define UPPERARM_ANGLE_LIFT   100 // 抬起姿态
#define UPPERARM_ANGLE_DROP   20  // 装配姿态

// 小臂舵机姿态（这里也需要全部重新设置）
#define FOREARM_ANGLE_START  90  // 水平（滑丝损坏，未归零）
#define FOREARM_ANGLE_CATCH  170 // 夹取姿态
#define FOREARM_ANGLE_LIFT   145 // 抬起姿态
#define FOREARM_ANGLE_DROP   120 // 装配姿态

// 夹爪舵机姿态
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
  gripperServo.write(GRIPPER_ANGLE_OPEN);
  delay(1000);
  yawServo.write(YAW_ANGLE_LEFT);
  forearmServo.write(FOREARM_ANGLE_START);
  upperarmServo.write(UPPERARM_ANGLE_START);
}

void Pos_catch() {
  // 先转到左边打开夹爪
  yawServo.write(YAW_ANGLE_LEFT);
  gripperServo.write(GRIPPER_ANGLE_OPEN);
  delay(1000);

  // 放下大臂和小臂到夹取位置
  forearmServo.write(FOREARM_ANGLE_CATCH);
  upperarmServo.write(UPPERARM_ANGLE_CATCH);
  delay(1000);

  // 夹紧夹爪
  gripperServo.write(GRIPPER_ANGLE_CLOSE);
  delay(1000);

  // 抬起大臂和小臂到抬起位置
  delay(1000);
  forearmServo.write(FOREARM_ANGLE_LIFT);
  upperarmServo.write(UPPERARM_ANGLE_LIFT);
}

void Pos_drop() {
  // 转到右边
  yawServo.write(YAW_ANGLE_RIGHT);
  delay(1000);

  // 放下大臂和小臂到装配位置
  forearmServo.write(FOREARM_ANGLE_DROP);
  upperarmServo.write(UPPERARM_ANGLE_DROP);
  delay(1000);

  // 张开夹爪
  gripperServo.write(GRIPPER_ANGLE_OPEN);
}

void loop() {
  Pos_init();
  delay(10000);
  Pos_catch();
  delay(2000);
  Pos_drop();
  delay(2000);
}
