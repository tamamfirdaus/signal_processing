#include "koef_filter.h"

float buffer[KOEF_LENGTH]; 
int i;

void setup() {
  // initialize serial communication at 9600 bits per second:
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
  float data = 0;
  float output;
  // pengukuran waktu
  unsigned long waktu_awal = millis();
  unsigned long y = 0;
  data = 1.0;
  Serial.println("start");
  for (y = 0; y < 1000000L; y++) {
    data = data + 1.0; // data mesti diubah terus, supaya tidak dioptimize oleh compiler
    data = (data+ output)/2; // supaya output tidak dioptimize
    
    output = filter(data); // hitung output filter digital
  }
  unsigned long waktu_akhir = millis();
  Serial.println(output); // output mesti dipakai, supaya tidak dioptimize oleh compiler
  Serial.print("waktu awal:");
  Serial.println(waktu_awal);
  Serial.print("waktu akhir:");
  Serial.println(waktu_akhir);
  Serial.print("beda waktu:");
  Serial.println(waktu_akhir - waktu_awal);


  while (1) {
    // halt di sini
  }
}
