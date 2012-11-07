#include <SPI.h>
#include <Ethernet.h>
#include <HttpClient.h>
#include <Cosm.h>
#include "cosmConfig.h"

// The following variables are stored in the cosmConfig.h file which is not available on github
// byte mac[] = { 0x??, 0x??, 0x??, 0x??, 0x??, 0x?? };
// char cosmKey[] = "???????????????????????????????";

// Analog pin which we're monitoring (0 and 1 are used by the Ethernet shield)
int sensorPin = 4;

// Define the strings for our datastream IDs
char sensorId[] = "Voltage";
CosmDatastream datastreams[] = {
  CosmDatastream(sensorId, strlen(sensorId), DATASTREAM_FLOAT),
};
// Finally, wrap the datastreams into a feed
CosmFeed feed(82565, datastreams, 1 /* number of datastreams */);

EthernetClient client;
CosmClient cosmclient(client);



//Voltage divider values
double RVDA = 15000;
double RVDB = 2200;
double VDscale = RVDB / ( RVDA + RVDB );

//Current sensing circuit values
double Rsense = 0.0005;
double RA = 1000;
double RB = 470000;
//Calculate current scale value
double Iscale = RB / RA;

//Calculates volts per div of Arduino
float adc = 5/1024.0;

//Raw input
float val, cur1, cur2;
//Output variables
float Currentin,Currentout,Voltage,Power;

void setup()
{

  Serial.begin(9600);

  Serial.println("Starting single datastream upload to Cosm...");
  Serial.println();
  
  while (Ethernet.begin(mac) != 1)
  {
    Serial.println("Error getting IP address via DHCP, trying again...");
    delay(15000);
  }

}

void loop()
{
    double vSum = 0;
//    double cSum1 = 0;
    double cSum2 = 0;
    for (int x=0; x<15000; x++){
      vSum = vSum + analogRead(sensorPin);
//      cSum1 = cSum1 + analogRead(1);
      cSum2 = cSum2 + analogRead(2);

    }
    
    val = vSum/15000;
 //   cur1 = cSum1/1000;
 //   cur2 = cSum2/1000;
    
    //Voltage calculation
//    val = analogRead(0);
    Voltage = (val * adc)/VDscale;
    Serial.print("Voltage: ");
    Serial.println(Voltage);

    datastreams[0].setFloat(Voltage);
    Serial.print("Read sensor value ");
    Serial.println(datastreams[0].getFloat());
    
    Serial.println("Uploading it to Cosm");
    int ret = cosmclient.put(feed, cosmKey);
    Serial.print("cosmclient.put returned ");
    Serial.println(ret);
  
    Serial.println();
   

 //   Currentin = ((cur2*(5.06/1024.0))-2.53)/0.01;
 //    Serial.print("Current: ");
 //   Serial.println(Currentin);

    //Current 1 calculation
//    Currentin = (cur1 * adc)/(Iscale*Rsense);
//    Serial.print("Current in: ");
//    Serial.println(Currentin);

    //Current 2 calculation
//    Currentout = (cur2 * adc)/(Iscale*Rsense);
//    Serial.print("Current out: ");
//    Serial.println(Currentout);
//    Serial.println("");

    //Power calculation
//    Power = Voltage * Current;
    //Send down USB
//    Serial.print(Power);
//    Serial.print('D');


} 
