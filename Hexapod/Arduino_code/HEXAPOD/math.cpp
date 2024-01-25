#include "math.h"

Math::Math(){
  this->sita1 =0;
  this->sita2 =0;
  this->phi = 0;
  this->thigh_length = 110;
  this->calf_length = 170;
}
void Math::SetSpeed(double spd){
  this->speed = spd;
}

void Math::SetLegLength(double thigh,double calf){
  thigh_length = thigh;
  calf_length = calf;
}
void Math::CalculateAngle(double r_x, double r_y, double r_z){
  // inverse kinematics
  double angle_a = 0;
  double angle_c = 0;
  double a = 0;
  r_x = -r_x;
  sita2 = atan(r_z/r_x);
  a = sqrt(sq(r_x) + sq(r_z));
  phi = acos((sq(r_z)+sq(r_x)+sq(r_y)-sq(thigh_length)-sq(calf_length))/(thigh_length*calf_length*2));
    
  angle_a = atan(sin(phi)/(thigh_length/calf_length + cos(phi)));
  if (angle_a<0){
    angle_a = M_PI+angle_a;
  }
  angle_c = atan(abs(r_y/a));
  
  if(r_y<0){
    sita1 = angle_a-angle_c;
  }else{
    sita1 = angle_a+angle_c;
  }

  if(r_x>0){
    phi = -phi;
    sita1 = M_PI - sita1;
  }
  
  // radian to degree
  sita1 = sita1/M_PI*180;
  sita2 = sita2/M_PI*180;
  phi = phi/M_PI*180;
  phi = phi-sita1;
  Serial.println(phi);
  // transform to servo angle
  sita1+=135;
  sita2+=135;
  phi = 270 - phi;
}

void Math::GetAngle(Leg* leg){
  leg->SetAngles(sita2,sita1,phi);
}


void Math::Coord_Rotate(double *x,double *y,double *z,double pitch, double yaw, double roll){
  r_x = *x;
  r_y = *y;
  r_z = *z;
    //Rotate about X-axis
  Rotation_Matrix(-pitch);
  temp_y = r_y * r_matrix[0][0] + r_z * r_matrix[0][1];//cos -sin
  temp_z = r_y * r_matrix[1][0] + r_z * r_matrix[1][1];//sin cos
  r_y = temp_y;
  r_z = temp_z;
  Rotation_Matrix(-yaw);
  temp_x = r_x * r_matrix[0][0] + r_z * r_matrix[0][1];
  temp_z = r_x * r_matrix[1][0] + r_z * r_matrix[1][1];
  r_z = temp_z;
  r_x = temp_x;
  Rotation_Matrix(-roll);
  temp_y = r_y * r_matrix[0][0] + r_x * r_matrix[0][1];
  temp_x = r_y * r_matrix[1][0] + r_x * r_matrix[1][1];
  r_x = temp_x;
  r_y = temp_y;
  
  *x = temp_x;
  *y = temp_y;
  *z = temp_z;
  
}

void Math::Rotation_Matrix(double angle){
  this->r_matrix[0][0] = cos(angle);
  this->r_matrix[0][1] = -sin(angle);
  this->r_matrix[1][0] = sin(angle);
  this->r_matrix[1][1] = cos(angle);
}

// void Math::CalculateAngle(Leg* leg,unsigned long time_elapsed){
//   // turning_angle = math.pi/8
//   unsigned int period = 1000;
//   double z_offset=0;
//   double x_offset=100;
//   double y_offset=-70;
//   double DistanceTravel = 90;

//   double angle_a;
//   double angle_c;
//   double a;
//   double time = time_elapsed%period;
//   double phase_angle = time/(period/2)*M_PI;

//   // // formula
//   if(time <= period/2){
//     // circle
//     r_z = DistanceTravel*cos(phase_angle)+z_offset;
//     r_y = DistanceTravel*sin(phase_angle)+y_offset;
//     r_x = x_offset;
//   }else{
//     // line
//     r_z = DistanceTravel*cos(phase_angle)+z_offset;
//     r_y = y_offset;
//     r_x = x_offset;
//   }
//   // if(time <=period/2){
//   //   r_z = (DistanceTravel+10)*2*time/(period)+z_offset;
//   //   r_y = (DistanceTravel-30)/2*sin(time/(period)*4*M_PI)+y_offset;
//   //   r_x = x_offset;
//   // }else{
//   //   r_z = (DistanceTravel+10)*(1-2*(time-period/2)/(period))+z_offset;
//   //   r_y = (DistanceTravel-30)*sin(2*M_PI-(time-period/2)/(period)*4*M_PI)+y_offset;
//   //   r_x = x_offset;
//   // }
      

//   // inverse kinematics
//   r_x = -r_x;
//   sita2 = atan(r_z/r_x);
//   a = sqrt(sq(r_x) + sq(r_z));
//   phi = acos((sq(r_z)+sq(r_x)+sq(r_y)-sq(calf_length)-sq(thigh_length))/(calf_length*thigh_length*2));
      
//   angle_a = atan(sin(phi)/(calf_length/thigh_length + cos(phi)));
//   if (angle_a<0){
//     angle_a = M_PI+angle_a;
//   }
//   angle_c = atan(abs(r_y/a));

//   if(r_y<0){
//     sita1 = angle_a-angle_c;
//   }else{
//     sita1 = angle_a+angle_c;
//   }

//   if(r_x > 0){
//     phi = -phi;
//     sita1 = M_PI - sita1;
//   }
  
//   sita1 = sita1/M_PI*180;
//   sita2 = sita2/M_PI*180;
//   phi = phi/M_PI*180;
//   phi = phi-sita1;
// }