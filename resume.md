---
title: resume
permalink: /resume/
layout: page
comments: false
---

<!-- <div> -->
<!--     <div style="float: right; margin-left: 10px;"> -->
<!--         <img src="/assets/img/profile.png" alt="Image Description" width="120"> -->
<!--     </div> -->
<!--     <div> -->
<!--         <h1 style="margin-bottom: 0;">Guilherme B. da Silva</h1> -->
<!--         <h5 style="margin-top: 0; margin-bottom: 10px;"> -->
<!--             <p style="color: gray; margin: 0;">MSc. in Electrical Engineering</p> -->
<!--             <p style="color: gray; margin: 0;">Embedded Software Engineer &</p> -->
<!--             <p style="color: gray; margin: 0;">Embedded Tech. Lead. at V3</p> -->
<!--         </h5> -->
<!--     </div> -->
<!-- </div> -->

<style>
    .container {
        overflow: auto;
    }

    .image-container {
        float: right;
        margin-left: 10px;
        margin-bottom: 0;
        margin-top: 0;
    }

    .name {
        margin-bottom: 0;
    }

    .subtitle {
        margin-top: 0;
        margin-bottom: 5px;
    }

    .gray-text {
        color: gray;
        margin: 0;
    }
</style>

<div class="container">
    <div class="image-container">
        <img src="/assets/img/profile.png" alt="Image Description" width="170">
    </div>
    <div>
        <h1 class="name">Guilherme Brandão da Silva</h1>
        <h5 class="subtitle">
            <p class="gray-text">MSc. in Electrical Engineering |</p>
            <p class="gray-text">Embedded Software Engineer &</p>
            <p class="gray-text">Embedded Tech. Lead. at V3</p>
        </h5>
    </div>
</div>

I am very passionate about new technologies research and development, always looking for challenges. Writing software for solving problems, while not being afraid of any hardware integration, excites me. Good communication skills, driven by teamwork, always willing to help those around and objectively reporting results, regardless of whether they are good. Fast learner experienced in Linux, Android, and bare-metal embedded systems development. Usual activities involve real-time programming, telemetry, computer vision, and electronic instrumentation.
Not in my skills, I love to study and research processor architectures, software engineering lore, and machine learning.

# Education

---
<div>
<div class="container">
    <h4> MSc. in Electrical Engineering </h4>
    <p class="gray-text">UEL (State University of Londrina) - 2019/2022</p>
    <p>Master's thesis: ”CUDA‐based Real-Time Ego‐Lane Detection in Embedded Systems”.</p>
</div>

<div class="container">
    <h4> BSc. in Electrical Engineering </h4>
    <p class="gray-text">UEL (State University of Londrina) - 2014/2018</p>
    <p>Undergraduate’s thesis: ”Hardware‐in‐the‐Loop Platform for Modeling and Control of Quad‐copters”.</p>
</div>

<div class="container">
    <h4> Technical in Informatics </h4>
    <p class="gray-text">UTFPR (Federal Technological University of Paraná) - 2010/2013</p>
</div>
</div>

# Projects
---
<div>
    <h4 class="subtitle">CUDA‑based Real-Time Ego‑Lane Detection in Embedded Systems</h4>
    <h5 class="gray-text">Master's thesis - Electrical Engineering (UEL) - 2022</h5>
</div>
This work proposed the heterogeneous embedded implementation of a real-time lane detection system capable of estimating lane marks from images of a monocular camera. Each frame is processed to obtain a suitable bird’s eye view perspective. Were extracted the lane mark features to build different feature maps. Then the maps are combined to generate a robust binary frame with the lane marks used for the lanes estimation.

- Responsible for the embedded hardware choice, algorithm design, and software implementation, testing, and validation (`CUDA`, `C++`, `OpenCV`, `GoogleTest`, `VisualProfiler`, `Python`).
- The software development and evaluation were on an embedded Jetson Nano board (an ARM A57 CPU and Maxwell 128 CUDA cores GPU). The whole application was implemented in `C++/CUDA` programming languages achieving high performance in heterogeneous programming. The GoogleTest was used for tests and the TuSimple dataset for the benchmarks and evaluations.
- The developed heterogeneous software performance ranged from 92.3% to 99.0% accuracy in the datasets, detecting up to 97.9% of the ego lanes available. The embedded system achieved real‐time constraints, running 25 and 140 times faster than the hybrid and CPU‐executed, respectively.

<div>
    <h4>Hardware‑in‑the‑Loop Platform for Modeling and Control of Quad‑copters</h4>
    <h5 class="gray-text">Undergraduate's thesis - Electrical Engineering (UEL) - 2018</h5>
</div>
The work proposed an end-to-end test environment for modeling and controlling quad-copters based on hardware-in-the-loop simulation.
Responsibilities and key achievements:

- Responsible for the embedded hardware, firmware implementation, model simulation, and HiL platform.
- The design and implementation of quad-copter dynamical and kinematic models and control plants for an online simulation. (`Matlab/Simulink`)
- A graphical interface to control and watch the telematics data from the under-test quad-copter `ControlDesk (dSPACE)`.
- The development of firmware for embedded quad-copters. Capable of real-time sensors telemetry, motors control, and receiving the online configurations and commands from the HiL platform. (`C`, `FreeRTOS`, `STM32-HAL`, `Electronics`)
- The 4DoF structure provides a safe and realistic test bench for the end-to-end test of quad-copters.

# Experience
---
## Golfleet/V3 (2021 - current)
##### Embedded Technical Lead (03/2022 - current)

Embedded software development for smart dash cams, focusing on video telematics.
- Embedded architecture planning for smart dash cams.
- Working on the automation of the Q&A process, the CI/CD, and the end-to-end equipment test platform.
- Assist in the design and development of cloud services and integration APIs.
- Leadership and management of the development team, actively in the team recruiting and interviews.
    
##### Embedded Software Developer (03/2021 - 03/2022)
- New features development, technical improvements, and maintenance of existing embedded software.
- Porting of existing embedded applications to a new hardware device.
- Development of services, APIs, and libraries for cloud applications.


## Ecozone (Embedded System Engineer | 2019 - 2020)
Electronic system for instrumentation of *PH3* and *O3* concentration and control of the silos purging process.     
- Embedded platform design for real-time data telemetry.
    - Firmware architecture planning for the sensors instrumentation and the real-time data acquisition and telemetry. (`C`, `FreeRTOS`, `STM32-HAL`)
    - I worked on the PCB design for the sensors boards and the embedded platform, which had an MCU (ARM Cortex M), serial communication (such as SPI for the sensor interface, and RS485 to communicate with the control module), and actuators.
- Developed the central board for real-time monitoring and control of the process (HMI).
    - Custom Linux kernel for the embedded system.
    - Developed the data acquisition, and processing for monitoring the purge process. (`Embedded Linux`, `C/C++`).
    - Graphical HMI development for assisting the data acquisition (telemetry), visualization, process monitoring, and control. (`C++`, `Qt5`).
    

## Lapaza (Embedded System Engineer | 2018 - 2019)

Embedded System design for a Smart Parking machine. The hiring company had similar devices and was interested in updating some of its hardware components and adding new software features.

- Custom Linux kernel development, with different peripherals such as a thermal printer, coin counter, 16x4 LCD display, RFID reader, keyboard, electronic actuators, and communication interfaces (`WiFi`, `GPRS`, etc).
- Software application development for smart parking. It involved handling tasks such as system operation modes design (state machine), sensor readings, activation of the actuators, cloud storage, etc.
- Tweaked the embedded OS (`Linux`) to redirect terminal outputs, disable not used peripherals, etc, to protect the company's Intellectual Property.
- Assisted in the PCB redesign for the embedded system operation requirements.
