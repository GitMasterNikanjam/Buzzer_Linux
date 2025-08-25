// #####################################################################
// Include libraries:

#include "Buzzer.h"

using namespace std::chrono_literals;

// #####################################################################
// Buzzer class:

Buzzer::Buzzer(const char* gpiodChip_path, unsigned int line_offset, uint8_t mode)
: _auxo(gpiodChip_path, line_offset, mode){}

bool Buzzer::begin()
{
    // Initialize as output and ensure buzzer is off
    if (!_auxo.begin()) 
    {
        errorMessage = "AUXO begin() failed.";
        return false;
    }

    off(); // ensure OFF
    return true;
}

void Buzzer::clean()
{
    // Return the line to kernel control
    _auxo.clean();
}

void Buzzer::alarmWarning_1()
{
    for (int i = 0; i < 5; ++i) 
    {
        on(); std::this_thread::sleep_for(100ms);
        off(); std::this_thread::sleep_for(100ms);
    }
}

void Buzzer::alarmInit()
{
    on(); std::this_thread::sleep_for(100ms);
    off(); std::this_thread::sleep_for(100ms);
}

void Buzzer::alarmExit()
{
    for (int i = 0; i < 2; ++i) 
    {
        on(); std::this_thread::sleep_for(50ms);
        off(); std::this_thread::sleep_for(100ms);
    }
}

