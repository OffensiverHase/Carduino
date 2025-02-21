#include <Engine.h>

Engine::Engine() {
    this->dxl.begin(1000000);
    this->dxl.setPortProtocolVersion(DXL_PROTOCOL_VERSION);
    
    this->dxl.ping(DXL_ID_L);
    this->dxl.ping(DXL_ID_R);

    // Turn off torque when configuring items in EEPROM area
    this->dxl.torqueOff(DXL_ID_L);
    this->dxl.setOperatingMode(DXL_ID_L, OP_VELOCITY);
    this->dxl.torqueOn(DXL_ID_L);

    this->dxl.torqueOff(DXL_ID_R);
    this->dxl.setOperatingMode(DXL_ID_R, OP_VELOCITY);
    this->dxl.torqueOn(DXL_ID_R);

    this->stop();
}

void Engine::forward(int percent) {
    this->dxl.setGoalVelocity(DXL_ID_R, percent, UNIT_PERCENT);
    this->dxl.setGoalVelocity(DXL_ID_L, percent - 100, UNIT_PERCENT);
}

void Engine::right(int percent) {
    this->dxl.setGoalVelocity(DXL_ID_R, percent - 100, UNIT_PERCENT);
    this->dxl.setGoalVelocity(DXL_ID_L, percent, UNIT_PERCENT);
}

void Engine::left(int percent) {
    this->dxl.setGoalVelocity(DXL_ID_R, percent, UNIT_PERCENT);
    this->dxl.setGoalVelocity(DXL_ID_L, percent - 100, UNIT_PERCENT);
}

void Engine::stop() {
    this->dxl.setGoalVelocity(DXL_ID_R, 0);
    this->dxl.setGoalVelocity(DXL_ID_L, 0);
}

void Engine::tick() {
    // todo PID?
}