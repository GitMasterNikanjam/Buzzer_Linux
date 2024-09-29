#ifndef _BUZZER_H_
#define _BUZZER_H_

    #include <iostream>
    #include <bcm2835.h>

    // Active buzzer object.
    class Buzzer
    {
        public:

            std::string errorMessage;

            /*
                Buzzer object constructor. Set Buzzer pin and its active low/high mode. Not apply setting.
                Hint: begin() method needs after this for apply setting on hardware.
                mode: active low/high mode. Actice low:0, Active high:1 
            */
            Buzzer(uint8_t pin, uint8_t mode); 

            /*
                Apply setting on hardware. Start Buzzer action.
                @return true if successed.
            */
            bool begin(void);

            /*
                Clean setting on hardware. Stop  Buzzer action. 
            */
            void clean(void);

            /*
                Alaram for warning type 1.
                Hint: it excutes in blocking mode.
            */
            void alarmWarning_1(void);

            /*
                Alarm for initialization actions.
                Hint: it excutes in blocking mode.
            */
            void alarmInit(void);

            /*
                Alarm for exite/stop actions.
                Hint: it excutes in blocking mode.
            */
            void alarmExit(void);

        private:

            // GPIO pin number
            uint8_t _pin;
            
            // Active low/high mode. Actice low:0, Active high:1 
            uint8_t _mode;

            // Digital value for buzzer turn on state.
            uint8_t _on;

    };

#endif  // _BUZZER_H_