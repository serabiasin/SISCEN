float Kp = 1.1;
float Kd = 1.0;
int Sp = 0;
int lastError = 0;


int MAXPWM = 250;
int MINPWM = 0;
float intervalPWM = (MAXPWM - MINPWM) / 8;
int PV;

#define enA 3
#define in1 5
#define in2 7
#define enB 13
#define in3 9
#define in4 11

#define PUSH1 15 //kiri
#define PUSH2 17 //tengah
#define PUSH3 19 //kanan

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


#define ADDR 0x3C

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);


int s1 = A14;
int s2 = A12;
int s3 = A10;
int s4 = A8;
int s5 = A6;
int s6 = A4;
int s7 = A2;
int s8 = A0;


int lPWM;
int rPWM; //87%dari speed motor B

int kondisi;
int m;
int lp = 0;
int lp2 = 0;
int sen[8];
int awl[8];
int pth[8];
int htm[8];
int mid[8];
String val;

int counter = 0;

void jalankenMotor();
void tulisOLED(String buffer, int x = 20, int y = 10);
void menuOLED();
void pilihMenu(int menu);
void setCursor(int x, int y);

#include <EEPROM.h>
void savetoROM(int nilaitengah[], int address = 0);
void readtoROM(int nilaitengah[], int address = 1);

void menuCalibrate() {
  tulisOLED("Press Button");
  while (digitalRead(PUSH1) == 1);
  tulisOLED("Callibrating");


  do
  {
    sen[0] = analogRead(s1);
    sen[1] = analogRead(s2);
    sen[2] = analogRead(s3);
    sen[3] = analogRead(s4);
    sen[4] = analogRead(s5);
    sen[5] = analogRead(s6);
    sen[6] = analogRead(s7);
    sen[7] = analogRead(s8);
    if (lp < 8)
    {
      //====================================================
      for (int i = 0; i < 8; i++)
      {
        pth[i] = sen[i];
        Serial.print(pth[i]);
        Serial.print("[");
        Serial.print(i);
        Serial.print("]");
        Serial.print(",");
      }
      Serial.println("PUTIH AWAL");
      //====================================================
      for (int i = 0; i < 8; i++)
      {
        htm[i] = sen[i];
        Serial.print(htm[i]);
        Serial.print("[");
        Serial.print(i);
        Serial.print("]");
        Serial.print(",");
      }
      Serial.println("HITAM AWAL");
    }

    else
    {
      Serial.println(lp);
      //NILAI SENSOR
      //====================================================
      for (int i = 0; i < 8; i++)
      {
        Serial.print(sen[i]);
        Serial.print("[");
        Serial.print(i);
        Serial.print("]");
        Serial.print(",");
      }
      Serial.println("NILAI SENSOR");

      //NILAI PUTIH
      //====================================================
      for (int i = 0; i < 8; i++)
      {
        if (sen[i] < pth[i])
        {
          pth[i] = sen[i];
        }
        else if (sen[i] > pth[i])
        {
          pth[i] = pth[i];
        }
        Serial.print(pth[i]);
        Serial.print("[");
        Serial.print(i);
        Serial.print("]");
        Serial.print(",");
      }
      Serial.println("NILAI PUTIH");

      //NILAI HITAM
      //====================================================
      for (int i = 0; i < 8; i++)
      {
        if (sen[i] > htm[i])
        {
          htm[i] = sen[i];
        }
        else if (sen[i] < htm[i])
        {
          htm[i] = htm[i];
        }
        Serial.print(htm[i]);
        Serial.print("[");
        Serial.print(i);
        Serial.print("]");
        Serial.print(",");
      }
      Serial.println("NILAI HITAM");

      //NILAI TENGAH
      //====================================================
      for (int i = 0; i < 8; i++)
      {
        mid[i] = ((htm[i] - pth[i]) / 2) + pth[i];
        Serial.print(mid[i]);
        Serial.print("[");
        Serial.print(i);
        Serial.print("]");
        Serial.print(",");
      }
      Serial.println("NILAI TENGAH");
    }
    lp++;
    lp2++;
  }
  while (lp2 <= 30);
  savetoROM(mid);
}

void setup() {


  pinMode(s1, INPUT);
  pinMode(s2, INPUT);
  pinMode(s3, INPUT);
  pinMode(s4, INPUT);
  pinMode(s5, INPUT);
  pinMode(s6, INPUT);
  pinMode(s7, INPUT);
  pinMode(s8, INPUT);
  pinMode(PUSH1, INPUT_PULLUP);
  pinMode(PUSH2, INPUT_PULLUP);
  pinMode(PUSH3, INPUT_PULLUP);
  Serial.begin(9600);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  bool option = false;
  display.clearDisplay();
  display.display();

  int menu = 1;
int timing=0;
  while (option != true) {
    if (menu > 3 | menu < 1) {
      menu = 1;
    }
    if (digitalRead(PUSH3) != 1) {
      display.clearDisplay();
      delay(200);
      menu++;
      timing=0;
    }
    else if (digitalRead(PUSH1) != 1) {
      display.clearDisplay();
      delay(200);
      menu--;
      timing=0;
    }

    menuOLED(menu);
    if (digitalRead(PUSH2) != 1) {
      pilihMenu(menu);
      timing=0;
    }
    timing++;
    if(timing>=30){
      option=true;
    }
    display.display();
    delay(100);


  }

  tulisOLED("Press Button");
  while (digitalRead(PUSH2) == 1);
  tulisOLED("Running");
}

void loop() {
  sen[0] = analogRead(s1);
  sen[1] = analogRead(s2);
  sen[2] = analogRead(s3);
  sen[3] = analogRead(s4);
  sen[4] = analogRead(s5);
  sen[5] = analogRead(s6);
  sen[6] = analogRead(s7);
  sen[7] = analogRead(s8);

  //===================================================================
  //KONVERSI TO STRING
  //===================================================================
  for (int i = 0; i < 8; i++)
  {
    if (sen[i] < mid[i])
    {
      sen[i] = 1;
    }
    else if (sen[i] >= mid[i])
    {
      sen[i] = 0;
    }
    if (i == 0) {
      val = String(sen[i]);
    }
    else {
      val += String(sen[i]);
    }
  }
  //  Serial.println(val);

  //===================================================================
  //PENGKONDISIAN
  //===================================================================


  if (val == "11111110") { //sensor paling kiri
    PV = -7;
    m = 1;
  }
  if (val == "11111000" or val == "11111100")   {
    PV =  -6;
    m = 1;
  }
  if (val == "11111101") {
    PV = -5;
    m = 1;
  }
  if (val == "11110001" or val == "11111001" ) {
    PV = -4;
    m = 1;
  }
  if (val == "11111011") {
    PV = -3;
    m = 1;
  }
  if (val == "11100011" or val == "11110011") {
    PV = -2;
    m = 1;
  }
  if (val == "11110111") {
    PV = -1;
    m = 1;
  }
  if (val == "11100111") {
    // tengah
    PV = 0;
  }
  if (val == "11101111") {
    PV = 1;
    m = 2;
  }
  if (val == "11000111" or val == "11001111") {
    PV = 2;
    m = 2;
  }
  if (val == "11011111") {
    PV = 3;
    m = 2;
  }
  if (val == "10001111" or val == "10011111") {
    PV = 4;
    m = 2;
  }
  if (val == "10111111") {
    PV = 5;
    m = 2;
  }
  if (val == "00011111" or val == "00111111") {
    PV = 6;
    m = 2;
  }
  if (val == "01111111") {
    // ujung kanan
    PV = 7  ;
    m = 2;
  }
  if (val == "11111111" or val == "00000000" ) {
    // loss
    PV = PV;
  }

  //============================================================================================================
  //>>>>>>>MEMORY<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


  int error = Sp - PV;
  int rate = error - lastError;
  int P = Kp * error;
  int D = rate * Kd;
  lastError = error;

  int MV = P + D;


  if (MV == 0) { //lurus, maju cepat
    lPWM = MAXPWM;
    rPWM = MAXPWM;
  } else if (MV > 0) { // alihkan ke kiri
    rPWM = MAXPWM - ((intervalPWM - 20) * MV);
    lPWM = (MAXPWM - (intervalPWM * MV) - 15);

  } else if (MV < 0) { // alihkan ke kanan
    lPWM = MAXPWM + ( ( intervalPWM - 20 ) * MV);
    rPWM = MAXPWM + ( ( intervalPWM * MV ) - 15 );
  }



  jalankenMotor();








  //============================================================================================================

  Serial.print(rPWM);
  Serial.print("   ");
  Serial.print(lPWM);
  Serial.print("   ");
  Serial.print(val);
  Serial.print("   ");
  Serial.println(PV);
}


void jalankenMotor() {


  rPWM = abs(rPWM);
  lPWM = abs(lPWM);


  //Jalan Motor Kiri
  analogWrite(enA, lPWM);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);

  analogWrite(enB, rPWM);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);


}

void tulisOLED(String buffer, int x = 20, int y = 10) {

  display.clearDisplay();
  display.display();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(x, y);

  display.print(buffer);
  display.display();

}

void savetoROM(int nilaitengah[], int address = 0) {
  for (int index = 0; index < 8; index++, address++) {
    EEPROM.write(address,  nilaitengah[index]);
    Serial.println(EEPROM.read(index));
  }
}

void readtoROM(int nilaitengah[], int address = 1) {
  for (int index = 0; index < 8; index++, address++) {
    nilaitengah[index] = EEPROM.read(index);
    Serial.println(nilaitengah[index]);
  }
}
void menuOLEDOne() {
  //  display.clearDisplay();
  display.display();
  display.setTextSize(1);
  display.setTextColor(WHITE);

  display.setCursor(20, 0);
  display.println("1.Callibration");

  display.setTextSize(1);
  display.setCursor(20, 10);
  display.print("2.Load Setting");
  //cursor
  display.setCursor(10, 0);
  display.print(">");
  //end
  display.setCursor(20, 20);
  display.print("3.PID Setting");
}

void menuOLEDTwo() {
  //  display.clearDisplay();
  display.display();
  display.setTextSize(1);
  display.setTextColor(WHITE);

  display.setCursor(20, 0);
  display.println("1.Callibration");

  display.setTextSize(1);
  display.setCursor(20, 10);
  display.print("2.Load Setting");
  //cursor
  display.setCursor(10, 10);
  display.print(">");
  //end
  display.setCursor(20, 20);
  display.print("3.PID Setting");
}


void menuOLEDThree() {
  //  display.clearDisplay();
  display.display();
  display.setTextSize(1);
  display.setTextColor(WHITE);

  display.setCursor(20, 0);
  display.println("1.Callibration");

  display.setTextSize(1);
  display.setCursor(20, 10);
  display.print("2.Load Setting");
  //cursor
  display.setCursor(10, 20);
  display.print(">");
  //end
  display.setCursor(20, 20);
  display.print("3.PID Setting");
}

void menuOLED(int menu) {
  switch (menu) {
    case 1: {
        menuOLEDOne();
        break;
      }
    case 2: {
        menuOLEDTwo();
        break;
      }
    case 3: {
        menuOLEDThree();
        break;
      }
  }


}

void spesifikMenu(int menu) {
  switch (menu) {
    case 1: {
        bool kabur = false;
        digitalWrite(PUSH2, 0);
        while (kabur != true) {

          Serial.println("Case 1");
          display.display();
          display.setTextSize(1);
          display.setTextColor(WHITE);
          display.setCursor(20, 0);
          display.print("Kp = ");
          display.setCursor(60, 0);
          display.println(Kp);
          if (digitalRead(PUSH1) != 1) {
            Kp -= 0.1;
            display.clearDisplay();
          }
          else if (digitalRead(PUSH3) != 1) {
            Kp += 0.1;
            display.clearDisplay();
          }
          else if (digitalRead(PUSH2) != 1) {

            kabur = true;
            return;

          }
          delay(100);
        }
        break;
      }
    case 2: {
        bool kabur = false;
        digitalWrite(PUSH2, 0);
        while (kabur != true) {
          Serial.println("Case 2");
          display.display();
          display.setCursor(20, 10);
          display.print("Kd = ");
          display.setCursor(60, 10);
          display.println(Kd);

          if (digitalRead(PUSH1) != 1) {
            Kd -= 0.1;
            display.clearDisplay();
          }
          else if (digitalRead(PUSH3) != 1) {
            Kd += 0.1;
            display.clearDisplay();
          }
          else if (digitalRead(PUSH2) != 1) {

            kabur = true;
            return;

          }
          delay(100);
        }
        break;
      }
    case 3: {
        return 0;
        break;
      }
  }

}

void pidMenu() {
  bool balik = false;
  int cursor = 1;
  int counter_press = 0;
  display.clearDisplay();

  while (balik != true) {
    display.display();
    display.setTextSize(1);
    display.setTextColor(WHITE);

    display.setCursor(20, 0);
    display.print("Kp = ");
    display.setCursor(60, 0);
    display.println(Kp);

    display.setCursor(20, 10);
    display.print("Kd = ");
    display.setCursor(60, 10);
    display.println(Kd);

    display.setCursor(60, 20);
    display.print("OK");
    //ganti cursor
    if (digitalRead(PUSH1) != 1) {
      cursor--;
      if (cursor < 1) {
        cursor = 1;
      }
      display.clearDisplay();
      //insert setCursor
      switch (cursor) {
        case 1: {
            display.setCursor(10, 0);
            display.print(">");
            break;
          }
        case 2: {
            display.setCursor(10, 10);
            display.print(">");
            break;
          }
        case 3: {
            display.setCursor(10, 20);
            display.print(">");
            break;
          }

          delay(100);

      }

    }
    else if (digitalRead(PUSH3) != 1) {
      cursor++;
      if (cursor > 3) {
        cursor = 1;
      }

      display.clearDisplay();
      //insert setCursor
      switch (cursor) {
        case 1: {
            display.setCursor(10, 0);
            display.print(">");
            break;
          }
        case 2: {
            display.setCursor(10, 10);
            display.print(">");
            break;
          }
        case 3: {
            display.setCursor(10, 20);
            display.print(">");
            break;
          }

      }

      delay(100);
    }

    //algoritma ke spesifik suatu menu
    if (digitalRead(PUSH2) != 1 && cursor != 3) {
      Serial.println("Case PUSH");
      spesifikMenu(cursor);
    }
    //escape mechanism
    else if (cursor == 3 && digitalRead(PUSH2) != 1) {
      balik = true;
    }

  }
  display.clearDisplay();
  return;
}

void pilihMenu(int menu) {
  switch (menu) {
    case 1: {
        menuCalibrate();
        tulisOLED("Callibrated..");
        delay(1500);
        display.clearDisplay();
        display.display();
        break;
      }
    case 2: {
        readtoROM(mid);
        tulisOLED("Sensor Loaded..");
        delay(1500);
        display.clearDisplay();
        display.display();
        break;
      }

    case 3: {
        pidMenu();
        break;
      }

  }
}
