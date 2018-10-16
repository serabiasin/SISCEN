  int Kp = 1.2;
  int Sp = 0;
  int MAXPWM = 150;
  int MINPWM = 0;
  float intervalPWM = (MAXPWM - MINPWM) / 8;
  int PV;
  
  #define enA 3
  #define in1 5
  #define in2 7
  #define enB 13
  #define in3 9
  #define in4 11
  
  int s1=A14;
  int s2=A12;
  int s3=A10;
  int s4=A8;
  int s5=A6;
  int s6=A4;
  int s7=A2;
  int s8=A0;
  
  
  int lPWM;
  int rPWM; //87%dari speed motor B
  
  int kondisi;
  int m;
  int lp=0;
  int lp2=0;
  int sen[8];
  int awl[8];
  int pth[8];
  int htm[8];
  int mid[8];
  String val;
  
  void jalankenMotor();
  
  void setup() {
  
  
    pinMode(s1,INPUT);
    pinMode(s2,INPUT);
    pinMode(s3,INPUT);
    pinMode(s4,INPUT);
    pinMode(s5,INPUT);
    pinMode(s6,INPUT);
    pinMode(s7,INPUT);
    pinMode(s8,INPUT);
    //pinMode(s9,INPUT);
   // pinMode(s10,INPUT);
    Serial.begin(9600);
            
              do
              {
                sen[0]=analogRead(s1);
                sen[1]=analogRead(s2);
                sen[2]=analogRead(s3);
                sen[3]=analogRead(s4);
                sen[4]=analogRead(s5);
                sen[5]=analogRead(s6);
                sen[6]=analogRead(s7);
                sen[7]=analogRead(s8);
                //sen[8]=analogRead(s9);
                //sen[9]=analogRead(s10);
                  if(lp<8)
                  {
                    //====================================================
                    for (int i=0;i<8;i++)
                    {
                      pth[i]=sen[i];
                      Serial.print(pth[i]);
                      Serial.print("[");
                      Serial.print(i);
                      Serial.print("]");
                      Serial.print(",");
                    }
                    Serial.println("PUTIH AWAL");
                    //====================================================
                    for (int i=0;i<8;i++)
                    {
                      htm[i]=sen[i];
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
                    for(int i=0;i<8;i++)
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
                    for(int i=0;i<8;i++)
                    {
                      if(sen[i]<pth[i])
                      {
                        pth[i]=sen[i];
                      }
                      else if(sen[i]>pth[i])
                      {
                        pth[i]=pth[i];
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
                    for(int i=0;i<8;i++)
                    {
                      if(sen[i]>htm[i])
                      {
                        htm[i]=sen[i];
                      }
                      else if(sen[i]<htm[i])
                      {
                        htm[i]=htm[i];
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
                    for(int i=0;i<8;i++)
                    {
                      mid[i]=((htm[i]-pth[i])/2)+pth[i];
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
              while(lp2<=30);
  }
  
  void loop() {
      sen[0]=analogRead(s1);
      sen[1]=analogRead(s2);
      sen[2]=analogRead(s3);
      sen[3]=analogRead(s4);
      sen[4]=analogRead(s5);
      sen[5]=analogRead(s6);
      sen[6]=analogRead(s7);
      sen[7]=analogRead(s8);
   //   sen[8]=analogRead(s9);
   //   sen[9]=analogRead(s10);
  
      //===================================================================
      //KONVERSI TO STRING
      //===================================================================
      for(int i=0;i<8;i++)
      {
        if(sen[i]<mid[i])
        {
          sen[i]=1;
        }
        else if(sen[i]>=mid[i])
        {
          sen[i]=0;
        }
        if(i==0){
          val= String(sen[i]);
        }
        else{
          val+= String(sen[i]);
        }
      }
    //  Serial.println(val);
  
      //===================================================================
      //PENGKONDISIAN
      //===================================================================
   /*        if(val=="0111111111"){kondisi=1;}
      else if(val=="0011111111"){kondisi=2;}
      else if(val=="1011111111"){kondisi=3;}
      else if(val=="1001111111"){kondisi=4;}
      else if(val=="1101111111"){kondisi=5;}
      else if(val=="1100111111"){kondisi=6;}
      else if(val=="1110111111"){kondisi=7;}
      else if(val=="1110011111"){kondisi=8;}
      else if(val=="1111011111"){kondisi=9;}
      else if(val=="1111001111"){kondisi=10;}
      else if(val=="1111101111"){kondisi=11;}
      else if(val=="1111100111"){kondisi=12;}
      else if(val=="1111110111"){kondisi=13;}
      else if(val=="1111110011"){kondisi=14;}
      else if(val=="1111111011"){kondisi=15;}
      else if(val=="1111111001"){kondisi=16;}
      else if(val=="1111111101"){kondisi=17;}
      else if(val=="1111111100"){kondisi=18;}
      else if(val=="1111111110"){kondisi=19;}
      else if(val=="1111111111"){kondisi=20;}
      else {kondisi=10;}*/
     // Serial.println(kondisi);
  
  
    
    if (val == "11111110") { //sensor paling kiri
      PV= -7;
      m=1;
    }
    if (val == "11111000" or val == "11111100")   {
      PV =  -6;
      m=1;
    }
    if (val == "11111101") {
      PV= -5;
      m=1;
    }
    if (val == "11110001" or val == "11111001" ) {
      PV= -4;
      m=1;
    }
    if (val == "11111011") {
      PV= -3;
      m=1;
    }
    if (val == "11100011" or val == "11110011") {
      PV= -2;
      m=1;
    }
    if (val == "11110111") {
      PV= -1;
      m=1;
    }
    if (val == "11100111") {
      // tengah
      PV= 0;
    }
    if (val == "11101111") {
      PV= 1;
      m=2;
    }
    if (val == "11000111" or val == "11001111") {
      PV= 2;
      m=2;
    }
    if (val == "11011111") {
      PV= 3;
      m=2;
    } 
    if (val == "10001111" or val == "10011111") {
      PV= 4;
      m=2;
    }
    if (val == "10111111") {
      PV= 5;
      m=2;
    }
    if (val == "00011111" or val == "00111111") {
      PV= 6;
      m=2;
    }
    if (val == "01111111") {
      // ujung kanan
      PV= 7  ;
      m=2;
    }
    if (val == "11111111" or val == "00000000" ) {
      // loss
      PV = PV;
    }
  
      
      
      
  
   /*   //=============================================================
      //GERAKAN MOTOR
      //=============================================================
      if (PV==-7){analogWrite(enB,spB*0.8);
                      analogWrite(enA,spA*0);
                      digitalWrite(in1,LOW); digitalWrite(in2,HIGH); digitalWrite(in3,LOW); digitalWrite(in4,HIGH);
                      m=1;}
      //============================================================================================================
      else if (kondisi==-6){analogWrite(enB,spB*0.7);
                      analogWrite(enA,spA*0.15);
                      digitalWrite(in1,LOW); digitalWrite(in2,HIGH); digitalWrite(in3,LOW); digitalWrite(in4,HIGH);
                      m=1;}
      //============================================================================================================
      else if (kondisi==-5){analogWrite(enB,spB*0.7);
                      analogWrite(enA,spA*0.15);
                      digitalWrite(in1,LOW); digitalWrite(in2,HIGH); digitalWrite(in3,LOW); digitalWrite(in4,HIGH);
                      m=1;}
      //============================================================================================================
      else if (kondisi==-4){analogWrite(enB,spB*0.7);
                      analogWrite(enA,spA*0.20);
                      digitalWrite(in1,LOW); digitalWrite(in2,HIGH); digitalWrite(in3,LOW); digitalWrite(in4,HIGH);
                      m=1;}
      //============================================================================================================
      else if (kondisi==-3){analogWrite(enB,spB*0.7);
                      analogWrite(enA,spA*0.20);
                      digitalWrite(in1,LOW); digitalWrite(in2,HIGH); digitalWrite(in3,LOW); digitalWrite(in4,HIGH);
                      m=1;}
      //============================================================================================================
      else if (kondisi==-2){analogWrite(enB,spB*0.7);
                      analogWrite(enA,spA*0.30);
                      digitalWrite(in1,LOW); digitalWrite(in2,HIGH); digitalWrite(in3,LOW); digitalWrite(in4,HIGH);
                      m=1;}
      //============================================================================================================
      else if (kondisi==-1){analogWrite(enB,spB);
                      analogWrite(enA,spA*0.8);
                      digitalWrite(in1,LOW); digitalWrite(in2,HIGH); digitalWrite(in3,LOW); digitalWrite(in4,HIGH);
                      m=1;}
      //============================================================================================================
      else if (kondisi==0){analogWrite(enB,spB);
                      analogWrite(enA,spA);
                      digitalWrite(in1,LOW); digitalWrite(in2,HIGH); digitalWrite(in3,LOW); digitalWrite(in4,HIGH);
      }
      //============================================================================================================
      else if (kondisi==1){analogWrite(enB,spB*0.7);
                      analogWrite(enA,spA*0.9);
                      digitalWrite(in1,LOW); digitalWrite(in2,HIGH); digitalWrite(in3,LOW); digitalWrite(in4,HIGH);
                      m=1;}
      //============================================================================================================
      //CENTER>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
      else if (kondisi==2){analogWrite(enB,spB*0.3);
                      analogWrite(enA,spA*0.7);
                      digitalWrite(in1,LOW); digitalWrite(in2,HIGH); digitalWrite(in3,LOW); digitalWrite(in4,HIGH);}
      //CENTER>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
      //============================================================================================================
      else if (kondisi==3){analogWrite(enB,spB*0.3);
                      analogWrite(enA,spA*0.7);
                      digitalWrite(in1,LOW); digitalWrite(in2,HIGH); digitalWrite(in3,LOW); digitalWrite(in4,HIGH);;
                      m=2;}
      //============================================================================================================
      else if (kondisi==4){analogWrite(enB,spB*0.25);
                      analogWrite(enA,spA*0.7);
                      digitalWrite(in1,LOW); digitalWrite(in2,HIGH); digitalWrite(in3,LOW); digitalWrite(in4,HIGH);;
                      m=2;}
      //============================================================================================================
      else if (kondisi==5){analogWrite(enB,spB*0.20);
                      analogWrite(enA,spA*0.8);
                      digitalWrite(in1,LOW); digitalWrite(in2,HIGH); digitalWrite(in3,LOW); digitalWrite(in4,HIGH);
                      m=2;}
      //============================================================================================================
      else if (kondisi==6){analogWrite(enB,spB*0.15);
                      analogWrite(enA,spA*0.8);
                      digitalWrite(in1,LOW); digitalWrite(in2,HIGH); digitalWrite(in3,LOW); digitalWrite(in4,HIGH);
                      m=2;}
      //============================================================================================================
      else if (kondisi==7){analogWrite(enB,spB*0.10);
                      analogWrite(enA,spA*0.8);
                      digitalWrite(in1,LOW); digitalWrite(in2,HIGH); digitalWrite(in3,LOW); digitalWrite(in4,HIGH);
                      m=2;}
  */
      //============================================================================================================
      //>>>>>>>MEMORY<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  
  
  int error = Sp - PV;
  int P = Kp * error;
  
  
  
  int MV = P;
  
       /**     if (  PV==8){
              if(m==1){
                            PV= -7;
                       }
              else if(m==2){
                            PV= 7;
                      }
                      }*/
                      
          if (MV == 0) { //lurus, maju cepat
              lPWM = MAXPWM;
              rPWM = MAXPWM;
          } else if (MV > 0) { // alihkan ke kiri
              rPWM = MAXPWM - ((intervalPWM - 20) * MV);
              lPWM = (MAXPWM - (intervalPWM * MV) - 15);
  
          } else if (MV < 0) { // alihkan ke kanan
              lPWM = MAXPWM+( ( intervalPWM - 20 ) * MV);
              rPWM = MAXPWM+( ( intervalPWM * MV ) - 15 );
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
  
  
  void jalankenMotor(){
  
  
       rPWM=abs(rPWM);
      lPWM=abs(lPWM);
    
    
    //Jalan Motor Kiri
    analogWrite(enA, lPWM);
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
  
    analogWrite(enB, rPWM);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
  
   
    }
