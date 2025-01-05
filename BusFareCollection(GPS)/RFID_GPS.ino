
//rfid gps

#include <SPI.h>
#include <MFRC522.h>
#include<Servo.h>
#include<SoftwareSerial.h>
#include <TinyGPS++.h>
TinyGPSPlus gps;
SoftwareSerial gpsSerial(6,7); //tx,rx
SoftwareSerial b(5,4); //tx , rx

//rfid SDA
#define SS_PIN 10

//rfid, MOSI-11,MISO-12,SCK-13
#define RST_PIN 9


Servo myservo;//declare servo

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance.

int declaredUID[4] = {0x36, 0x5E, 0x5D, 0x5A}; //[ game card ]    Declare the UID you want to compare.{83 B0 AE 1B blue tag} 
int declaredUID2[4] = {0xB2, 0x03, 0xEB, 0x4E}; //[white card]    Declare the UID you want to compare.
int balance = 2000; // Initial balance of parthasarathy
int balance2 = 200;//Initial balance of saran
double lat1,lon1,lat2,lon2,lat3,lon3,lat4,lon4;
double dis,dis1;


char p=1;
char q=1;

void setup() 
  { 
  Serial.begin(9600);  // Initialize serial communications.
  SPI.begin();      // Init SPI bus.
  gpsSerial.begin(9600);
  mfrc522.PCD_Init();   // Init MFRC522 card
  myservo.attach(3); // declare pin of servo
  myservo.write(0); // Initial position of the servo
  b.begin(9600);//initialize blutooth 
  Serial.println("SCAN YOUR CARD");  
  b.print("scan your card");
  }

void loop() 
{
  

if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) // scan new cards.  
  {    
    if (compareUID(mfrc522.uid.uidByte, declaredUID)) // Verify if the card's UID matches the declared UID.
      {
        if (balance>0)
        {
          if (p==1)
          { 
      
           myservo.write(90);
          Serial.println("\nRFID is valid!");
           b.print("\n\nRFID is valid\n");
          delay(2000);
          Serial.print("initial balance of parthasarathy:");
          Serial.println(balance);
          b.print("initial balance of parthasarathy:");
          b.print(balance); 
          Serial.print("******************initializing gps******************");
          b.print("\n******************initializing gps******************");
          myservo.write(0);
            p=0;
          getGPSData();
          Serial.print("\n");
       Serial.print("lattitude  ");
        Serial.print(lat1,6);
        Serial.print("\n");
        Serial.print("longitude  ");
         Serial.print(lon1,6);
         Serial.print("\n");
          b.print("\n");
          b.print("lattitude  ");
          b.print(lat1,6);
          b.print("\n");
           b.print("lattitude  ");
           b.print(lon1,6);
           b.print("\n");
        
          }
  else
   {
    myservo.write(90);
    Serial.print("\n******************initializing gps******************");
      b.print("\n******************initializing gps******************");
   
            getGPSData();
            Serial.print("\n");
           Serial.print("lattitude  ");
          Serial.print(lat2,6);
          Serial.print("\n");
           Serial.print("longitude  ");
         Serial.print(lon2,6);
         b.print("\n");
            b.print("lattitude  ");
          b.print(lat2,6);
          b.print("\n");
             b.print("lattitude  ");
           b.print(lon2,6);
         
             dis = calculateDistance(lat1,lon1,lat2,lon2);
             Serial.print("\ndistance  :");
           Serial.print(dis);
            b.print("\n distance  :");
           b.print(dis);
             float amount = (dis*0.7);
             Serial.print("\namount for the distance :");
           Serial.print(amount);
            b.print("\namount for the distance :");
           b.print(amount);
         delay (1000);
         balance = balance -amount; 
        Serial.print("\nbalance amount  :");
  
       Serial.print(balance);
       b.print("\nbalance amount  :");
  
      b.print(balance);
         Serial.print("\n");
          b.print("\n");
         myservo.write(0);
         p=1;
    }
 
  
  }}

else if (compareUID2(mfrc522.uid.uidByte, declaredUID2)) // Verify if the card's UID matches the declared UID.
      {
        if (balance>0)

        {
          if (q==1)
        
       
          { 
       
           myservo.write(90);
          Serial.println("\nRFID is valid!");
           b.print("\n\nRFID is valid\n");
          delay(2000);
          Serial.print("initial balance of saran:");
          Serial.println(balance2);
          b.print("initial balance of saran");
          b.print(balance2); 
          Serial.print("***************initializing gps*****************");
          b.print("\n******************initializing gps******************");
          myservo.write(0);
            q=0;

           getGPSData();
           Serial.print("\n");
           
           Serial.print("lattitude  ");
         Serial.print(lat3,6);
         Serial.print("\n");
          Serial.print("longitude   ");
         Serial.print(lon3,6);
         Serial.print("\n");
          b.print("\n");
             b.print("lattitude  ");
          b.print(lat3,6);
          b.print("\n");
             b.print("lattitude  ");
           b.print(lon3,6);
           b.print("\n");

   }

   else
   {
     myservo.write(90);
     Serial.print("\n******************initializing gps******************");
          b.print("\n******************initializing gps******************");
           getGPSData();
           Serial.print("\n");
           Serial.print("lattitude  ");
          Serial.print(lat4,6);
          Serial.print("\n");
           Serial.print("longitude  ");
         Serial.print(lon4,6);
         Serial.print("\n");
          b.print("\n");
             b.print("lattitude  ");
          b.print(lat4,6);
          b.print("\n");
             b.print("lattitude  ");
           b.print(lon4,6);
           
             dis1 = calculateDistance1(lat1,lon1,lat2,lon2);
             Serial.print("distance  :");
           Serial.print(dis1);
            b.print("\n distance  :");
           b.print(dis1); 
             float amount1 = (dis1*0.7);
             Serial.print("\namount for the distance  :");
           Serial.print(amount1);
           b.print("\namount for the distance  :");
           b.print(amount1);
         delay (1000);
         balance2 = balance2-amount1; 
        Serial.print("\nbalance amount  :");
  
       Serial.print(balance2);
       b.print("\nbalance amount  :");
  
       b.print(balance2);
          Serial.print("\n");
          b.print("\n");
          myservo.write(0);
          q=1;
   }
   
   }}
   else {

  Serial.println("card invalid");
  b.print("\ncard invalid\n");
  delay(1000);
}
   
  }





  
}

// Function to compare two arrays.
bool compareUID(byte array1[], int array2[]) {
  for (int i = 0; i < 4; i++) {
    if (array1[i] != array2[i]) {
      return false; // Arrays don't match.
    }
  }
  return true; // Arrays match.
}

// Function to compare two arrays.
bool compareUID2(byte array1[], int array2[]) {
  for (int i = 0; i < 4; i++) {
    if (array1[i] != array2[i]) {
      return false; // Arrays don't match.
    }
  }
  return true; // Arrays match.
}
const double EARTH_RADIUS_KM = 6371.0; // Earth's radius in kilometers


// Function to calculate the distance using the Haversine formula
double calculateDistance(double lat1, double lon1, double lat2, double lon2) {

  double dlat = (lat2 - lat1);
  double dlon = (lon2 - lon1);

  double a = sin(dlat / 2)*sin(dlat/2) + cos(lat1) * cos(lat2) *sin(dlon / 2)*sin(dlon / 2);

  double c = 2 * atan2(sqrt(a), sqrt(1 - a));
  
 double distance=EARTH_RADIUS_KM * c;
  double dis=(distance/18.5);
  
  return dis;
}

double calculateDistance1(double lat3, double lon3, double lat4, double lon4) {

  double dlat = (lat4 - lat3);
  double dlon = (lon4 - lon3);

  double a = sin(dlat / 2)*sin(dlat/2) + cos(lat3) * cos(lat4) *sin(dlon / 2)*sin(dlon / 2);

  double c = 2 * atan2(sqrt(a), sqrt(1 - a));
  
 double distance=EARTH_RADIUS_KM * c;
  double dis1=(distance/18.5);
  
  return dis1;
}

void getGPSData() {

     while (gpsSerial.available() > 0) {
      if (gps.encode(gpsSerial.read())) {
        if (gps.location.isValid()) {
           break;
           lat1=gps.location.lat();
           lon1=gps.location.lng();
           lat2=gps.location.lat();
           lon2=gps.location.lng();
           lat3=gps.location.lat();
           lon3=gps.location.lng();
           lat4=gps.location.lat();
           lon4=gps.location.lng();
           
        }
      }
    }
}
