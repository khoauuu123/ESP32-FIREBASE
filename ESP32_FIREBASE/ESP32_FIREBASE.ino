#include "WiFi.h"
const char* ssid = "Khoa";
const char* password = "10121999";

#include "FirebaseESP32.h"
#define FIREBASE_AUTH ""
#define FIREBASE_HOST ""
FirebaseData firebaseData;
String path = "/";
void initFirebase() {
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  if (!Firebase.beginStream(firebaseData, path))
  {
    Serial.println("REASON: " + firebaseData.errorReason());
    Serial.println();
  }
  Serial.println("Kết nối Firebase thành công");
}

void setup() {
  Serial.begin(115200);
  delay(200);
  Serial.println();
  Serial.print("Connecting to wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  initFirebase(); // Kêt nối Firebase
}

void loop() {
  // set data
  int so = random(0, 99);
  if (Firebase.setString(firebaseData, "/set", String(so))) {
    Serial.println("set: " + String(so));
  }

  // get data
  if (Firebase.getString(firebaseData, "/get")) {
    String s = firebaseData.stringData();
    Serial.println("get: " + s);
  }
}
