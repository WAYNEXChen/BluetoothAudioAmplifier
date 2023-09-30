#include "BluetoothA2DPSinkQueued.h"
#define AMP_SD 19 //setting GPIO19 to Audio_AMP_SD 

BluetoothA2DPSinkQueued a2dp_sink;

void setup() {
    pinMode(AMP_SD, OUTPUT);  //setting AMP_SD to High
    
    i2s_pin_config_t my_pin_config = {
        .bck_io_num = 22,
        .ws_io_num = 21,
        .data_out_num = 23,
        .data_in_num = I2S_PIN_NO_CHANGE
    }; 
    a2dp_sink.set_pin_config(my_pin_config);
    a2dp_sink.start("WayneMusicBox");  
}


void loop() {
  digitalWrite(AMP_SD, HIGH);   // enable AMP_SD
  delay(1000); // do nothing
}
