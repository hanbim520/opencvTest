//
//  SpeekRecognition.hpp
//  opencvTest
//
//  Created by abc on 03/04/2017.
//  Copyright © 2017 abc. All rights reserved.
//

#ifndef SpeekRecognition_hpp
#define SpeekRecognition_hpp

#include <stdio.h>
#include <memory>
#include <iostream>
#include "portaudio.h"

using namespace std;

/* #define SAMPLE_RATE  (17932) // Test failure to open with this value. */
#define SAMPLE_RATE  (44100)
#define FRAMES_PER_BUFFER (512)
#define NUM_SECONDS     (5)
#define NUM_CHANNELS    (2)
/* #define DITHER_FLAG     (paDitherOff) */
#define DITHER_FLAG     (0) /**/
/** Set to 1 if you want to capture the recording to a file. */
#define WRITE_TO_FILE   (0)

/* Select sample format. */
#if 1
#define PA_SAMPLE_TYPE  paFloat32
typedef float SAMPLE;
#define SAMPLE_SILENCE  (0.0f)
#define PRINTF_S_FORMAT "%.8f"
#elif 1
#define PA_SAMPLE_TYPE  paInt16
typedef short SAMPLE;
#define SAMPLE_SILENCE  (0)
#define PRINTF_S_FORMAT "%d"
#elif 0
#define PA_SAMPLE_TYPE  paInt8
typedef char SAMPLE;
#define SAMPLE_SILENCE  (0)
#define PRINTF_S_FORMAT "%d"
#else
#define PA_SAMPLE_TYPE  paUInt8
typedef unsigned char SAMPLE;
#define SAMPLE_SILENCE  (128)
#define PRINTF_S_FORMAT "%d"
#endif


typedef struct
{
    int          frameIndex;  /* Index into sample array. */
    int          maxFrameIndex;
    SAMPLE      *recordedSamples;
}
paTestData;

class SpeekRecognition
{
public:
    SpeekRecognition();
    ~SpeekRecognition();
    
    
public:
    bool InitSpeek(int deviceIdx = 0);
    void StartSpeek();
    
    void CloseSpeek();
    
    void TerminalSpeek();
    
private:
    int deviceIdx;
    
    PaStreamParameters  inputParameters,
    outputParameters;
    PaStream*           stream;
    PaError             err = paNoError;
    paTestData          data;
    int                 i;
    int                 totalFrames;
    int                 numSamples;
    int                 numBytes;
    SAMPLE              max, val;
    double              average;
    
};


#endif /* SpeekRecognition_hpp */
