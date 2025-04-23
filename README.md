# Ticksy - Smart RFID Bus Ticketing System 🚌💳

**Ticksy** is an Arduino-based smart ticketing system designed to reduce the manual efforts of bus conductors. It uses an RFID reader to automate the ticketing process by allowing passengers to tap their RFID cards when boarding a bus.

## 🚀 Project Overview

The goal of Ticksy is to provide a contactless and efficient solution for bus ticketing. By implementing an RFID module at the bus door, passengers can quickly access the system to get ticket details, check balances, and deduct fare based on distance – all displayed on an LCD screen.

This solution ensures:
- Fast boarding process
- Less human effort for ticket collection
- Secure and transparent fare deductions
- Easy integration with existing public transport systems

## 🔧 Features

- 🚪 **RFID-Based Entry System**  
  Passengers tap their card to get authenticated.

- 🧑‍💼 **Passenger Identification**  
  Displays the passenger's name and current balance.

- 💸 **Automated Fare Deduction**  
  Deducts fare according to distance (configurable, e.g., ₹30 per journey).

- 📺 **LCD Display**  
  Shows name, balance, and journey info clearly on a 16x2 LCD screen.

- 🔁 **Serial Monitor Logging**  
  Provides additional logs for debugging or data logging purposes.

- 🔐 **Smart Access Control**  
  Denies entry if the card is unregistered or the balance is insufficient.

- 🎯 **Conductor-Free Operation**  
  Reduces human interaction and errors in ticketing.

## 🧰 Hardware Requirements

- Arduino Uno (or compatible board)  
- RFID Reader (MFRC522)  
- RFID Tags/Cards  
- 16x2 LCD Display (with I2C module)  
- Servo Motor (for gate simulation)  
- Breadboard & Jumper Wires  
- Optional: Buzzer or LED indicators

## 🛠️ How It Works

1. **Setup the hardware** by wiring the components according to the circuit diagram.
2. Upload the Arduino code from this repository using the Arduino IDE.
3. Place an RFID card near the reader.
4. The LCD displays the user's name, balance, and deducts fare.
5. If balance is insufficient or card is unknown, access is denied.
6. Gate (servo) opens only for valid users.

## 📷 Project Demo & Circuit

*Insert images of your circuit and working project here if available*

## 🎨 Logo

![Ticksy Logo](./ticksy_logo.png)  
*A modern touch to a smarter journey*

## 📁 Repository Structure

