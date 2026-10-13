#include <iostream>
#include "microwave.hpp"
using namespace std;

void PrintState(const MicrowaveOven& Oven)
{
    cout << "\n---------------- STATE ----------------\n";
    cout << "Power      : " << (Oven.GetPower() ? "ON" : "OFF") << "\n";
    cout << "Mode       : " << Oven.GetModeName() << "\n";
    cout << "MicroPower : " << Oven.GetMicroPower() << " W\n";
    cout << "Timer      : " << Oven.GetTimer() / 60 << " min " << Oven.GetTimer() % 60 << " s\n";
    cout << "Emitter    : " << (Oven.GetEmitter() ? "ON" : "OFF") << "\n";
    cout << "Heater     : " << (Oven.GetHeater() ? "ON" : "OFF") << "\n";
    cout << "Door       : " << (Oven.GetDoorOpen() ? "OPEN" : "CLOSED") << "\n";
    cout << "---------------------------------------\n";
}

void PrintResult(bool Ok)
{
    if (Ok) cout << ">> Done\n";
    else cout << ">> Refused: conditions are not met\n";
}

bool ReadInt(int& Value)
{
    if (cin >> Value) return true;
    cin.clear();
    cin.ignore(10000, '\n');
    cout << ">> Invalid input\n";
    return false;
}

int main()
{
    MicrowaveOven Oven;
    Oven.Reset();

    char key;
    do
    {
        PrintState(Oven);
        cout << "\n[1] Power on          [0] Power off\n";
        cout << "[2] Select mode       [3] Set microwave power\n";
        cout << "[4] Set timer         [5] Start heating\n";
        cout << "[6] Open door         [7] Close door\n";
        cout << "[8] Finish heating    [e] Exit\n";
        cout << "> ";
        cin >> key;

        switch (key)
        {
            case '1':
                Oven.TurnOn();
                break;
            case '0':
                Oven.TurnOff();
                break;
            case '2':
            {
                int m;
                cout << "Mode (0 - microwave, 1 - grill): ";
                if (ReadInt(m)) PrintResult(Oven.SetMode(m));
                break;
            }
            case '3':
            {
                int w;
                cout << "Power (160, 320, 640, 800): ";
                if (ReadInt(w)) PrintResult(Oven.SetMicroPower(w));
                break;
            }
            case '4':
            {
                int s;
                cout << "Timer in seconds (10 - 3600): ";
                if (ReadInt(s)) PrintResult(Oven.SetTimer(s));
                break;
            }
            case '5':
                PrintResult(Oven.StartHeating());
                break;
            case '6':
                Oven.OpenDoor();
                break;
            case '7':
                Oven.CloseDoor();
                break;
            case '8':
            {
                int s;
                cout << "Seconds worked: ";
                if (ReadInt(s)) cout << ">> Energy used: " << Oven.FinishHeating(s) << " kWh\n";
                break;
            }
            case 'e':
                break;
            default:
                cout << ">> Unknown command\n";
        }
    } while (key != 'e');

    return 0;
}