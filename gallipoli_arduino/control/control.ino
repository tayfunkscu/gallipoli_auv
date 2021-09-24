#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
#endif

#include <ros.h>
#include <std_msgs/UInt16.h>
#include <std_msgs/Float64.h>
#include <gallipoli_msgs/Motorpwm.h>
#include <Wire.h>
#include "MS5837.h"
#include <Servo.h>


MS5837 sensor;

ros::NodeHandle nh;

std_msgs::Float64 depth;
ros::Publisher pub_depth("depth", &depth);


Servo esc1,esc2,esc3,esc4,esc5,esc6,esc7,esc8;

#define upper_limit 2000
#define lower_limit 1000
#define stop_sig 1500

void direction_cb(const gallipoli_msgs::Motorpwm& msg){
      esc1.writeMicroseconds(msg.m1);
      esc2.writeMicroseconds(msg.m2);
      esc3.writeMicroseconds(msg.m3);
      esc4.writeMicroseconds(msg.m4);
}

void vertical_pwm_cb(const gallipoli_msgs::Motorpwm& msg){
      esc5.writeMicroseconds(msg.m1);
      esc6.writeMicroseconds(msg.m2);
      esc7.writeMicroseconds(msg.m3);
      esc8.writeMicroseconds(msg.m4);
}

ros::Subscriber<gallipoli_msgs::Motorpwm> direciton_sub("direction_pwm", direction_cb);
ros::Subscriber<std_msgs::UInt16> veritcal_pwm_sub("vertical_pwm", vertical_pwm_cb);

void setup() {
  esc1.attach(6,lower_limit,upper_limit);
  esc2.attach(7,lower_limit,upper_limit);
  esc3.attach(8,lower_limit,upper_limit);
  esc4.attach(9,lower_limit,upper_limit);
  esc5.attach(10,lower_limit,upper_limit);
  esc6.attach(11,lower_limit,upper_limit);
  esc7.attach(12,lower_limit,upper_limit);
  esc8.attach(13,lower_limit,upper_limit);

  esc1.writeMicroseconds(stop_sig);
  esc2.writeMicroseconds(stop_sig);
  esc3.writeMicroseconds(stop_sig);
  esc4.writeMicroseconds(stop_sig);
  esc5.writeMicroseconds(stop_sig);
  esc6.writeMicroseconds(stop_sig);
  esc7.writeMicroseconds(stop_sig);
  esc8.writeMicroseconds(stop_sig);
  delay(3000);

  nh.initNode();
  nh.subscribe(direciton_sub);
  nh.subscribe(veritcal_pwm_sub);
  nh.advertise(pub_depth);


  Wire.begin();

  // Initialize pressure sensor
  // Returns true if initialization was successful
  // We can't continue with the rest of the program unless we can initialize the sensor
  while (!sensor.init()) {
    nh.logerror("Init failed!");
    nh.logerror("Are SDA/SCL connected correctly?");
    nh.logerror("Blue Robotics Bar30: White=SDA, Green=SCL\n\n");
    delay(5000);
  }
  
  sensor.setModel(MS5837::MS5837_30BA);
  sensor.setFluidDensity(1020); // kg/m^3 (freshwater, 1029 for seawater)
}

void loop() {
  sensor.read();

  depth.data = sensor.depth();
  pub_depth.publish(&depth);
  nh.spinOnce();
  delay(1);
}
