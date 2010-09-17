/* 
 * File:   FrameCounter.h
 * Author: batas2
 *
 * Created on 29 kwiecień 2010, 12:29
 */

#ifndef _FRAMECOUNTER_H
#define	_FRAMECOUNTER_H

class FrameCounter {
private:

public:
    static int Frame;
    static bool Stop;

    void Inc();
    int Value();

    void CounterStop();
    bool Stoped();
};



#endif	/* _FRAMECOUNTER_H */

