
int batMonPin = 0;         // input pin for the divider
int val = 0;               // variable for the A/D value
float pinVoltage = 0;      // variable to hold the calculated voltage
float batteryVoltage = 0;
float ratio = 2.316;       // Change this to match the MEASURED ratio of the circuit

void setup() {
  
  Serial.begin(19200);      // open the serial port at 9600 baud
}

void loop() {  
  val = analogRead(batMonPin);            //  read the voltage on the divider  
  pinVoltage = val/(1023*5);              //  There are 1023 possible values between 0 and 5                                 
  batteryVoltage = pinVoltage * ratio;     
  
  Serial.print("Voltage: ");
  Serial.println(batteryVoltage);
  
  
  delay(1000);                  //  Slow it down
}
