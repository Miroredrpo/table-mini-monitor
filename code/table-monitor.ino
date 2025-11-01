#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Bonezegei_DHT11.h>
#include <EEPROM.h>
#include <math.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define DHTPIN 2
#define BUTTON_PIN 3

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Bonezegei_DHT11 dht(DHTPIN);

// ===== CLOCK VARIABLES =====
unsigned long lastMillis = 0;
int sec = 0, minu = 0, hr = 12;
int day = 1, month = 11, year = 2025;

// ===== PAGE SYSTEM =====
int page = 0;
const int totalPages = 5;
unsigned long lastButton = 0;
#define EEPROM_PAGE_ADDR 0

// ===== ANIMATION VARIABLES =====
unsigned long lastAnim = 0;
int animFrame = 0;

// Nepali calendar offset
const int nepaliYearDiff = 56;
const int nepaliMonthDiff = 8;
const int nepaliDayDiff = 17;

// ======== SETUP ========
void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  dht.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();
  Serial.begin(9600);

  page = EEPROM.read(EEPROM_PAGE_ADDR);
  if (page >= totalPages) page = 0;

  fadeIn();
}

// ======== LOOP ========
void loop() {
  updateClock();

  if (digitalRead(BUTTON_PIN) == LOW && millis() - lastButton > 400) {
    fadeOut();
    page = (page + 1) % totalPages;
    EEPROM.write(EEPROM_PAGE_ADDR, page);
    fadeIn();
    lastButton = millis();
  }

  switch (page) {
    case 0: showClock(); break;
    case 1: showADDate(); break;
    case 2: showBSDate(); break;
    case 3: showTempHumidity(); break;
    case 4: showRandomAnimations(); break;
  }

  delay(60);
}

// ======== CLOCK ========
void updateClock() {
  if (millis() - lastMillis >= 1000) {
    lastMillis = millis();
    sec++;
    if (sec >= 60) { sec = 0; minu++; }
    if (minu >= 60) { minu = 0; hr++; }
    if (hr >= 24) {
      hr = 0; day++;
      if (day > 30) { day = 1; month++; }
      if (month > 12) { month = 1; year++; }
    }
  }
}

// ======== HELPERS ========
void showLabel(const char* label) {
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print(label);
}

void fadeOut() {
  for (int i = 0; i < 5; i++) {
    display.dim(true);
    delay(50);
  }
  display.clearDisplay();
  display.display();
}

void fadeIn() {
  for (int i = 0; i < 5; i++) {
    display.dim(false);
    delay(50);
  }
}

void printTime() {
  if (hr < 10) display.print('0');
  display.print(hr);
  display.print(':');
  if (minu < 10) display.print('0');
  display.print(minu);
  display.print(':');
  if (sec < 10) display.print('0');
  display.print(sec);
}

void printDate(int d, int m, int y) {
  if (d < 10) display.print('0');
  display.print(d);
  display.print('/');
  if (m < 10) display.print('0');
  display.print(m);
  display.print('/');
  display.print(y);
}

// ======== PAGES ========
void showClock() {
  display.clearDisplay();
  showLabel("Clock");
  display.setTextSize(2);
  display.setCursor(10, 25);
  printTime();
  display.display();
}

void showADDate() {
  display.clearDisplay();
  showLabel("AD Date");
  display.setTextSize(2);
  display.setCursor(10, 25);
  printDate(day, month, year);
  display.display();
}

void showBSDate() {
  int bsYear = year + nepaliYearDiff;
  int bsMonth = month + nepaliMonthDiff;
  int bsDay = day + nepaliDayDiff;
  if (bsDay > 30) { bsDay -= 30; bsMonth++; }
  if (bsMonth > 12) { bsMonth -= 12; bsYear++; }

  display.clearDisplay();
  showLabel("BS Date");
  display.setTextSize(2);
  display.setCursor(10, 25);
  printDate(bsDay, bsMonth, bsYear);
  display.display();
}

void showTempHumidity() {
  float t = dht.getTemperature();  // ✅ Correct function for Bonezegei_DHT11
  float h = dht.getHumidity();     // ✅ Correct function for Bonezegei_DHT11

  display.clearDisplay();
  showLabel("Env");
  display.setTextSize(1);
  display.setCursor(10, 25);
  display.print("Temp: ");
  display.print(t, 1);
  display.println(" C");
  display.setCursor(10, 40);
  display.print("Humi: ");
  display.print(h, 1);
  display.println(" %");
  display.display();
}

// ======== ANIMATIONS ========
void showRandomAnimations() {
  display.clearDisplay();
  showLabel("Anim");

  if (millis() - lastAnim > 100) {
    animFrame++;
    lastAnim = millis();
  }

  int type = animFrame % 15;
  switch (type) {
    case 0: movingDot(); break;
    case 1: bouncingBall(); break;
    case 2: rainEffect(); break;
    case 3: wavePattern(); break;
    case 4: sparkle(); break;
    case 5: expandingCircle(); break;
    case 6: shrinkingCircle(); break;
    case 7: diagonalLines(); break;
    case 8: zigzag(); break;
    case 9: pulseSquare(); break;
    case 10: snakeLine(); break;
    case 11: orbitDots(); break;
    case 12: twinkleStars(); break;
    case 13: radarSweep(); break;
    case 14: swirl(); break;
  }

  display.display();
}

// ===== 15 COOL ANIMATIONS =====
void movingDot() {
  int x = (animFrame * 4) % SCREEN_WIDTH;
  int y = (sin(animFrame * 0.2) * 20) + 32;
  display.fillCircle(x, y, 2, SSD1306_WHITE);
}

void bouncingBall() {
  int x = (animFrame * 3) % SCREEN_WIDTH;
  int y = abs((animFrame % 32) - 16) * 2;
  display.fillCircle(x, y, 3, SSD1306_WHITE);
}

void rainEffect() {
  for (int i = 0; i < 10; i++) {
    display.drawLine(random(128), random(64), random(128), random(64), SSD1306_WHITE);
  }
}

void wavePattern() {
  for (int x = 0; x < SCREEN_WIDTH; x++) {
    int y = (sin((x + animFrame) * 0.2) * 10) + 32;
    display.drawPixel(x, y, SSD1306_WHITE);
  }
}

void sparkle() {
  for (int i = 0; i < 20; i++) {
    display.drawPixel(random(128), random(64), SSD1306_WHITE);
  }
}

void expandingCircle() {
  int r = (animFrame % 30);
  display.drawCircle(64, 32, r, SSD1306_WHITE);
}

void shrinkingCircle() {
  int r = 30 - (animFrame % 30);
  display.drawCircle(64, 32, r, SSD1306_WHITE);
}

void diagonalLines() {
  for (int i = 0; i < SCREEN_WIDTH; i += 8) {
    display.drawLine(i, 0, i + 32, 64, SSD1306_WHITE);
  }
}

void zigzag() {
  for (int i = 0; i < SCREEN_WIDTH; i += 8) {
    int y = (i % 16 == 0) ? 20 : 44;
    display.drawLine(i, y, i + 8, (y == 20) ? 44 : 20, SSD1306_WHITE);
  }
}

void pulseSquare() {
  int s = (animFrame % 20) + 20;
  display.drawRect(64 - s/2, 32 - s/2, s, s, SSD1306_WHITE);
}

void snakeLine() {
  for (int i = 0; i < SCREEN_WIDTH; i++) {
    int y = 32 + (sin((i + animFrame) * 0.3) * 15);
    display.drawPixel(i, y, SSD1306_WHITE);
  }
}

void orbitDots() {
  int x = 64 + (cos(animFrame * 0.1) * 20);
  int y = 32 + (sin(animFrame * 0.1) * 20);
  display.fillCircle(x, y, 3, SSD1306_WHITE);
}

void twinkleStars() {
  for (int i = 0; i < 30; i++) {
    if (random(0, 5) == 0)
      display.drawPixel(random(128), random(64), SSD1306_WHITE);
  }
}

void radarSweep() {
  float angle = (animFrame % 360) * 0.01745;
  int x = 64 + 30 * cos(angle);
  int y = 32 + 30 * sin(angle);
  display.drawLine(64, 32, x, y, SSD1306_WHITE);
}

void swirl() {
  for (int i = 0; i < 20; i++) {
    int x = 64 + cos(animFrame * 0.2 + i) * (i * 3);
    int y = 32 + sin(animFrame * 0.2 + i) * (i * 3);
    display.drawPixel(x, y, SSD1306_WHITE);
  }
}
