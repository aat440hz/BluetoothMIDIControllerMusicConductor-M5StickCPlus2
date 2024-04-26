# Bluetooth MIDI Controller Music Conductor

The Bluetooth MIDI Controller Music Conductor is an innovative tool designed for musicians and music enthusiasts to explore new dimensions of creativity by generating random MIDI notes within selected key signatures. With its distinctive gyroscope and built-in sensors, it allows users to change notes and control expressions through physical movements and taps, making music creation more intuitive and engaging.

## How It Works

The Music Conductor utilizes a combination of a gyroscope and built-in sensors to facilitate dynamic musical interactions:

- **Gyroscope for Note Changes:** Change MIDI notes dynamically based on the orientation and movement of the device. Tilt, rotate, or move the controller to shift between notes, adding an expressive layer to your musical performance.

- **Sensors for MIDI Triggers:** The built-in sensors detect taps and vibrations, acting as MIDI triggers. This feature is perfect for playing percussive notes, executing trills, or adding rhythmic elements to your performance. Tap on the device to play notes or create patterns, adding a tactile and immediate aspect to your music creation.

## Features

### Gyroscope Note Changing

- **Dynamic Note Variation and Expressive Control:** Change between random notes in the selected scale through physical motion using the gyroscope to add an expressive quality to your music.
- **Physical Engagement:** Add a performative element to your compositions by physically interacting with the music.

### Sensor-based MIDI Trigger

- **Tap to Play:** Use the sensors to trigger notes or sounds by tapping on the device.
- **Sensitivity Adjustment:** Customize the sensitivity for different playing styles and environments.
- **Versatile Application:** Ideal for playing trills, percussive elements, or any musical pattern that benefits from a physical touch.

## Dependencies

To ensure smooth operation, you'll need:

1. **MIDIberry (Windows 10):** A MIDI loopback driver to route MIDI data between applications. [Download MIDIberry](http://newbodyfresher.linclip.com/).
2. **loopMIDI (Windows 10):** A tool for creating virtual MIDI ports, facilitating communication between MIDI applications. [Download loopMIDI](https://www.tobias-erichsen.de/software/loopmidi.html).

## Compatibility and Setup Instructions

The Bluetooth MIDI Controller Music Conductor has been confirmed to work well with various setups including Windows 10, Android, and now iPhone devices, providing a versatile tool for musicians and producers.

### For Windows 10 Users:

- **REAPER (or any DAW supporting MIDI):** Tested for reliability and performance.
- **Board Selection:** Use the M5StickC ESP32 board definition from Espressif (`https://dl.espressif.com/dl/package_esp32_index.json`) when working with Windows to resolve connectivity issues. You can also try the M5StickCPlus2 board from M5Stack (`https://m5stack.oss-cn-shenzhen.aliyuncs.com/resource/arduino/package_m5stack_index.json`)

### For Android and iPhone Users:

- **Android: MIDI+BTLE and BandLab.**
- **iPhone: Bluetooth MIDI Connect by KORG and BandLab (available on the Apple Store).**
- **Board Selection for Both Android and iPhone:** Use the M5StickCPlus2 board definition from M5Stack (`https://m5stack.oss-cn-shenzhen.aliyuncs.com/resource/arduino/package_m5stack_index.json`). This board selection has been tested and works well for both Android and iPhone, facilitating a consistent experience across mobile devices.

### General Installation:

1. **Download and Install Necessary Applications:** MIDIberry and loopMIDI for Windows 10, and respective MIDI applications for mobile devices.
2. **Clone the Repository:** Obtain the project files from the GitHub repository.
3. **Set Up Arduino Environment:**
    - Open the project in your Arduino development environment.
    - Select the correct board from the Tools menu based on your target OS (Windows, Android, or iPhone).
    - Upload the code to your M5StickCPlus2.
4. **Hardware Connection:** Connect your M5StickCPlus2 to your computer or mobile device via Bluetooth.
5. **MIDI Configuration:**
    - In your DAW or music production software, configure the MIDI inputs to use the appropriate MIDI driver.
    - Ensure the software is set to receive MIDI from the correct virtual port if using tools like loopMIDI.

## Feedback and Contributions

We encourage users to share their experiences, especially regarding compatibility with different systems and setups. Your feedback helps improve this tool for everyone!

- **Reporting Issues:** Please use the issues section of this GitHub repository for any problems or suggestions.
- **Contributions:** Code improvements and feature suggestions are welcome! Feel free to fork this repository and submit pull requests.

## License

This project is open-source and available under the [MIT License](LICENSE.md).

Enjoy creating music with the Bluetooth MIDI Controller Music Conductor, now compatible with Windows, Android, and iPhone!
