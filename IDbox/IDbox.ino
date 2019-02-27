#include <ESP8266WiFi.h> 
#include <FirebaseArduino.h> 
#include <SPI.h>
#include <MFRC522.h>
#include <virtuabotixRTC.h>  
#define FIREBASE_HOST "idbox-76d4e.firebaseio.com"
#define FIREBASE_AUTH "n2CdhEPc92uqSqPpitpORxrw75XdBhZy8ejos8Cs"
#define SS_PIN 4 
#define RST_PIN 5
const char* ssid = "Ary"; 
const char* password = "12345678"; 
MFRC522 mfrc522(SS_PIN, RST_PIN); 
virtuabotixRTC myRTC(D3, D4, D8);
void setup() {
  Serial.begin(9600);
 //myRTC.setDS1302Time(14, 10, 00, 1, 23, 02, 2019);
  pinMode(D0,OUTPUT);
  SPI.begin();
  mfrc522.PCD_Init();
  WiFi.begin(ssid, password);
  Serial.print("connecting");
    while (WiFi.status() != WL_CONNECTED) {
      Serial.print(".");
      delay(500);
    }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
  myRTC.updateTime(); 
   String ho, mi, se, di, mo, ye;
  if (myRTC.hours < 10){ho = "0"+(String)myRTC.hours;}else{ho = (String)myRTC.hours;}
  if (myRTC.minutes < 10){mi = "0"+((String)myRTC.minutes);}else{mi = (String)myRTC.minutes;}
  if (myRTC.seconds < 10){se = "0"+((String)myRTC.seconds);}else{se = (String)myRTC.seconds;}
  if (myRTC.dayofmonth < 10){di = "0"+(String)myRTC.dayofmonth;}else{di = (String)myRTC.dayofmonth;}
  if (myRTC.month < 10){mo = "0"+((String)myRTC.month);}else{mo = (String)myRTC.month;}
  if (myRTC.year < 10){ye = "0"+((String)myRTC.year);}else{ye = (String)myRTC.year;} 
   String t = ho+":"+mi+":"+se;
   String d = di+"/"+mo+"/"+ye;
   String da = ye+"/"+mo+"/"+di;
   
   if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.println();
  Serial.print(" UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
}
  content.toUpperCase();
  Serial.println();
  String url = "id/"+content.substring(1);
  String id = content.substring(1);
  digitalWrite(D0, HIGH);
  delay(200);
  digitalWrite(D0, LOW);
  delay(200);
 Firebase.setString("cod", id);
  if (Firebase.getString(url+"/a_Presente") == "Sim"){
    String nome = Firebase.getString(url+"/c_Nome");
    Serial.print(nome);
    String estado = "Saida";
    String data = t+" "+d;
    Firebase.setString(url+"/a_Presente", "Nao");
    Firebase.setString(url+"/f_Ultimo", d);
    Firebase.pushString("logs/"+nome+"/"+da, estado+" "+t);
    delay(3000);
    }else if (Firebase.getString(url+"/a_Presente") == "Nao"){
    String nome = Firebase.getString(url+"/c_Nome");
    Serial.print(nome);
    Firebase.setInt(url+"/e_Contagem", Firebase.getInt(url+"/e_Contagem")+1);
    String estado = "Entrada";
    String data = t+" "+d;
    Firebase.setString(url+"/a_Presente", "Sim");
    Firebase.setString(url+"/f_Ultimo", d);
    Firebase.pushString("logs/"+nome+"/"+da, estado+" "+t);
    delay(3000);
    }
}
