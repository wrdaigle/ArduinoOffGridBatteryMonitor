
//Voltage divider values
double RVDA = 99000;
double RVDB = 14700;
double VDscale = RVDB / ( RVDA + RVDB );

//Current sensing circuit values
//double Rsense = 0.0005;
//double RA = 1000;
//double RB = 470K;
//Calculate current scale value
//double Iscale = RB / RA;

//Calculates volts per div of Arduino
float adc = 5/1024.0;

//Raw input
float val;
//Output variables
float Currentin,Currentout,Voltage,Power;

void setup()
{

    Serial.begin(19600);

}

void loop()
{
    double valSum = 0;
    for (int x=0; x<100; x++){
      valSum = valSum + analogRead(1);
    }
    
    val = valSum/100;
  
    //Voltage calculation
//    val = analogRead(0);
    Voltage = (val * adc);
    
    
    //Send down USB
    Serial.print(Voltage);
    Serial.println('V at pin');
    Voltage = (val * adc)/VDscale;
    Serial.print(Voltage);
    Serial.println('V');

    //Current calculation
//    val = analogRead(1);
//    Currentin = (val * adc)/(Iscale*Rsense);
    //Send down USB
//    Serial.print(Currentin);
//    Serial.print('B');

        //Current calculation

//    val = analogRead(2);
//    Currentout = (val * adc)/(Iscale*Rsense);
    //Send down USB
//    Serial.print(Currentout);
//    Serial.print('C');

    //Power calculation
//    Power = Voltage * Current;
    //Send down USB
//    Serial.print(Power);
//    Serial.print('D');

    delay(1000);
} 
