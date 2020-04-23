% File Name : filter_lpf_3khz
% Author    : Moh. Tamamul Firdaus
% Date      : 21 April 2020

clear all;
n = 32; %orde filter
fs = 40000; %frekuensi sampling
fc = 5000; %frekuensi cut-off
Wn = fc/(fs/2);
b = fir1(n,Wn,'low'); %perhitungan koefisien filter dengan FIR
freqz(b); %plot Magnitude dan Phase
