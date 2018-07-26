void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  Serial.println();
  WiFi.begin("abcd","12345678");
  while(WiFi.status()!=WL_CONNECTED){
    delay(500);
    Serial.println(".");
  }
  Serial.print(WiFi.SSID());
  Serial.println("connected");
}
 
  //Global Variables
  int count1 = 5;
  int count2 = 10;
  int count3 = 20;
  int count4 = 7;
  int delayTotal = 0;
  int delayTime = 350;

  
void loop() {
  // put your main code here, to run repeatedly:
  count1++;
  count2++;
  count3++;
  count4++;

  delay(delayTime);
  delayTotal+=delayTime;
  if(delayTotal%6000 == 0)
  {
    delayTotal = 0;
    uploadData();
  }
}


void uploadData()
{

 WiFiClient client;
  if(client.connect(host,80)){
    Serial.println("connected");
    Serial.println("sending request");
    client.print(String("GET /update?key=")+key+"&field1="+String(count1)+"\r\n\r\n\r\n");  //sending analog value at gpio2 to field1 of thingspeak
    client.print(String("GET /update?key=")+key+"&field2="+String(count2)+"\r\n\r\n\r\n");
    client.print(String("GET /update?key=")+key+"&field3="+String(count3)+"\r\n\r\n\r\n");
    client.print(String("GET /update?key=")+key+"&field4="+String(count4)+"\r\n\r\n\r\n");
   
    Serial.println("response");
    while(client.connected()){
      if(client.available()){
        String line=client.readStringUntil('\n');         
        Serial.println(line);                      //response
      }
    }
    client.stop();                     //disconnect connection
    Serial.println("disconnected");
  }
 // delay(6000);
 
}

