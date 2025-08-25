# Buzzer_Linux

A simple C++ library for controlling **active buzzers** on Linux systems using the [AUXIO_Linux](../AUXIO_Linux) GPIO abstraction (libgpiod backend).  
It provides basic on/off control as well as a few predefined blocking alarm patterns.

---

## Features

- Lightweight wrapper around a single GPIO line using **AUXO** (output helper).
- Supports **active-high** or **active-low** buzzer wiring.
- Ready-made **blocking alarm patterns**:
  - `alarmInit()` → single beep
  - `alarmExit()` → two quick beeps
  - `alarmWarning_1()` → five short beeps
- Manual control functions: `on()` / `off()`.
- Error handling with human-readable messages.
- Easy integration with other AUXIO-based libraries.

---

## Requirements

- Linux kernel with GPIO character device support (`/dev/gpiochipN`).
- [libgpiod](https://git.kernel.org/pub/scm/libs/libgpiod/libgpiod.git) (tested with **v1.6.2**).
- C++17 or newer compiler.
- Root privileges (or proper udev rules) to access `/dev/gpiochip*`.

---

## Build

Clone this repository along with [AUXIO_Linux](../AUXIO_Linux).  
Example build command for the provided example `ex1.cpp`:

```bash
mkdir -p ./bin
g++ -std=c++17 -O2 -o ./bin/ex1 ex1.cpp ../*.cpp ../../AUXIO_Linux/*.cpp -lpthread -lgpiod
````

---

## Usage Example

```cpp
#include "Buzzer.h"
#include <iostream>
#include <chrono>
#include <thread>

int main() {
    // Buzzer on GPIO line 27, active-high wiring, using /dev/gpiochip0
    Buzzer buzzer("/dev/gpiochip0", 27, 1);

    if (!buzzer.begin()) {
        std::cerr << "Init failed: " << buzzer.errorMessage << std::endl;
        return 1;
    }

    buzzer.alarmInit();  // play a single short beep
    buzzer.on();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    buzzer.off();

    buzzer.clean();      // release GPIO line
    return 0;
}
```

---

## API Reference

### Class: `Buzzer`

```cpp
Buzzer(const char* chip, unsigned int line, uint8_t mode = 1);
```

* `chip` → Path to GPIO chip (e.g., `"/dev/gpiochip0"`).
* `line` → Line offset number within that chip.
* `mode`:

  * `1` = active-high (drive high = buzzer on).
  * `0` = active-low (drive low = buzzer on).

---

### Public Methods

* `bool begin()`
  Initialize GPIO as output. Returns `false` on failure.

* `void clean()`
  Release GPIO line.

* `void on()` / `void off()`
  Manual control of buzzer.

* `void alarmInit()`
  One short beep (\~100 ms).

* `void alarmExit()`
  Two quick beeps (\~50 ms each).

* `void alarmWarning_1()`
  Five short beeps (\~100 ms each).

---

### Error Handling

* `std::string errorMessage`
  Contains the last error message if `begin()` fails.

---

## Example Program

`ex1.cpp` demonstrates usage:

```cpp
Buzzer buzzer("/dev/gpiochip0", 27, 1);

if (!buzzer.begin()) {
    std::cout << buzzer.errorMessage << std::endl;
    return 1;
}

buzzer.alarmExit();  // two quick beeps
```

### Build & Run

```bash
mkdir -p ./bin
g++ -o ./bin/ex1 ex1.cpp ../*.cpp ../../AUXIO_Linux/*.cpp -lpthread -lgpiod
sudo ./bin/ex1
```

---

## Notes

* Alarm methods are **blocking** (use `std::this_thread::sleep_for`).
  For non-blocking patterns, extend with your own thread worker.
* Requires root access unless udev rules grant permission to `/dev/gpiochip*`.
* Tested on Raspberry Pi and x86 Linux boards with libgpiod v1.6.2.

---

## License

This project is released under the MIT License.
See [LICENSE](LICENSE) for details.


