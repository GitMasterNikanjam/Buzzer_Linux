
//  * ### Build:
//  * @code
//  * mkdir -p ./bin && g++ -o ./bin/ex1 ex1.cpp ../*.cpp ../../AUXIO_Linux/*.cpp -lpthread -lgpiod
//  * @endcode
//  *
//  * ### Run (requires root privileges):
//  * @code
//  * sudo ./bin/ex1
//  * @endcode
 

// ###########################################################
// Include libraries:
#include <iostream>
#include "../Buzzer.h"
#include <gpiod.h>

// ############################################################

/**
 * @brief Default GPIO chip device file.
 */
static constexpr const char* chipAddress = "/dev/gpiochip0";

/**
 * @brief GPIO line offset number for the Buzzer.
 */
const unsigned int line_offset = 27;        // GPIO17

// ############################################################

int main()
{
    Buzzer buzzer(chipAddress, line_offset, 1);

    if (buzzer.begin() == false)
    {
        std::cout << buzzer.errorMessage << std::endl;
        return 1;
    }

    buzzer.alarmExit();

    return 0;
}
