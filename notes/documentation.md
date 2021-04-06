---
title: Buoy Documentation
author: Jeremy Andrews I. Zantua
output: pdf_document
---

\tableofcontents

# Researching for specifications and selection of components
In this stage, the specifications and expected capabilities of the device have been discussed:

## Buoy
The expected capabilities of the buoy have been discussed and the following components have been selected:

### Computing
A microcontroller with enough computational power a small physical footprint is required as it will be made to fit inside a pool floater. We have opted for an **Arduino Nano clone** as it is cheap, readily available and has about the same functionality as an authentic Arduino-brand board. It is also preferred as it already has an onboard regulator to regulate the current coming from the power source.

### Power supply
Power for all the electronics will mainly come from a battery pack inside the buoy, which is being charged by the solar panel. Power directly coming from the solar panel itself can be used as a supplementary source of current if the battery is fully charged.

- Power will be stored in a **18650 rechargable 3.7V 2,500 mAh Lithium-ion battery** hooked up to a solar charging system. It will be held in place by a **battery holder**.
- A **2A Boost Converter** is used to boost the voltage coming from the battery, as we will be using a single 3.7V cell while the Arduino Nano clone requires an operating voltage of at least 5V.

### Power recharging
Power for recharging will be supplied by a solar charging system consisting of two components:

- **5V 1.25W Solar Panel** for converting solar energy into electrical energy.
- **TP4056 micro USB charging controller board** for regulating the electrical energy from the solar panel going into the battery. It ensures that the battery will not charge beyond its rated voltage as this may result in a battery malfunction, resulting in fire, explosion, leakage or other types of battery malfunctions. It also enables the device to be charged via conventional smartphone chargers, as it has a micro USB port.

### Noise level measurement
For measuring the noise level in an aquatic environment, the use of a Hydrophone seemed appropriate. As there is no commercially-available hydrophone from the stores that we have checked with, we have decided to fabricate our own. The hydrophone will consist of:

- A **sound sensor** to measure the noise levels in the environment.
- **Mineral oil** to submerge the sound sensor in a non-conductive liquid, so that any sound waves travelling through the body of water will be picked up by the sound sensor, as opposed to containing the sound sensor in an enclosure with air.
- An **enclosure** for the hydrophone that will keep water out.

### Communication
We have opted for the **nRF24L01 Wireless Transceiver Module** --- a wireless, radio-frequency transceiver will be used for wireless communication between the buoy and the station as it is cheap, readily available and does not require a lot of power, an important factor since our buoy will be powered by batteries. 

### Enclosure
A floatable enclosure with enough room to house a smaller, waterproof enclosure containing the electronics is needed. We have opted for a **pool chlorine dispenser** as it is perfectly capable of staying afloat while having an internal compartment that can fit a cylinder, which will house the electronics of the buoy.

### Miscellaneous
- A **passive buzzer** is installed in the buoy to help with troubleshooting in the form of beep codes.
- A **laser-cut acrylic enclosure** was made to house the solar panel, charging module and radio-frequency transceiver. It is mounted to the top lid of the pool floater.
- **Wires** for connecting components.
- **PCB** for assembling the components into a single board.
- **10µF 6.3V capacitors** are added to the radio transceivers to clean up the power that it receives.

## Station
The station will be a stationary device intended to be on land, which will act as a communication hub for multiple buoys. It can be operated on its own, or with manual operation via a serial interface available through a laptop/desktop computer, or a smartphone.

### Power Supply and Recharging
It will use the same setup as the buoy, sans the solar charging system. It is mainly going to be charged using conventional smartphone chargers thanks to the TP4056.

### Communication
It will use the same radio-frequency wireless transceiver as the buoy.

### Enclosure
Its enclosure will be a rectangular plastic enclosure to house all the electronics.

### Misc
- A **passive buzzer** is installed in the buoy to help with troubleshooting in the form of beep codes.
- **Wires** for connecting components.
- **PCB** for assembling the components into a single board.
- **10µF 6.3V capacitors** are added to the radio transceivers to clean up the power that it receives.

# Programming
Code is then written for use with the buoy and the station. The source code can be viewed at **[http://github.com/Cyphred/boom-buoy](http://github.com/Cyphred/boom-buoy)**.

## Initialization
During the establishment of a connection between the station and the buoy, an exchange of information must take place. First, the station must send a connection request to the buoy, which in turn, may grant or reject the request, depending on the buoy's current state. Once a connection request has been granted, the buoy is expecting the station to send the operational parameters to be used, such as the **variance threshold**, **operation mode**, **noise measurement interval** and **ping intervals**. Once the buoy has been properly initialized, it will proceed with operation following the parameters that the station has set.

## Blast detection algorithm
The algorithm for monitoring for a potential dynamite blast consists of regularly taking noise level samples from the environment, and comparing each new noise sample to the previous one by getting the percentage of variance between the older sample and the newer sample. A maximum variance threshold is set during initialization, and each computed variance is compared to this threshold. If this threshold is exceeded, the station is alerted of a possible dynamite blast.

# Fabrication and Assembly
