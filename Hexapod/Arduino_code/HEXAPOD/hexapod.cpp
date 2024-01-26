/*
  INDEXES
  5               25
    6          26
      7      27
  9 10 11   23 22 21
      15     19
    14          18
  13              17
  servo driver:

  B 16 15 14 13 | 12 11 10 9 | 8 7 6 5| 4 3 2 1 (+16)
     X  X  X  X    X  #  # *   X # # *  X # # *
  A 1 2 3 4 | 5 6 7 8 | 9 10 11 12 | 13 14 15 16
    X X X X   * # # X   *  #  #  X    *  #  #  X
  
  A:1~16       B:17~32
*/
#include "hexapod.h"
#include "leg.h"
#include "math.h"
#include "servo.h"
#include "controller.h"

Hexapod::Hexapod()
  : calculator(),
    driver(),
    joystick(this),
    left_front(&calculator,&driver),  
    left_mid(&calculator,&driver),  
    left_back(&calculator,&driver), 
    right_front(&calculator,&driver),  
    right_mid(&calculator,&driver), 
    right_back(&calculator,&driver){
  //                        hip thigh knee
  this->left_front.SetIndex(7,6,5);
  this->left_mid.SetIndex(11,10,9);
  this->left_back.SetIndex(15,14,13);
  this->right_front.SetIndex(27,26,25);
  this->right_mid.SetIndex(23,22,21);
  this->right_back.SetIndex(19,18,17);

  this->State = "Default";
  
  this->start_time = 0;

  this->X_pos_joystick = 0;
  this->Y_pos_joystick = 0;
  this->button_state = 0;
}

void Hexapod::Reset(){
  left_front.Reset();
  left_mid.Reset();
  left_back.Reset();
  right_front.Reset();
  right_mid.Reset();
  right_back.Reset();
}

void Hexapod::InitiateDriver(){
  this->driver.initiate();
}
void Hexapod::Walk(unsigned long time){
  // START
  if(start_time == 0) {
    start_time = time;
  }
  period = 2000;
  z_offset=0;
  x_offset=150;
  y_offset=-70;
  double DistanceTravel = sqrt(sq(X_pos_joystick)+sq(Y_pos_joystick))*70;

  time_elapsed = (time-start_time)%period;
  phase_angle = time_elapsed/(period/2.0)*M_PI;
  // formula
  // left_front && left_back && right_mid time -->r_xyz
  if(time_elapsed <= period/2.0){
    // circle
    r_z = DistanceTravel*cos(phase_angle)+z_offset;
    r_y = DistanceTravel*sin(phase_angle)+y_offset;
    r_x = x_offset;
  }else{
    // line
    r_z = DistanceTravel*cos(phase_angle)+z_offset;
    r_y = y_offset;
    r_x = x_offset;
  }
  time_elapsed = (time-start_time + period/2)%period;
  phase_angle = time_elapsed/(period/2.0)*M_PI;
  // right_front && right_back && left_mid -->r_xyz_2
  if(time_elapsed <= period/2.0){
    // circle
    r_z_2 = DistanceTravel*cos(phase_angle)+z_offset;
    r_y_2 = DistanceTravel*sin(phase_angle)+y_offset;
    r_x_2 = x_offset;
  }else{
    // line
    r_z_2 = DistanceTravel*cos(phase_angle)+z_offset;
    r_y_2 = y_offset;
    r_x_2 = x_offset;
  }
  left_mid.GoToPosition(r_x_2,r_y_2,r_z_2);
  temp_x = r_x;
  temp_y = r_y;
  temp_z = r_z;
  calculator.Coord_Rotate(&temp_x,&temp_y,&temp_z,0,M_PI/3,0);
  left_front.GoToPosition(temp_x, temp_y, temp_z);
  temp_x = r_x;
  temp_y = r_y;
  temp_z = r_z;
  calculator.Coord_Rotate(&temp_x,&temp_y,&temp_z,0,-M_PI/3,0);
  left_back.GoToPosition(temp_x, temp_y, temp_z);

  // RIGHT
  time_elapsed = (time-start_time)%period;
  phase_angle = 2*M_PI - time_elapsed/(period/2.0)*M_PI;
  // formula
  // left_front && left_back && right_mid time -->r_xyz
  if(time_elapsed <= period/2.0){
    // circle
    r_z = DistanceTravel*cos(phase_angle)+z_offset;
    r_y = -DistanceTravel*sin(phase_angle)+y_offset;
    r_x = x_offset;
  }else{
    // line
    r_z = DistanceTravel*cos(phase_angle)+z_offset;
    r_y = y_offset;
    r_x = x_offset;
  }
  time_elapsed = (time-start_time + period/2)%period;
  phase_angle = 2*M_PI -time_elapsed/(period/2.0)*M_PI;
  // right_front && right_back && left_mid -->r_xyz_2
  if(time_elapsed <= period/2.0){
    // circle
    r_z_2 = DistanceTravel*cos(phase_angle)+z_offset;
    r_y_2 = -DistanceTravel*sin(phase_angle)+y_offset;
    r_x_2 = x_offset;
  }else{
    // line
    r_z_2 = DistanceTravel*cos(phase_angle)+z_offset;
    r_y_2 = y_offset;
    r_x_2 = x_offset;
  }
  right_mid.GoToPosition(r_x_2,r_y_2,r_z_2);
  temp_x = r_x;
  temp_y = r_y;
  temp_z = r_z;
  calculator.Coord_Rotate(&temp_x,&temp_y,&temp_z,0,-M_PI/3,0);
  right_back.GoToPosition(temp_x, temp_y, temp_z);
  temp_x = r_x;
  temp_y = r_y;
  temp_z = r_z;
  calculator.Coord_Rotate(&temp_x,&temp_y,&temp_z,0,M_PI/3,0);
  right_front.GoToPosition(temp_x, temp_y, temp_z);

}
void Hexapod::Stand(unsigned long time){
  period = 2000;
  // START
  if(start_time == 0) {
    start_time = time;
  }
  // END
  if(time - start_time > period) {
    start_time = 0;
    State = "Idle";
    return;
  }   
  time_elapsed = (time-start_time)%period;
  if(time_elapsed <= period/2.0){
    //curve
    r_x = 240 - sin(time_elapsed/1000.0*M_PI/2.0)*90;
    // Serial.println(r_x);
    r_y = cos(time_elapsed/1000.0*M_PI/2.0)*11;
    r_z = 0;
  }else{
    //line
    r_x = 150;
    r_y = ((time_elapsed - (double)period/2.0)/1000.0)*-70;
    r_z = 0;
  } 
  left_front.GoToPosition(r_x,r_y,r_z);
  left_mid.GoToPosition(r_x,r_y,r_z);
  left_back.GoToPosition(r_x,r_y,r_z);
  right_front.GoToPosition(r_x,r_y,r_z);
  right_mid.GoToPosition(r_x,r_y,r_z);
  right_back.GoToPosition(r_x,r_y,r_z);
  
  
}
void Hexapod::Update(unsigned long time){
  joystick.Update();
  if (State == "StandingUp"){
    Stand(time);
  }else if (State == "Idle"){
    // Ready to do anything
    State = "Walk";
  }else if (State == "Walk"){
    Walk(time);
  }else if (State == "Default"){
    Reset();
    if(button_state == 1){
      State = "StandingUp";
    }
  }
}
void Hexapod::SetXYPos(double X, double Y){
  X_pos_joystick = X;
  Y_pos_joystick = Y;
}
void Hexapod::SetButtonState(bool state){
  button_state = state;
}