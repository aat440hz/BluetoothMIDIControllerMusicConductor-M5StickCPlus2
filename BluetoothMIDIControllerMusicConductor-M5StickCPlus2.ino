#include <M5StickCPlus2.h>
#include <Arduino.h>
#include <BLEMIDI_Transport.h>
#include <hardware/BLEMIDI_ESP32_NimBLE.h>

BLEMIDI_CREATE_DEFAULT_INSTANCE()

bool isConnected = false;
bool notePlaying = false;
int currentNote = -1;
const int maxNotes = 1;
int playingNotes[maxNotes];
int numPlayingNotes = 0;

int currentKeyIndex = 0;
const int numKeys = 13;

// Define the scales for each key signature
int cMinorScale[] = {48, 50, 51, 53, 55, 56, 58, 60, 62, 63, 65, 67};
int cSharpMinorScale[] = {49, 51, 52, 54, 56, 57, 59, 61, 63, 64, 66, 68};
int dMinorScale[] = {50, 52, 53, 55, 57, 58, 60, 62, 64, 65, 67, 69};
int dSharpMinorScale[] = {51, 53, 54, 56, 58, 59, 61, 63, 65, 66, 68, 70};
int eMinorScale[] = {52, 54, 55, 57, 59, 60, 62, 64, 66, 67, 69, 71};
int fMinorScale[] = {53, 55, 56, 58, 60, 61, 63, 65, 67, 68, 70, 72};
int fSharpMinorScale[] = {54, 56, 57, 59, 61, 62, 64, 66, 68, 69, 71, 73};
int gMinorScale[] = {55, 57, 58, 60, 62, 63, 65, 67, 69, 70, 72, 74};
int gSharpMinorScale[] = {56, 58, 59, 61, 63, 64, 66, 68, 70, 71, 73, 75};
int aMinorScale[] = {57, 59, 60, 62, 64, 65, 67, 69, 71, 72, 74, 76};
int aSharpMinorScale[] = {58, 60, 61, 63, 65, 66, 68, 70, 72, 73, 75, 77};
int bMinorScale[] = {59, 61, 62, 64, 66, 67, 69, 71, 73, 74, 76, 78};
int chromaticScale[] = {48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59};

int bButtonPressCount = 0;
unsigned long lastBButtonPressTime = 0;
const unsigned long debounceDelay = 200;

float ax, ay, az; // Accelerometer values

float lastGx = 0;
bool peakDetected = false;
const float peakThreshold = 9.9; // Adjust this value based on your testing

void setup() {
  M5.begin();
  M5.Lcd.setRotation(1);
  MIDI.begin(MIDI_CHANNEL_OMNI);

  BLEMIDI.setHandleConnected([]() {
    isConnected = true;
    // You might want to add some code here to handle when the device connects.
  });

  BLEMIDI.setHandleDisconnected([]() {
    isConnected = false;
    // You might want to add some code here to handle when the device disconnects.
  });

  M5.Imu.init();
  updateDisplay();
}

void loop() {
  M5.update();
  BLEMIDI.read();

  float gx, gy, gz;
  M5.Imu.getGyroData(&gx, &gy, &gz);
  M5.Imu.getAccelData(&ax, &ay, &az);

  if (isConnected) {
    if (M5.BtnA.isPressed()) {
      if (!notePlaying) {
        changeNote();
        notePlaying = true;
      }

      float deltaGx = gx - lastGx;

      if ((lastGx < 0 && gx > 0 && abs(deltaGx) > peakThreshold) || 
          (lastGx > 0 && gx < 0 && abs(deltaGx) > peakThreshold)) {
        peakDetected = true;
      } else {
        peakDetected = false;
      }

      if (peakDetected) {
        for (int i = 0; i < numPlayingNotes; i++) {
          MIDI.sendNoteOff(playingNotes[i], 0, 1);
        }
        numPlayingNotes = 0;
        notePlaying = false;
      }
    } else if (notePlaying) {
      for (int i = 0; i < numPlayingNotes; i++) {
        MIDI.sendNoteOff(playingNotes[i], 0, 1);
      }
      numPlayingNotes = 0;
      notePlaying = false;
    }

    if (M5.BtnB.wasReleased()) {
      unsigned long currentMillis = millis();
      if (currentMillis - lastBButtonPressTime > debounceDelay) {
        lastBButtonPressTime = currentMillis;
        bButtonPressCount++;
        if (bButtonPressCount >= 3) {
          currentKeyIndex = (currentKeyIndex + 1) % numKeys;
          updateDisplay();
          bButtonPressCount = 0;
        }
      }
    }
  }

  lastGx = gx;
}

void changeNote() {
  int randomIndex = random(12);
  currentNote = getScaleForCurrentKey()[randomIndex];
  
  // Calculate the magnitude of acceleration
  float magnitude = sqrt(ax * ax + ay * ay + az * az);
  
  // Map the magnitude to MIDI velocity range (0-127). Adjust scaling as needed.
  int velocity = map(magnitude, 0, 4, 0, 127); // Adjust the '20' as per your max expected acceleration
  velocity = constrain(velocity, 64, 127); // Ensure the velocity is within MIDI range

  MIDI.sendNoteOn(currentNote, velocity, 1);

  if (numPlayingNotes < maxNotes) {
    playingNotes[numPlayingNotes] = currentNote;
    numPlayingNotes++;
  }
}

void updateDisplay() {
  M5.Lcd.fillScreen(TFT_BLACK);
  M5.Lcd.setTextSize(2); // Increase text size
  M5.Lcd.setTextColor(TFT_WHITE);
  M5.Lcd.setCursor(10, 10); // Adjust the cursor position
  M5.Lcd.println("Current Key:");
  M5.Lcd.setCursor(20, 60);
  M5.Lcd.println(getKeyString(currentKeyIndex));
}

int* getScaleForCurrentKey() {
  switch (currentKeyIndex) {
    case 0: return cMinorScale;
    case 1: return cSharpMinorScale;
    case 2: return dMinorScale;
    case 3: return dSharpMinorScale;
    case 4: return eMinorScale;
    case 5: return fMinorScale;
    case 6: return fSharpMinorScale;
    case 7: return gMinorScale;
    case 8: return gSharpMinorScale;
    case 9: return aMinorScale;
    case 10: return aSharpMinorScale;
    case 11: return bMinorScale;
    case 12: return chromaticScale;
    default: return cMinorScale; // Default to C Minor/Eb Major
  }
}

String getKeyString(int keyIndex) {
  switch (keyIndex) {
    case 0: return "C Minor/Eb Major";
    case 1: return "C# Minor/E Major";
    case 2: return "D Minor/F Major";
    case 3: return "D# Minor/F# Major";
    case 4: return "E Minor/G Major";
    case 5: return "F Minor/Ab Major";
    case 6: return "F# Minor/A Major";
    case 7: return "G Minor/Bb Major";
    case 8: return "G# Minor/B Major";
    case 9: return "A Minor/C Major";
    case 10: return "A# Minor/C# Major";
    case 11: return "B Minor/D Major";
    case 12: return "Chromatic";
  }
}