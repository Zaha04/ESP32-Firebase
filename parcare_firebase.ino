
#include <WiFi.h>
#include "FirebaseESP32.h"

const int echoPin= 5 ;// attach pin D2 Arduino to pin Echo of HC-SR04
const int trigPin= 2; //attach pin D3 Arduino to pin Trig of HC-SR04
const int echopin2=35;
const int trigpin2=34;

// defines variables
long duration; // variable for the duration of sound wave travel
long duration2;
int distance2;
int distance; // variable for the distance measurement


#define FIREBASE_HOST "YOUR_HOST"      // Project name address from firebase id

#define WIFI_PASSWORD "YOUR_PASSWORD" 
const int rosu1=33;
const int verde1=23;
const int rosu2=17;
const int verde2=18;
String o="ocupat";
#define FIREBASE_AUTH "SECRET_KEY"            //  Secret key generated from firebase

String title="Loc1";
String title2="Loc2";

#define WIFI_SSID "WI_FI_SSID"                                     // Enter your wifi name

String l="liber";
FirebaseData firebasedata; 
void setup() {
     Serial.begin(115200);

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
   pinMode(trigpin2, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echopin2, INPUT);
   // // Serial Communication is starting with 9600 of baudrate speed
  Serial.println("Ultrasonic Sensor HC-SR04 Test"); // print some text in Serial Monitor
  Serial.println("with Arduino UNO R3");
  
  delay(4000);                
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                                     //try to connect with wifi
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(4000);
  }
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Serial.print("IP Address is : ");
  Serial.println(WiFi.localIP());                                            //print local IP address
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);                              // connect to firebase


pinMode(rosu1,OUTPUT);
pinMode(verde1,OUTPUT);
pinMode(rosu2,OUTPUT);
pinMode(verde2,OUTPUT);
}
void loop() {
  // Clears the trigPin condition
  Firebase.setString(firebasedata,"/PARCARE1/loc1/title",title);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  if(distance<10){
    digitalWrite(rosu1,HIGH);
    digitalWrite(verde1,LOW);
    Firebase.setString(firebasedata,"/PARCARE1/loc1/status",o);
    delay(4000);
  }
  else{
    digitalWrite(verde1,HIGH);
    digitalWrite(rosu1,LOW);
    Firebase.setString(firebasedata,"/PARCARE1/loc1/status",l);
    delay(4000);
  }
   Firebase.setString(firebasedata,"/PARCARE1/loc2/title",title2);
  digitalWrite(trigpin2, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigpin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin2, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echopin2, HIGH);
  // Calculating the distance
  distance2 = duration2 * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance2);
  Serial.println(" cm");
  if(distance2<10){
    digitalWrite(rosu2,HIGH);
    digitalWrite(verde2,LOW);
    Firebase.setString(firebasedata,"/PARCARE1/loc2/status",o);
    delay(4000);
  }
  else{
    digitalWrite(verde2,HIGH);
    digitalWrite(rosu2,LOW);
    Firebase.setString(firebasedata,"/PARCARE1/loc2/status",l);
    delay(4000);
  }
  
  
}
