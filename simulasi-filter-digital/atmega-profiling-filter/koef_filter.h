#ifndef _KOEF_FILTER_
#define _KOEF_FILTER_

#define KOEF_LENGTH 34

// define Filter yang ingin digunakan
#define LPF_3K
// #define LPF_5K
// #define LPF_10K
// #define HPF_3K
// #define HPF_5K
// #define HPF_10K

#ifdef LPF_3K
    float koef_filter[KOEF_LENGTH] = {//LPF 3KHz
    
        0.0015,   0.0013,    0.0008,    -0.0006,   -0.0033,   -0.0073,   -0.0115,   -0.0141,   -0.0126,   -0.0045,   0.0117,

        0.0357,   0.0653,    0.0963,    0.1238,    0.1428,    0.1495,    0.1428,    0.1238,    0.0963,    0.0653,    0.0357,

        0.0117,   -0.0045,   -0.0126,   -0.0141,   -0.0115,   -0.0073,   -0.0033,   -0.0006,   0.0008,    0.0013,    0.0015

    };
#endif

#ifdef LPF_5K
    float koef_filter[KOEF_LENGTH] = {//LPF 5KHz
    
        -0.0000,   -0.0013,   -0.0026,   -0.0027,    0.0000,    0.0058,    0.0116,    0.0113,   -0.0000,   -0.0203,   -0.0381,

        -0.0359,    0.0000,    0.0694,    0.1539,    0.2236,    0.2506,    0.2236,    0.1539,    0.0694,    0.0000,   -0.0359,

        -0.0381,   -0.0203,   -0.0000,    0.0113,    0.0116,    0.0058,    0.0000,   -0.0027,   -0.0026,   -0.0013,   -0.0000
    
    };
#endif

#ifdef LPF_10K
    float koef_filter[KOEF_LENGTH] = {//LPF 10KHz 

        -0.0000,   -0.0019,    0.0000,    0.0039,   -0.0000,   -0.0082,    0.0000,    0.0159,   -0.0000,   -0.0287,    0.0000,

        0.0507,   -0.0000,   -0.0980,    0.0000,    0.3159,    0.5007,    0.3159,    0.0000,   -0.0980,   -0.0000,    0.0507,

        0.0000,   -0.0287,   -0.0000,    0.0159,    0.0000,   -0.0082,   -0.0000,    0.0039,    0.0000,   -0.0019,   -0.0000
    
    };
#endif

#ifdef HPF_3K
    float koef_filter[KOEF_LENGTH] = {//HPF 3KHz
    
        -0.0015,   -0.0013,   -0.0008,    0.0006,    0.0034,    0.0073,    0.0116,    0.0142,    0.0126,    0.0045,   -0.0118,

        -0.0359,   -0.0656,   -0.0968,   -0.1244,   -0.1435,    0.8513,   -0.1435,   -0.1244,   -0.0968,   -0.0656,   -0.0359,

        -0.0118,    0.0045,    0.0126,    0.0142,    0.0116,    0.0073,    0.0034,    0.0006,   -0.0008,   -0.0013,   -0.0015

    };
#endif

#ifdef HPF_5K
    float koef_filter[KOEF_LENGTH] = {//HPF 5KHz
    
        -0.0000,    0.0013,    0.0026,    0.0027,    -0.0000,   -0.0058,   -0.0116,   -0.0113,   -0.0000,    0.0203,    0.0380,

        0.0358,     -0.0000,   -0.0693,   -0.1537,   -0.2232,    0.7505,   -0.2232,   -0.1537,   -0.0693,   -0.0000,    0.0358,

        0.0380,     0.0203,    -0.0000,   -0.0113,   -0.0116,   -0.0058,   -0.0000,    0.0027,    0.0026,    0.0013,    -0.0000

    };
#endif

#ifdef HPF_10K
    float koef_filter[KOEF_LENGTH] = {//HPF 10KHz 

        -0.0000,    0.0019,   -0.0000,   -0.0039,   -0.0000,    0.0082,   -0.0000,   -0.0159,   -0.0000,    0.0287,   -0.0000,

        -0.0507,   -0.0000,    0.0980,   -0.0000,   -0.3159,    0.5007,   -0.3159,   -0.0000,    0.0980,   -0.0000,   -0.0507,

        -0.0000,    0.0287,   -0.0000,   -0.0159,   -0.0000,    0.0082,   -0.0000,   -0.0039,   -0.0000,    0.0019,   -0.0000

    };
#endif

#endif