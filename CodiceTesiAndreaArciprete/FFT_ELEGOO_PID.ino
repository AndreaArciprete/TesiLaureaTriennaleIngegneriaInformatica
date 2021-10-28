//SLAVE
#include <Wire.h> //Protocollo I2C
#include <arduinoFFT.h>
#define SAMPLES 128             //Must be a power of 2
#define SAMPLING_FREQUENCY 2500 //Hz, must be less than 10000 due to ADC
 
arduinoFFT FFT0 = arduinoFFT();
arduinoFFT FFT1 = arduinoFFT(); 
arduinoFFT FFT2 = arduinoFFT();

double x0; //frequenza fondamentale
double v0; //ampiezza alla frequenza fondamentale
double x1; //frequenza fondamentale
double v1; //ampiezza alla frequenza fondamentale
double x2; //frequenza fondamentale
double v2; //ampiezza alla frequenza fondamentale
unsigned int sampling_period_us;
unsigned long microseconds;
double errore;
int ritardo;
char ritardo_string[2];
char t[4] = {};
char temp[] = {};
double vReal0[SAMPLES];
double vImag0[SAMPLES];
double vReal1[SAMPLES];
double vImag1[SAMPLES];
double vReal2[SAMPLES];
double vImag2[SAMPLES];
void setup() {
    sampling_period_us = round(1000000*(1.0/SAMPLING_FREQUENCY));
    Serial.begin(115200);
    Wire.begin(3); //L'indirizzo assegnato all'Arduino slave è 3
    Wire.onRequest(InviaAmpiezze);
}

void loop(){
    for(int i=0; i<SAMPLES; i++)
    {
        microseconds = micros();    //Overflows after around 70 minutes!
        vReal0[i] = analogRead(0);;
        vImag0[i] = 0;
        vReal1[i] = analogRead(1);
        vImag1[i] = 0;
        vReal2[i] = analogRead(2);
        vImag2[i] = 0;
     
        while(micros() < (microseconds + sampling_period_us)){
        }
    }
 
    /*FFT*/
    FFT0.Windowing(vReal0, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    FFT0.Compute(vReal0, vImag0, SAMPLES, FFT_FORWARD);
    FFT0.ComplexToMagnitude(vReal0, vImag0, SAMPLES);
    FFT0.DCremoval(vReal0);
    FFT0.MajorPeak(vReal0, SAMPLES, SAMPLING_FREQUENCY, &x0, &v0); //frequenza fondamentale
    FFT0.BandPassFilter(vReal0,SAMPLES, SAMPLING_FREQUENCY,970, 1100,x0,&v0);

    FFT1.Windowing(vReal1, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    FFT1.Compute(vReal1, vImag1, SAMPLES, FFT_FORWARD);
    FFT1.ComplexToMagnitude(vReal1, vImag1, SAMPLES);
    FFT1.DCremoval(vReal1);
 
    FFT1.MajorPeak(vReal1, SAMPLES, SAMPLING_FREQUENCY, &x1, &v1); //frequenza fondamentale
    FFT1.BandPassFilter(vReal1,SAMPLES, SAMPLING_FREQUENCY,970, 1100,x1,&v1);

    FFT2.Windowing(vReal2, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    FFT2.Compute(vReal2, vImag2, SAMPLES, FFT_FORWARD);
    FFT2.ComplexToMagnitude(vReal2, vImag2, SAMPLES);
    FFT2.DCremoval(vReal2);
    
    FFT2.MajorPeak(vReal2, SAMPLES, SAMPLING_FREQUENCY, &x2, &v2); //frequenza fondamentale
    FFT2.BandPassFilter(vReal2,SAMPLES, SAMPLING_FREQUENCY,970, 1100,x2,&v2);

    errore = abs(v1-v0);
    errore = constrain(errore,1000,5000);
    //Serial.print(v0);
    //Serial.print(" ");
    //Serial.println(v1);
    //Serial.println(errore);
}

void InviaAmpiezze(){
if (v0 == 0 && v1 == 0 && v2 == 0){
t[2] = 'd';
}
else{
  t[2] = 'c';
}
if (v1 < v0){
  t[0] = 's';
}
else {
  t[0]= 'n';
}
if (v2 > v1 && v2 > v0){
  t[1]= 'a';
}
else{
  t[1] = 'b';
}

if (errore > 3000) {
t[3] = '5';
t[4] = ' ';
}
else{
t[3] = '2';
t[4] = '0';
}
//Serial.println(t[3]);
strncpy(temp,t,5); 
Wire.write(temp);  
}
