#pragma once

// #############################################################################
// Include libraries:

#include <cstdint>
#include <string>
#include <thread>
#include <chrono>
#include "../AUXIO_Linux/AUXIO.h" // expects AUXO (output) in your AUXIO library

// ############################################################################
// Buzzer class:

/**
* @brief Active buzzer driver using AUXIO (libgpiod backend).
*
* Keeps original semantics: constructor takes (pin, mode) where mode expresses
* the active level: 0 = active-low, 1 = active-high. Internally maps to
* output levels through AUXO.
*/
class Buzzer 
{
    public:
        std::string errorMessage; //!< Last error, if any

        /**
        * @param pin GPIO line offset
        * @param mode Active level: 0=active-low, 1=active-high
        */
        Buzzer(uint8_t pin, uint8_t mode);

        /** Configure the GPIO as output and drive the buzzer off. */
        bool begin();

        /** Release the GPIO line. */
        void clean();

        /** Warning pattern #1: 5 short beeps (blocking). */
        void alarmWarning_1();

        /** Init chirp: one short beep (blocking). */
        void alarmInit();

        /** Exit pattern: two quick beeps (blocking). */
        void alarmExit();

        /** Manually set buzzer on/off. */
        inline void on() { _write(true); }
        inline void off() { _write(false); }

    private:
        uint8_t _pin {0};
        uint8_t _mode {1}; // 0=active-low, 1=active-high
        uint8_t _onLevel {1}; // logical output level that turns the buzzer on

        AUXO _auxo; // output helper from AUXIO

        // Convert logical on/off to physical level and write
        void _write(bool on);
};

