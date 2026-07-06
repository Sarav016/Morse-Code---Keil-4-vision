# Real-Time Morse Code Encoder & Simulator (ARM7 - LPC2148)

An embedded C application designed for the NXP LPC2148 (ARM7 TDMI-S) microcontroller that transforms standard text strings into standard International Morse Code signals. This repository is specifically optimized for bare-metal evaluation inside the **Keil uVision4/5 Simulator Engine**, mapping bit-level GPIO state shifts directly to simulated software oscilloscopes.

---

## 📖 System Design & Theory of Operation

Morse code represents text characters through a standardized sequence of short and long signals, known as **Dots** (.) and **Dashes** (-). The timing ratios within this implementation adhere strictly to standard time-unit structures:

* **1 Unit of Time :** The fundamental basis of duration. Used as the length of a single **Dot** and the mandatory silence interval between individual dots and dashes inside a single letter.
* **3 Units of Time :** The duration of a **Dash** signal, as well as the absolute silent interval separating two distinct letters.
* **7 Units of Time (:** The absolute silence interval separating complete words or string iterations.



### The Simulation Optimization Challenge
In a physical hardware implementation, a delay loop running at a standard peripheral clock frequency (e.g., $60\text{ MHz}$) requires high iteration limits (e.g., counting up to `6000` loops) to halt execution for exactly $1\text{ ms}$. 

However, when running inside an IDE software simulator, simulating millions of raw clock cycles causes heavy CPU bottlenecks, making real-world execution appear completely frozen. This project rectifies the issue by deploying a radically scaled configuration  = 1$ and a inner delay loop limit of `10`), allowing full data packet processing within fractions of a simulated second.

---

## 🛠️ Architecture & Pin Out Specifications

* **Target Core:** ARM7TDMI-S (LPC2148)
* **Output Pin Assignment:** Port 0, Pin 0 (`P0.0` / Pin 1 on physical LQFP64 package layouts)
* **Peripheral Mapping:** Controlled via the standard NXP memory-mapped I/O structure (`IOSET0`, `IOCLR0`, `IODIR0`, `PINSEL0`).
* **System Clock Configuration:** Simulated at a crystal oscillator speed of **12.0 MHz**.

---


OUTPUT :
The word SOS in morse code<img width="750" height="363" alt="image" src="https://github.com/user-attachments/assets/f503ab0b-2554-400f-b8ca-341c0443d2b5" />


## ⚙️ Customization: Encoding Your Name

The encoder features an automatic lookup algorithm that maps ASCII characters to array indexing numbers ($Index = \text{Character} - \text{'A'}$), natively managing capitalization formatting.

To modify the broadcast text to your name or custom string, locate the runtime execution loop inside the `main.c` function block:

```c
int main(void) {
    PINSEL0 = 0x00000000;  // Configure Pins P0.0 to P0.15 as GPIO
    IODIR0  = MORSE_PIN;   // Set P0.0 to output mode
    
    while(1) {
        // Change the target string literal argument below:
        Send_Morse("YOUR NAME HERE"); 
        
        // Wait 7 units before starting the loop again
        Delay_ms(UNIT_TIME * 7); 
    }
}


