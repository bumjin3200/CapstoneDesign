#define MODULE 4
const int sampleWindow = 50; // Sample window width in mS (50 mS = 20Hz)
unsigned int sample;

char impurse = 'i';
char sound = 's';

void setup() 
{
   Serial.begin(9600);
   Serial.println("");
}
 
 
void loop() 
{
   unsigned long startMillis= millis();  // Start of sample window
   unsigned int peakToPeak = 0;   // peak-to-peak level
 
   unsigned int signalMax = 0;
   unsigned int signalMin = 1024;
 
   // collect data for 50 mS
   while (millis() - startMillis < sampleWindow)
   {
      sample = analogRead(0);
      if (sample < 1024)  // toss out spurious readings
      {
         if (sample > signalMax)
         {
            signalMax = sample;  // save just the max levels
         }
         else if (sample < signalMin)
         {
            signalMin = sample;  // save just the min levels
         }
      }
   }
   peakToPeak = signalMax - signalMin;  // max - min = peak-peak amplitude
   double volts = (peakToPeak * 3.3) / 1024;  // convert to volts
  
   if(volts >=0){
      Serial.print(MODULE);
      Serial.print(sound);
      Serial.print("_");
      Serial.println(volts);
   }

     int val1;
     int val2;
     val1=analogRead(1);//Connect the sensor to analog pin 0
     val2=analogRead(2);
     if(val1>100)  //left
     {
      Serial.print(MODULE);
      Serial.print(impurse);
      Serial.print(1);
      Serial.print("_");
      Serial.println(val1,DEC);//
     }
     if(val2>100) //right
     {
      Serial.print(MODULE);
      Serial.print(impurse);
      Serial.print(2);
      Serial.print("_");
      Serial.println(val2,DEC);//
     }
      
}
