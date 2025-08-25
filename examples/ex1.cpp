/**
 * @file ex1.cpp
 * @brief Example program demonstrating use of the Buzzer class.
 *
 * This simple demo shows how to:
 * - Initialize a buzzer connected to a GPIO line
 * - Play a predefined alarm pattern (`alarmExit`)
 *
 * ### Build
 * @code
 * mkdir -p ./bin && g++ -o ./bin/ex1 ex1.cpp ../*.cpp ../../AUXIO_Linux/*.cpp -lpthread -lgpiod
 * @endcode
 *
 * ### Run (requires root privileges)
 * @code
 * sudo ./bin/ex1
 * @endcode
 */
 
// ###########################################################
// Include libraries:
#include <iostream>
#include "../Buzzer.h"
#include <gpiod.h>

// ############################################################

/**
 * @brief Default GPIO chip device file.
 *
 * Most Linux boards expose GPIO lines through `/dev/gpiochipN`.
 * This example assumes chip 0.
 */
static constexpr const char* chipAddress = "/dev/gpiochip0";

/**
 * @brief GPIO line offset number for the buzzer.
 *
 * This is the offset within the chip (not the physical header pin).
 * For example, offset 27 typically corresponds to GPIO27 on Raspberry Pi.
 */
const unsigned int line_offset = 27;       

// ############################################################

/**
 * @brief Program entry point.
 *
 * Steps:
 * 1. Create a Buzzer object bound to `chipAddress` and `line_offset`.
 * 2. Initialize it with begin().
 * 3. If initialization succeeds, play the `alarmExit()` pattern
 *    (two short beeps).
 * 4. Exit cleanly.
 *
 * @return 0 on success, non-zero on failure.
 */
int main()
{   
    // Create buzzer on GPIO27, active-high wiring.
    Buzzer buzzer(chipAddress, line_offset, 1);

    // Initialize and check for errors.
    if (buzzer.begin() == false)
    {
        std::cout << buzzer.errorMessage << std::endl;
        return 1;
    }

    // Play exit alarm pattern.
    buzzer.alarmExit();

    return 0;
}
