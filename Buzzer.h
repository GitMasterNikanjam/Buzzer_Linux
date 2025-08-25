#pragma once

// #############################################################################
// Include libraries:

#include "../AUXIO_Linux/AUXIO.h" // expects AUXO (output) in your AUXIO library
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
 * This class provides a simple interface to control an active buzzer connected 
 * to a GPIO pin using the AUXIO library (AUXO output helper). The buzzer can be 
 * configured as active-high or active-low, and supports predefined alarm patterns 
 * in addition to manual on/off control.
 *
 * Example usage:
 * @code
 * Buzzer buz(17, 1);   // GPIO 17, active-high
 * if (buz.begin()) {
 *     buz.alarmInit();  // play init beep
 *     buz.on();
 *     std::this_thread::sleep_for(std::chrono::seconds(1));
 *     buz.off();
 * }
 * @endcode
 */
class Buzzer 
{
    public:
        /**
         * @brief Last error message, if any operation fails.
         *
         * This string is updated whenever an error occurs, e.g., during GPIO 
         * initialization or writing. It is empty when no error is present.
         */
        std::string errorMessage; 

        /**
         * @brief Construct a new Buzzer object.
         *
         * @param gpiodChip_path Path to the GPIO chip device (e.g. "/dev/gpiochip0").
         * @param line_offset GPIO line offset number.
         * @param mode Active level:   
         * 
         *  0 = active-low (buzzer turns on when GPIO is driven low)  
         * 
         *  1 = active-high (buzzer turns on when GPIO is driven high)
         */
        Buzzer(const char* gpiodChip_path, unsigned int line_offset, uint8_t mode = 1);

        /**
         * @brief Initialize the buzzer GPIO as an output.
         *
         * Configures the given GPIO line using AUXIO as an output, and ensures 
         * the buzzer is initially off. Must be called before using other methods.
         *
         * @return true if initialization succeeds.
         * @return false if initialization fails (check @ref errorMessage).
         */
        bool begin();

        /**
         * @brief Release the GPIO line and clean up resources.
         *
         * After calling this, the buzzer object becomes inactive and cannot 
         * drive the GPIO until @ref begin() is called again.
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

