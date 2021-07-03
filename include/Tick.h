//
// Created by tiger on 2021/7/2.
//

#ifndef SERIAL_TICK_H
#define SERIAL_TICK_H

#define MSPERTICK 10

class Tick{
private:
    int m_msPerTick;
    int m_currentTick;
    Tick(int msPerTick, int currentTick): m_currentTick(currentTick), m_msPerTick(msPerTick){;}
    static Tick* instance(){
        static Tick instance(MSPERTICK, 0);
        return &instance;
    }
public:
    static void tick(){++instance()->m_currentTick;}
    static int getTick(){return instance()->m_currentTick;}
    static int getMsPerTick(){return instance()->m_msPerTick;}

};


#endif //SERIAL_TICK_H
