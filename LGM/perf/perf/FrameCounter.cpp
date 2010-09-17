/* 
 * File:   FrameCounter.cpp
 * Author: batas2
 * 
 * Created on 29 kwiecień 2010, 12:29
 */

#include "FrameCounter.h"

int FrameCounter::Frame = 0;
bool FrameCounter::Stop = false;

void FrameCounter::Inc() {
    Frame++;
}

int FrameCounter::Value() {
    return Frame;
}

void FrameCounter::CounterStop() {
    Stop = true;
}

bool FrameCounter::Stoped() {
    return Stop;
}

