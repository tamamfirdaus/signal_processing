#include "data.h"
#include "koef_filter.h"


#define BUFFER_LENGTH 200

float buffer[KOEF_LENGTH]; 
int i;


void setup() {
  // initialize serial communication at 115200 bits per second:
  Serial.begin(115200);

  // inisialisasi buffer dengan nol
  for(i = 0; i < KOEF_LENGTH; i++) { 
      buffer[i] = 0;
  }
}


/**
 * Filter dengan menggunakan koefisien filter FIR
 * @param input
 * @return hasil
 */ 
float filter(float input){
    int j;
    int k = 0;
    float hasil;
    //buffering
    for(j = KOEF_LENGTH - 1; j > 0; j--) {
        buffer[j] = buffer[j-1]; 
    }
    //input disimpan di buffer 0
    buffer[k] = input;
    // perhitungan filter
    hasil = 0;
    for(j = 0; j < KOEF_LENGTH; j++) {
        hasil = hasil + buffer[(j+k)%KOEF_LENGTH] * koef_filter[j]; 
    }
    k = (k+KOEF_LENGTH-1)%KOEF_LENGTH; 
    // kembalikan hasil pemfilteran
    return hasil;
}

void loop() {
  int counter = 0;  
  float output;
  int y;
  Serial.println("start");
  Serial.println("time,filter_in,filter_out");
  for (y = 0; y < BUFFER_LENGTH; y++) {
    float data = 0;
    data = (float)output_adc[y] / 1024.0;

    Serial.print(counter);
    Serial.print(",");
    Serial.print(data);
    Serial.print(",");

    output = filter(data); // hitung output filter digital
    Serial.print(output);
    Serial.println("");
    counter++;
  }

  while (1) {
    // halt di sini
  }
}
