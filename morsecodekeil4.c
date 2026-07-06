#include <LPC214x.H>

#define MORSE_PIN (1 << 0)      // P0.0
#define UNIT_TIME 1             // Optimized for simulator speed

const char morse[26][6] = {
    ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---",
    "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-",
    "..-", "...-", ".--", "-..-", "-.--", "--.."
};

void Delay_ms(unsigned int ms) {
    unsigned int i, j;
    for(i = 0; i < ms; i++) {
        for(j = 0; j < 10; j++); 
    }
}

void Send_Morse(char message[]) {
    int i, j;
    for(i = 0; message[i] != '\0'; i++) { 
        char c = message[i];

        if(c == ' ') {
            Delay_ms(UNIT_TIME * 7); 
            continue;
        }

        if(c >= 'a' && c <= 'z') c -= 32;

        if(c >= 'A' && c <= 'Z') {
            int letterIndex = c - 'A';
            
            for(j = 0; morse[letterIndex][j] != '\0'; j++) {
                IOSET0 = MORSE_PIN;                 // Pin High
                
                if(morse[letterIndex][j] == '.') 
                    Delay_ms(UNIT_TIME);            // DOT
                else
                    Delay_ms(UNIT_TIME * 3);        // DASH
                
                IOCLR0 = MORSE_PIN;                 // Pin Low
                Delay_ms(UNIT_TIME);                // Intra-symbol gap
            }
            Delay_ms(UNIT_TIME * 3);                // Inter-letter gap
        }
    }
}

int main(void) {
    PINSEL0 = 0x00000000;
    IODIR0 = MORSE_PIN;
    
    while(1) {
        Send_Morse("SOS");
        Delay_ms(UNIT_TIME * 7); 
    }
}