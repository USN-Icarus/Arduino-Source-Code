
#include <Arduino_LSM9DS1.h>

float xmin = 1000.0, xmax= -1000.0, ymin= 1000.0, ymax= -1000.0, zmin= 1000.0, zmax= -1000.0;
float offsetx = 0.0, offsety = 0.0, offsetz = 0.0;

void setup() {
  Serial.begin(9600);
  while (!Serial);
  Serial.println("Started");

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }
  Serial.print("Magnetic field sample rate = ");
  Serial.print(IMU.magneticFieldSampleRate());
  Serial.println(" uT");
  Serial.println();
  Serial.println("Magnetic Field in uT");
  Serial.println("X\tY\tZ");
}

void loop() {
  float x, y, z;
  // x: -35.47 <-> 38.75
  // y: -81.47 <-> -6.95
  // z: -47.78 <-> 29.70

  if (IMU.magneticFieldAvailable()) {
    IMU.readMagneticField(x, y, z);
    if(xmin > x){
      xmin = x;
    }
    if(xmax < x){
      xmax = x;
    }
    if(ymin > y){
      ymin = y;
    }
    if(ymax < y){
      ymax = y;
    }
    if(zmin > z){
      zmin = z;
    }
    if(zmax < z){
      zmax = z;
    }

    x -= offsetx;
    y -= offsety;
    z -= offsetz;
    
    Serial.print(x);
    Serial.print('\t');
    Serial.print(y);
    Serial.print('\t');
    Serial.print(z);
    Serial.print('\t');
    float sum = sqrt(sq(x)+sq(y)+sq(z));
    Serial.println(sum);
  }
  if(Serial.available()){
    Serial.parseInt();
    offsetx = (xmin + xmax)/2.0;
    offsety = (ymin + ymax)/2.0;
    offsetz = (zmin + zmax)/2.0;
    Serial.println("New offsets\nx: " + String(offsetx) + "\ty: " + String(offsety) + " \tz: " + String(offsetz));
  }
}
