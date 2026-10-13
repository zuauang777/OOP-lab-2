#include "microwave.hpp"

bool MicrowaveOven::IsBusy() const
{
    return Emitter || Heater || ResumeEmitter || ResumeHeater;
}

bool MicrowaveOven::IsValidMicroPower(int Watts) const
{
    return Watts == 160 || Watts == 320 || Watts == 640 || Watts == 800;
}

int MicrowaveOven::CurrentPower() const
{
    if (Mode == MODE_MICROWAVE) return MicroPower;
    return GRILL_POWER;
}

void MicrowaveOven::Reset()
{
    Power = false;
    Mode = MODE_MICROWAVE;
    MicroPower = DEFAULT_MICRO_POWER;
    Timer = 0;
    Emitter = false;
    Heater = false;
    DoorOpen = false;
    ResumeEmitter = false;
    ResumeHeater = false;
}

void MicrowaveOven::TurnOn()
{
    if (Power) return;
    Power = true;
    Mode = MODE_MICROWAVE;
    MicroPower = DEFAULT_MICRO_POWER;
    Timer = 0;
}

void MicrowaveOven::TurnOff()
{
    Power = false;
    Emitter = false;
    Heater = false;
    ResumeEmitter = false;
    ResumeHeater = false;
}

bool MicrowaveOven::SetMode(int NewMode)
{
    if (!Power || IsBusy()) return false;
    if (NewMode != MODE_MICROWAVE && NewMode != MODE_GRILL) return false;
    Mode = NewMode;
    return true;
}

bool MicrowaveOven::SetMicroPower(int Watts)
{
    if (!Power || IsBusy()) return false;
    if (!IsValidMicroPower(Watts)) return false;
    MicroPower = Watts;
    return true;
}

bool MicrowaveOven::SetTimer(int Seconds)
{
    if (!Power) return false;
    if (Seconds < MIN_TIMER || Seconds > MAX_TIMER) return false;
    Timer = Seconds;
    return true;
}

bool MicrowaveOven::StartHeating()
{
    if (!Power || DoorOpen || IsBusy()) return false;
    if (Timer < MIN_TIMER) return false;
    if (Mode == MODE_MICROWAVE) Emitter = true;
    else Heater = true;
    return true;
}

void MicrowaveOven::OpenDoor()
{
    DoorOpen = true;
    if (Emitter) { Emitter = false; ResumeEmitter = true; }
    if (Heater) { Heater = false; ResumeHeater = true; }
}

void MicrowaveOven::CloseDoor()
{
    if (!DoorOpen) return;
    DoorOpen = false;
    if (Power)
    {
        if (ResumeEmitter) Emitter = true;
        if (ResumeHeater) Heater = true;
    }
    ResumeEmitter = false;
    ResumeHeater = false;
}

double MicrowaveOven::FinishHeating(int WorkedSec)
{
    if (!IsBusy() || WorkedSec < 0) return 0.0;
    if (WorkedSec > Timer) WorkedSec = Timer;
    double Energy = CurrentPower() * (WorkedSec / 3600.0) / 1000.0;
    Emitter = false;
    Heater = false;
    ResumeEmitter = false;
    ResumeHeater = false;
    Timer -= WorkedSec;
    return Energy;
}