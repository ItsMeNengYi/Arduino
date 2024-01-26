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
  double distance_sq = sq(r_z)+sq(r_x)+sq(r_y);
  double angle_a = 0;
  double angle_b = 0;
  double angle_c = 0;

  if(r_x == 0){
    if(r_z >= 0){
      angle_hip = M_PI/2;
    }else{
      angle_hip = -M_PI/2;
    }
  }else{
    angle_hip = atan(abs(r_z/r_x));
    if(r_x > 0){
      if(r_z < 0){
        angle_hip = -angle_hip;
      }
    }else{
      if(r_z > 0){
        angle_hip = M_PI - angle_hip;
      }else{
        angle_hip = angle_hip - M_PI;
      }
    }
  }

  angle_a = acos((sq(thigh_length) + sq(calf_length) - distance_sq)/(2*thigh_length*calf_length));
  angle_knee = M_PI - angle_a;
  angle_b = acos((sq(thigh_length) + distance_sq - sq(calf_length))/(2*thigh_length*sqrt(distance_sq)));
  angle_c = asin(sqrt(sq(r_x)+sq(r_z))/sqrt(distance_sq));
  if(r_y > 0){
    angle_c = M_PI - angle_c;
  }
  angle_thigh = angle_b + angle_c;

  // radian to degree
  angle_hip = angle_hip/M_PI*180;
  angle_thigh = angle_thigh/M_PI*180;
  angle_knee = angle_knee/M_PI*180;

  // transform
  angle_knee = angle_knee + 90;
  angle_thigh = angle_thigh + 45;
  angle_hip = angle_hip + 135;
}

void Math::GetAngle(Leg* leg){
  // leg->SetAngles(sita2,sita1,phi);
  leg->SetAngles(angle_hip, angle_thigh, angle_knee);
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

// OLD VERSION OF INVERSE KINEMATICS (STH IS WRONGG)
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
  // transform to servo angle
  sita1+=135;
  sita2+=135;
  phi = 270 - phi;

