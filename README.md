# Bluetooth Audio Box

##Objective

Combine the ESP32 Board with the MAX98357A module to assemble a Bluetooth speaker.

![Watch the video](https://github.com/WAYNEXChen/BluetoothAudioAmplifier/blob/master/Bluetooth%20Audio%20Amplifier.mp4)

##Hardware Design
Connect according to the sections in the diagram below. The sections can be divided as follows:
![overview](bluetooth_audio_amplifier_circuit.png)
![overview1](Bluetooth Audio Amplifier circuit(top side).PNG)
![overview2](Bluetooth Audio Amplifier circuit(Bottom side).PNG)

1.ESP32: There are many versions of ESP32. Here, we are using the NodeMCU-32S due to its affordable price, easy accessibility, and built-in Bluetooth functionality. We utilize PINs 21, 22, and 23 for I2S interface output.
![ESP32](/SPEC/ESP32/nodemcu_32s_pin.png)

2. Wattage: The MAX98357A module is a simple I2S input interface AMP that requires a VDD of 5V. The maximum output power of the module can be achieved by connecting the Gain Pin through a 100K ohm to GND, as demonstrated in the diagram with resistors R1 and R2.


3.Left and Right Channels: Based on the specifications, it is evident that the SD_MODE Pin can determine the left and right channels. When the voltage of the SD_MODE Pin lies between 0.7V and 1.4V, it sets to the right channel. When the voltage exceeds 1.4V, it sets to the left channel. 
The configuration of SD_MODE can be achieved either through Push Pull resistors or the Open Drain method. It is recommended to use the Push Pull method, as SD_MODE has its own timing sequence. If it's pulled to a High voltage before the firmware can control it, it might lead to AMP issues.
![Left and Right Channels](/SPEC/AudioAmp/SD_MODE_Control.PNG)



##Firmware Configuration
Developed using the Arduino IDE, we employed the ESP32-A2DP-main Library. The primary configurations are: Pin 22 set as BCLK, Pin 21 as LRCLK, Pin 23 as Data_output, and Pin 19 as AMP_SD_Pin. The Bluetooth device name for ESP32 has been changed to "WayneMusicBox".
	
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

## Future Outlook
1. **Cost**: The architecture seems quite straightforward, integrating an MCU with Bluetooth capability and a digital I2S AMP. We can consider switching the ESP32 for a more task-specific MCU or integrating two AMPs for cost reduction.

2. **Speaker**: If the AMP's audio output power is on the lower side, choosing a 4ohm speaker can help counteract this low power output. On the other hand, if the AMP's audio output power is still quite low, opting for an 8ohm speaker can enhance the depth of the sound. The choice is flexible, and either can offer sufficiently loud sound for individual use.

3. **Audio Quality**: If the audio quality seems unsatisfactory, placing a DSP in between the circuits for sound adjustment can be beneficial. For instance, a DSP with EQ functionality or even applying a DSP with special certifications (e.g. DTS and Dolby ATMOS) can be considered.


## Reference Libraries
1. [Arduino_TensorFlowLite_ESP32] (https://github.com/tanakamasayuki/Arduino_TensorFlowLite_ESP32)
2. [btAudio] (https://github.com/tierneytim/btAudio)
3. [NodeMCU-32S] (https://docs.ai-thinker.com/esp32/boards/nodemcu_32s)