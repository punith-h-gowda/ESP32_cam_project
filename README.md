ESP32-CAM Take Photo 

///Parts Required///
ESP32-CAM with OV2640 – read Best ESP32-CAM Dev Boards
MicroSD card
FTDI programmer
Female-to-female jumper wires
5V power supply for ESP32-CAM or power bank (optional)


///Project Overview///

Step2 : Installing the Esp32 add-on
We'll program the ESP32 board using Arduino IDE.
Add this link to preferences in Arduino IDE : https://dl.espressif.com/dl/package_esp32_index.json

////Uploading Code///

##Many FTDI programmers have a jumper that allows you to select 3.3V or 5V. Make sure the jumper is in the right place to select 5V.
/////
Important: GPIO 0 needs to be connected to GND so that you’re able to upload code.
/////

##To upload the code, follow the next steps:

1) Go to Tools > Board and select AI-Thinker ESP32-CAM.

2) Go to Tools > Port and select the COM port the ESP32 is connected to.

3) Then, click the upload button to upload the code.

4) When you start to see these dots on the debugging window as shown below, press the ESP32-CAM on-board RST button.

After Uploading remove the jumper wire between GND and GPI0 pin

Check the Arduino IDE Serial Monitor window to see if everything is working as expected. As you can see, the picture was successfully saved in the microSD card.

##After making sure that everything is working as expected, you can disconnect the ESP32-CAM from the FTDI programmer and power it using an independent power supply.

##To see the photos taken, remove the microSD card from the microSD card slot and insert it into your computer. You should have all the photos saved.



////TFT eSPI display ILI9225////

Required Libraries

1)TFT_eSPI
2}TJpg_Decoder

NOTE: Changing TFT display according to Driver
Go to TFT_eSPI library edit User setup

select Driver ILI9225

change pins selection
SDA == MOSI
CLK == SCLK
RS == DC

#define TFT_MOSI 15 // In some display driver board, it might be written as "SDA" and so on.
#define TFT_SCLK 14
#define TFT_CS   1  // Chip select control pin
#define TFT_DC   12  // Data Command control pin
#define TFT_RST  13  // Reset pin (could connect to Arduino RESET pin)


![ESP32 cam design--punith](https://github.com/punith-h-gowda/ESP32_cam_project/assets/113229976/5fb9b2f9-0565-4b5b-838d-26d685c6bebf)
