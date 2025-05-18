# 🦶🔋 Footstep Power Generator – Monitoring Circuit
Ayat-Nauman/Footstep-Power-Generation-Monitorization

This project implements a **real-time monitoring system** for a footstep-based power generator. Using Arduino Uno and a combination of sensors, it displays voltage, current, power, RPM, applied weight, and spring deflection on an OLED screen. Ideal for energy harvesting and smart infrastructure applications.

---

## 🎯 Objectives

- Measure electrical output (voltage, current, and power).
- Monitor mechanical parameters: gear RPM, platform weight, and spring compression.
- Display all data in real-time on a compact OLED interface.
- Ensure safe Arduino interfacing using INA219 for high-voltage measurement.

---

## 📦 Components Used

| Component                  | Quantity | Description                                     |
|---------------------------|----------|-------------------------------------------------|
| Arduino Uno               | 1        | Microcontroller for processing & control        |
| INA219 Module             | 1        | Voltage, current, and power measurement         |
| A3144 Hall Effect Sensor  | 1        | Detects RPM via magnetic pulse sensing          |
| 50kg Load Cells           | 4        | Measures weight on the footstep plate           |
| HX711 Amplifier           | 1        | Signal amplifier for load cells                 |
| Potentiometer             | 1        | Measures spring compression/deflection          |
| OLED Display (128x64 I2C) | 1        | Visual output for live data                     |
| Small Magnet              | 1        | Mounted on pinion gear for RPM detection        |
| Jumper Wires              | -        | For connections                                 |
| Power Source              | 1        | From footstep generator (up to 24V)             |

---

## 🔌 Arduino Pin Mapping

| Arduino Pin | Component Connected         | Purpose                         |
|-------------|-----------------------------|---------------------------------|
| A0          | Potentiometer               | Spring deflection sensing       |
| A4          | INA219 & OLED (SDA)         | I2C communication data          |
| A5          | INA219 & OLED (SCL)         | I2C communication clock         |
| D2          | Hall Effect Sensor (OUT)    | RPM detection input             |
| D3          | HX711 DT                    | Load cell data                  |
| D4          | HX711 SCK                   | Load cell clock                 |
| 5V          | All VCC lines               | Power supply                    |
| GND         | All GND lines               | Common ground                   |

---

## 🖥️ Parameters Displayed on OLED

- **Voltage (V)**
- **Current (A)**
- **Power (W)**
- **Weight (kg)**
- **Gear RPM**
- **Spring Deflection**

---

## ⚙️ How It Works

1. **Footstep is applied** → Rack and pinion rotates.
2. **Gear motion detected** → Hall sensor counts magnetic pulses for RPM.
3. **Weight applied** → Load cells capture pressure and HX711 sends digital signal.
4. **Spring compresses** → Potentiometer changes resistance proportional to movement.
5. **Generator output** → INA219 safely measures voltage/current.
6. **Data displayed** → OLED shows real-time readings.

---
