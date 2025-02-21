#ifndef ENGINE_H
#define ENGINE_H

#include "Arduino.h"
#include "DynamixelShield.h"

using namespace ControlTableItem;

class Engine {
    public:
        Engine();
        void forward(int percent);
        void right(int percent);
        void left(int percent);
        void stop();
        void tick();
    private:
        uint8_t DXL_ID_L = 1;
        uint8_t DXL_ID_R = 2;
        float DXL_PROTOCOL_VERSION = 1.0;
        DynamixelShield dxl;
};

#endif