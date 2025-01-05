
#include <SPI.h>
#include <MFRC522.h>
#include<Servo.h>
#include<SoftwareSerial.h>

//rfid SDA
#define SS_PIN 10

//rfid, MOSI-11,MISO-12,SCK-13
#define RST_PIN 9


Servo myservo;//declare servo
SoftwareSerial b(5,4); //tx , rx
MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance.

int declaredUID[4] = {0x36, 0x5E, 0x5D, 0x5A}; //[ game card ]    Declare the UID you want to compare.{83 B0 AE 1B blue tag} 
int declaredUID2[4] = {0xB2, 0x03, 0xEB, 0x4E}; //[white card]    Declare the UID you want to compare.
int balance = 2000; // Initial balance of parthasarathy
int balance2 = 200;//Initial balance of saran

char button1 = 2;
char button2 = 8;

void setup() 
  { 
  Serial.begin(9600);  // Initialize serial communications.
  SPI.begin();      // Init SPI bus.
  mfrc522.PCD_Init();   // Init MFRC522 card
  myservo.attach(3); // declare pin of servo
  myservo.write(0); // Initial position of the servo
  b.begin(9600);//initialize blutooth 
  Serial.println("SCAN YOUR CARD");  
  pinMode(button1,INPUT_PULLUP);
pinMode(button2,INPUT_PULLUP);
  }

void loop() 
{
    
     bool currentstate1=1;
     bool currentstate2=1;

  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) // scan new cards.  
  {    
    if (compareUID(mfrc522.uid.uidByte, declaredUID)) // Verify if the card's UID matches the declared UID.
      {
        if (balance>0)
       
          {
      
      myservo.write(90);
      Serial.println("\nRFID is valid!");
      b.print("\n\nRFID is valid\n");
      delay(2000);
      Serial.print("initial balance of parthasarathy:");
      Serial.println(balance);
      b.print("initial balance of parthasarathy:");
      b.print(balance); 
      
     while(currentstate1!=0&&currentstate2!=0)
      {
      currentstate1=digitalRead(button1);
      currentstate2=digitalRead(button2);
       }
       if (currentstate1==0)
       {
        balance-=50; 
        Serial.println("debiting 50 from the parthasarathy's balance");
      b.print("\ndebiting 50 from the parthasarathy's balance\n");
      delay(1000);
       }

      else if (currentstate2==0)
       {
         balance-=100;
         Serial.println("debiting 100 from the parthasarathy's balance");
      b.print("\ndebiting 100 from the parthasarathy's balance\n");
      delay(1000);
  
      }
      
      
      Serial.print("Current balance: ");
      Serial.println(balance);                             // Print the current balance.
      b.print("Current balance: ");
      b.println(balance); 
      myservo.write(0); 
      }
        else
      Serial.println("\ninsufficient balance");
   
      delay(1000);
    
      }
 
    else if (compareUID2(mfrc522.uid.uidByte, declaredUID2))  
    {
     if (balance2>0)
      {
      myservo.write(90);
      Serial.println("\nRFID is valid!");
      b.print("\n\nRFID is valid\n");
      delay(2000);
      Serial.print("initial balance of saran:");
      Serial.println(balance2);
      b.print("initial balance of saran:");
      b.print(balance2);

      while(currentstate1!=0&&currentstate2!=0)
      {
      currentstate1=digitalRead(button1);
      currentstate2=digitalRead(button2);
       }
       if (currentstate1==0)
       {
        balance2-=50; 
        Serial.println("debiting 50 from the saran's balance");
      b.print("\ndebiting 50 from the saran's balance\n");
      delay(1000);
       }

else if (currentstate2==0)
       {
        if (balance2>=100)
         {balance2-=100;
         Serial.println("debiting 100 from the saran's balance");
      b.print("\ndebiting 100 from the saran's balance\n");
      delay(1000);}
        else{
          Serial.print("insufficient balance");
           b.print("\ninsufficient balance\n");
          return;
          }
      }
     
      Serial.print("Current balance: ");
      Serial.println(balance2);                 
      b.print("Current balance: ");
      b.println(balance2);  
      myservo.write(0);
      }
      else
      Serial.println("\ninsufficient balance");
      delay(1000);
    
      }
      else 
      {
      Serial.println("\nRFID INVALID");
      b.print("\n\nRFID INVALID\n");
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
