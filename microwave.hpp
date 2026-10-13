#ifndef MICROWAVE_HPP
#define MICROWAVE_HPP

const int GRILL_POWER = 1000;
const int MIN_TIMER = 10;
const int MAX_TIMER = 3600;
const int DEFAULT_MICRO_POWER = 800;

enum OvenMode { MODE_MICROWAVE, MODE_GRILL };

const char* const OvenModeName[2] = { "MICROWAVE", "GRILL" };

class MicrowaveOven {
    bool Power;
    int MicroPower;
    int Timer;
    int Mode;
    bool Emitter;
    bool Heater;
    bool DoorOpen;
    bool ResumeEmitter;
    bool ResumeHeater;

    bool IsBusy() const;
    bool IsValidMicroPower(int) const;
    int CurrentPower() const;

public:
    void Reset();
    void TurnOn();
    void TurnOff();
    bool SetMode(int);
    bool SetTimer(int);
    bool SetMicroPower(int);
    bool StartHeating();
    void OpenDoor();
    void CloseDoor();
    double FinishHeating(int WorkedSec);

    bool GetPower() const { return Power; }
    int GetMicroPower() const { return MicroPower; }
    int GetMode() const { return Mode; }
    const char* GetModeName() const { return OvenModeName[Mode]; }
    int GetTimer() const { return Timer; }
    bool GetEmitter() const { return Emitter; }
    bool GetHeater() const { return Heater; }
    bool GetResumeEmitter() const { return ResumeEmitter; }
    bool GetResumeHeater() const { return ResumeHeater; }
    bool GetDoorOpen() const { return DoorOpen; }
};

#endif