/**
 * @file Buzzer.h
 * @brief Simple active buzzer driver built on AUXIO (libgpiod backend).
 *
 * This class wraps a single GPIO line as a buzzer output and provides:
 * - Manual on/off control
 * - A few ready-made blocking alarm patterns (short beeps)
 *
 * The buzzer can be wired as active-high or active-low. Use `mode = 1` for
 * active-high (driving GPIO high turns the buzzer on) or `mode = 0` for
 * active-low wiring.
 *
 * @note Alarm pattern methods are **blocking** and sleep internally.
 *
 * @see AUXIO for the underlying GPIO output helper.
 */

// #################################################################
#pragma once

// #############################################################################
// Include libraries:

#include "../AUXIO_Linux/AUXIO.h" // AUXIO (AUXO) is based on libgpiod.
#include <cstdint>
#include <string>
#include <thread>
#include <chrono>

// ############################################################################
// Buzzer class:

/**
 * @class Buzzer
 * @brief Active buzzer driver using AUXIO (libgpiod backend).
 *
 * A lightweight wrapper around a single GPIO line configured as an output
 * through AUXIO's AUXO helper. It supports active-high or active-low wiring
 * and provides a few convenience alarm patterns.
 *
 * ### Example
 * @code
 * #include "Buzzer.h"
 * #include <chrono>
 * #include <thread>
 *
 * int main() {
 *     // Use GPIO line 17 on /dev/gpiochip0; active-high wiring.
 *     Buzzer buz("/dev/gpiochip0", 17, 1);
 *
 *     if (!buz.begin()) {
 *         std::cerr << "Buzzer init failed: " << buz.errorMessage << "\n";
 *         return 1;
 *     }
 *
 *     buz.alarmInit();                           // one short beep
 *     buz.on();
 *     std::this_thread::sleep_for(std::chrono::seconds(1));
 *     buz.off();
 *
 *     buz.clean();                               // release the GPIO line
 *     return 0;
 * }
 * @endcode
 */
class Buzzer 
{
    public:
        /**
         * @brief Last error message, if any operation fails.
         *
         * Populated (non-empty) when initialization or a GPIO write fails in the
         * underlying AUXO helper. Empty when there is no error.
         */
        std::string errorMessage; 

        /**
         * @brief Construct a new Buzzer object.
         *
         * @param gpiodChip_path Path to the GPIO chip device (e.g. `"/dev/gpiochip0"`).
         * @param line_offset    GPIO line offset number on that chip.
         * @param mode           Active level configuration:
         *                       - `0` = active-low (driving low turns the buzzer on)
         *                       - `1` = active-high (driving high turns the buzzer on)
         *
         * @note This constructor does not perform I/O. Call begin() before use.
         */
        Buzzer(const char* gpiodChip_path, unsigned int line_offset, uint8_t mode = 1);

        /**
         * @brief Initialize the buzzer GPIO as an output and ensure it is off.
         *
         * Configures the line via AUXO and drives the buzzer to the inactive level.
         *
         * @return `true` on success, `false` on failure (see #errorMessage).
         */
        bool begin();

        /**
         * @brief Release the GPIO line and clean up resources.
         *
         * After calling this, the object cannot drive the GPIO until begin() is
         * invoked again.
         */
        void clean();

        /**
         * @brief Alarm pattern: five short beeps.
         *
         * This is a blocking function that toggles the buzzer five times in 
         * quick succession, commonly used as a warning indicator.
         */
        void alarmWarning_1();

        /**
         * @brief Alarm pattern: one short beep.
         *
         * Plays a single short beep. Useful for initialization signals 
         * (e.g., system power-up).
         */
        void alarmInit();

        /**
         * @brief Alarm pattern: two quick beeps.
         *
         * Plays two short beeps in succession. Useful for exit or shutdown 
         * notifications.
         */
        void alarmExit();

        /**
         * @brief Turn the buzzer on manually.
         *
         * Drives the GPIO to the configured "on" level, activating the buzzer.
         */
        inline void on() { _auxo.on(); }

        /**
         * @brief Turn the buzzer off manually.
         *
         * Drives the GPIO to the configured "off" level, deactivating the buzzer.
         */
        inline void off() { _auxo.off(); }

    private:

        AUXO _auxo;                 //!< AUXIO output helper instance
};

