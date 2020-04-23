/* 
 * File     : main.c
 * Author   : Moh. Tamamul Firdaus
 * Date     : 19 April 2020
 * Reference: Pak Waskita, https://github.com/waskita/embedded/tree/master/simulasi-filter-digital/simulasi-filter
 *            Konvolusi Praktikum PSD
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "math.h"
#include "koef_filter.h"

#define BUFFER_LENGTH 200

float buffer[KOEF_LENGTH]; 

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


int main(int argc, char** argv) {
    float waktu = 0;
    float sampling_rate = 10000; // frekuensi sampling
    float waktu_step;
    waktu_step = 1 / sampling_rate; // penambahan waktu tiap time step, sesuai frekuensi sampling
    char delim[] = ",";
    char data[BUFFER_LENGTH];
    int i;

    // inisialisasi buffer dengan nol
    for(i = 0; i < KOEF_LENGTH; i++) { 
        buffer[i] = 0;
    }

    char input_filename[] = "../anti-aliasing-out.csv"; //simulasi input filter
    char output_filename[] = "simulasi-filter.csv"; //simulasi output filter
    char dac_filename[] = "dac-output.txt"; // simulasi output DAC

    FILE *input_fp;
    FILE *output_fp;
    FILE *dac_fp;

    input_fp = fopen(input_filename, "r"); // file input filter
    output_fp = fopen(output_filename, "w"); // file output filter 
    dac_fp = fopen(dac_filename, "w"); // file output DAC

    fprintf(output_fp, "n,vin,lpf_out,adc_out,filter_out\n"); // menuis nama kolom file output filter
    
    if (input_fp != NULL && output_fp != NULL) { // kedua file harus dapat dibuka
        // membaca file input
        printf("read file %s ok\n", input_filename);
        fgets(data, BUFFER_LENGTH, input_fp); // buang baris pertama, karena isinya nama kolom file input
        while (fgets(data, BUFFER_LENGTH, input_fp) != NULL) {
            float output; // output filter sesaat
            int kolom_input = 0; // menandai angka itu di kolom_input berapa
            printf("%s\n", data);
            int angka_waktu; // waktu integer
            float angka_input, angka_output_lpf; // sinyal floating point

            char *ptr = strtok(data, delim);
            while (ptr != NULL) {
                int angka = 0;
                printf("%s\n", ptr);
                angka = atoi(ptr);
                printf("angka %d\n", angka);
                ptr = strtok(NULL, delim);
                if (kolom_input == 0) {
                    angka_waktu = angka;
                }
                if (kolom_input == 1) {
                    angka_input = angka / 32768.0;
                }
                if (kolom_input == 2) {
                    angka_output_lpf = angka / 32768.0;
                }
                kolom_input++;
            }
            float angka_output_adc = 0;
            float level_adc = 1024; // jumlah level ADC . 10 bit-> 1024, 8 bit->  256 
            // kuantisasi output ADC menjadi 12 bit (1024 level)
            // asumsi angka_output_lpf sudah dipetakan 0 sampai 1 volt (sesuai limit di LTSpice)
            // simulasi output ADC, dalam praktek bedanya kecil sekali (1/1024)
            angka_output_adc = (floor(angka_output_lpf * level_adc)) / level_adc;
            printf("waktu:%d vin:%f lpf_out:%f adc_out:%f\n"
                    , angka_waktu
                    , angka_input, angka_output_lpf, angka_output_adc);
            
            // memanggil fungsi filter 
            output = filter(angka_output_lpf); // hitung output filter digital
            printf("output %f\n", output);
            fprintf(output_fp, "%d,%f,%f,%f,%f\n"
                    , angka_waktu
                    , angka_input
                    , angka_output_lpf
                    , angka_output_adc
                    , output);
            // output DAC seharusnya dikuantisasi menjadi 12 level sesuai resolusi DAC, namun pada simulasi ini perbedaan kecil saja.
            // output DAC berupa anak tangga di bawah ini:
            for (i = 0; i < 10; i++) {
                fprintf(dac_fp, "%f,%f\n", waktu + waktu_step / 10 * i, output);
            }
            waktu += waktu_step;
        }
        //menutup file
        fclose(input_fp);
        fclose(output_fp);
        fclose(dac_fp);

    } else {
        printf("error read file %s\n", input_filename);
    }
    return (EXIT_SUCCESS);
}