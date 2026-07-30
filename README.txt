STM32 BME280 & OLED Weather Station (RTOS Optimized)

This project is a high-reliability embedded firmware solution designed for the STM32F446RE (Nucleo-64) platform. It serves as a practical demonstration of RTOS-based concurrent task management, secure resource sharing, and system-level fault protection.


🏗️ System Architecture
The firmware is built on FreeRTOS, employing a decoupled task architecture to ensure deterministic timing and system stability:

Data Acquisition Task: Dedicated task for BME280 sensor sampling, ensuring continuous environmental monitoring.

Communication Task (HMI): Manages the SSD1306 OLED display updates, ensuring the UI remains responsive without blocking the sensor sampling loop.

Concurrency & Thread Safety: Implementation of Mutexes for shared I2C bus access, preventing data corruption and resource contention between tasks.

Fault Tolerance: Integration of an Independent Watchdog (IWDG) to guarantee fail-safe system recovery in case of deadlock or task hang-ups.

🛠️ Technical Implementation
IDE: STM32CubeIDE (C/C++).

Operating System: FreeRTOS (Task-based architecture, Mutexes, Message Queues).

Hardware: STM32 Nucleo-F446RE, BME280 (I2C), SSD1306 OLED (I2C), DS3231 RTC.

Communication: I2C (100kHz Normal Mode) with hardware synchronization; UART telemetry for debugging.

Verification: Logic Analyzer (Kingst LA1010) utilized to verify bus protocol integrity and timing constraints.

💡 Key Challenges & Solutions
I2C Bus Contention: With two tasks (sensor and display) competing for the same bus, I implemented a Mutex mechanism. This ensures thread-safe access and prevents race conditions during I2C transactions.

System Reliability: To ensure long-term stability, an Independent Watchdog (IWDG) was configured. Tasks provide "heartbeat" feedback; if any task fails to respond within the predefined window, the hardware forces a system reset.

Deterministic Scheduling: By utilizing Message Queues, data is passed asynchronously from the acquisition task to the display task, minimizing the blocking time on the I2C bus.

📂 Project Structure
Plaintext
/Core           - RTOS Tasks (DataTask, CommTask, DefaultTask), Main App
/Drivers        - HAL and CMSIS peripheral drivers
/Dokumentation  - Schematics, logic analysis logs, and technical specs
/Debug          - Compilation/Binary outputs
📄 Documentation
Detailed technical logs and hardware designs can be found in the Dokumentation/ directory:

Hardware Schematic

I2C Bus Analysis Logs

Sensor & HMI Protocol Analysis

📚 Credits & References
Bosch BME280 Sensor API

afiskon/stm32-ssd1306