#include <SPI.h>
#include <Ethernet.h>
#include <HttpClient.h>
#include <Cosm.h>
#include "cosmConfig.h"

// The following variables are stored in the cosmConfig.h file which is not available on github
// byte mac[] = { 0x??, 0x??, 0x??, 0x??, 0x??, 0x?? };
// char cosmKey[] = "???????????????????????????????";

// Analog pin which we're monitoring (0 and 1 are used by the sd card on the Ethernet shield)
int pin_V = 4;
int pin_I_in = 3;
int pin_I_out = 5;

//// Define the strings for our datastream IDs
char sensorId[] = "Voltage";
char sensorId2[] = "Current_In";
char sensorId3[] = "Current_Out";
char sensorId4[] = "Watts_net";

CosmDatastream datastreams[] = {
  CosmDatastream(sensorId, strlen(sensorId), DATASTREAM_FLOAT),
  CosmDatastream(sensorId2, strlen(sensorId), DATASTREAM_FLOAT),
  CosmDatastream(sensorId3, strlen(sensorId), DATASTREAM_FLOAT),
  CosmDatastream(sensorId4, strlen(sensorId), DATASTREAM_FLOAT),
};
// Finally, wrap the datastreams into a feed

CosmFeed feed(82565, datastreams, 4 /* number of datastreams */);

EthernetClient client;
CosmClient cosmclient(client);
	 
//Voltage divider values
double RVDA = 15000;
double RVDB = 2200;
double VDscale = RVDB / ( RVDA + RVDB );
	 
//Calculates volts per div of Arduino
float adc = 5/1024.0;
 
//Output variables
float I_in,I_out,Voltage,Watts_net;
double sum_V;
double sum_I_in;
double sum_I_out;
int cycles = 5000;	 

void setup()
{
  Serial.begin(9600);

  Serial.println("Starting datastream upload to Cosm...");
  Serial.println();
   
  while (Ethernet.begin(mac) != 1)
  {
    Serial.println("Error getting IP address via DHCP, trying again...");
    delay(5000);
  }	 
}
	 
void loop()
{

  Serial.println();  
    sum_V = 0;
    sum_I_in = 0;
    sum_I_out = 0;
    int x;
    for (x=0; x<cycles; x++){
      sum_V = sum_V + analogRead(pin_V);
    }
    delay(1000);
    for (x=0; x<cycles; x++){
      sum_I_out = sum_I_out + analogRead(pin_I_out);
    }   
    delay(1000);
    for (x=0; x<cycles; x++){
      sum_I_in = sum_I_in + analogRead(pin_I_in);
    }
 
   
   
    Voltage = ((sum_V/cycles) * adc)/VDscale;
    Serial.print("Voltage: ");
    Serial.println(Voltage);

    I_in = ((sum_I_in/cycles)*adc)*(200/5);
    Serial.print("Current_in: ");
    Serial.println(I_in);
        
    I_out = ((sum_I_out/cycles)*adc)*(200/5);
    Serial.print("Current_out: ");
    Serial.println(I_out);  
    
    Serial.print("Watts net: ");
    Watts_net = Voltage*I_in - Voltage*I_out;
    Serial.println(Watts_net);
    
    Serial.println();
    
    datastreams[0].setFloat(Voltage);
    datastreams[1].setFloat(I_in);
    datastreams[2].setFloat(I_out);
    datastreams[3].setFloat(Watts_net);
    
//    Serial.print("Read sensor value ");
//    Serial.println(datastreams[0].getFloat());
//    Serial.println(datastreams[1].getFloat());
//    Serial.println(datastreams[2].getFloat());
//    Serial.println(datastreams[3].getFloat());

    Serial.println("Uploading it to Cosm");
    int ret = cosmclient.put(feed, cosmKey);
    Serial.print("cosmclient.put returned ");
    Serial.println(ret);
    Serial.println();

    delay(2000);
} 
