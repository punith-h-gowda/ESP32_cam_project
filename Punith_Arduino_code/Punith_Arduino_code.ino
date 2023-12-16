#include "esp_camera.h"
#include <SPI.h>
#include <TFT_eSPI.h>
#include <TJpg_Decoder.h>
#include "driver/rtc_io.h"
#include "soc/soc.h"           // Disable brownour problems
#include "soc/rtc_cntl_reg.h"  // Disable brownour problems

#define PWDN_GPIO_NUM     32
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM      0
#define SIOD_GPIO_NUM     26
#define SIOC_GPIO_NUM     27
#define Y9_GPIO_NUM       35
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       21
#define Y4_GPIO_NUM       19
#define Y3_GPIO_NUM       18
#define Y2_GPIO_NUM        5
#define VSYNC_GPIO_NUM    25
#define HREF_GPIO_NUM     23
#define PCLK_GPIO_NUM     22

TFT_eSPI tft = TFT_eSPI();


void setup() {
//  Serial.begin(115200);
  
  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH);
  delay(350);
  digitalWrite(4, LOW);
  displayInit();
  cameraInit();
  delay(1000);
  pinMode(3, OUTPUT);
  digitalWrite(3, HIGH);
  delay(350);
  digitalWrite(3, LOW);
  delay(1000);
  
  showingImage();

  // Turns off the ESP32-CAM white on-board LED (flash) connected to GPIO 4
//  pinMode(4, OUTPUT);
//  digitalWrite(4, LOW);
//  rtc_gpio_hold_en(GPIO_NUM_4);

//  delay(1000);
 

  // Bind Wakeup to GPIO13 going LOW
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_2, 0);


  
//  Serial.println("Going to sleep now");
  delay(1000);
 
  esp_deep_sleep_start();
//  Serial.println("This will never be printed");


  
}

void loop() {

}




void cameraInit(){
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;
  config.frame_size = FRAMESIZE_QVGA; //240x176
  config.jpeg_quality = 15;
  config.fb_count = 2;

  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
//    Serial.printf("Camera init failed with error 0x%x", err);
    return;
  }
}

void showingImage(){
  camera_fb_t* fb = esp_camera_fb_get();
  if(!fb || fb->format != PIXFORMAT_JPEG){
//    Serial.println("Camera Capture Failed!");
  }else{
//    Serial.println("Camera Image to Display Here!");

 
    TJpgDec.drawJpg(0, 0, (const uint8_t*)fb->buf, fb->len);
    delay(4000);
//    Serial.println("Call_image_sucessesful");
  }
  esp_camera_fb_return(fb);
}

bool tft_output(int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t* bitmap){
  if( y>= tft.height()) return 0;
  tft.pushImage(x, y, w, h, bitmap);
  return 1;
}

void displayInit(){
  tft.begin();
  tft.setRotation(0);
  tft.fillScreen(TFT_BLACK);

  TJpgDec.setJpgScale(1);
  TJpgDec.setSwapBytes(true);
 TJpgDec.setCallback(tft_output);
}
