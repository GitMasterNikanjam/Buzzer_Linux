// #####################################################################
// Include libraries:

#include "Buzzer.h"

using namespace std::chrono_literals;

// #####################################################################
// Buzzer class:

Buzzer::Buzzer(uint8_t pin, uint8_t mode)
: _pin(pin), _mode(mode), _auxo(pin)
{
    // Determine physical level that activates the buzzer
    _onLevel = (_mode == 0) ? 0 : 1; // active-low -> 0, active-high -> 1
}

bool Buzzer::begin()
{
    if (_pin > 30) 
    {
        errorMessage = "Error Buzzer object. pin configuration is in wrong range.";
        return false;
    }

    // Initialize as output and ensure buzzer is off
    if (!_auxo.beginOutput()) 
    {
        errorMessage = "AUXO beginOutput() failed.";
        return false;
    }

    _write(false); // ensure OFF
    return true;
}

void Buzzer::clean()
{
    // Return the line to kernel control
    _auxo.end();
}

void Buzzer::_write(bool on)
{
    const int level = on ? _onLevel : (1 - _onLevel);
    _auxo.write(level); // ignore return for brevity; adapt if you prefer
}

void Buzzer::alarmWarning_1()
{
    for (int i = 0; i < 5; ++i) 
    {
        _write(true); std::this_thread::sleep_for(100ms);
        _write(false); std::this_thread::sleep_for(100ms);
    }
}

void Buzzer::alarmInit()
{
    _write(true); std::this_thread::sleep_for(100ms);
    _write(false); std::this_thread::sleep_for(100ms);
}

void Buzzer::alarmExit()
{
    for (int i = 0; i < 2; ++i) 
    {
        _write(true); std::this_thread::sleep_for(50ms);
        _write(false); std::this_thread::sleep_for(100ms);
    }
}

