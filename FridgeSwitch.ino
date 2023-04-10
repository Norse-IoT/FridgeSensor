const int REED_PIN = 23;	// reed switch pin power
//ground 38
const int LED_PIN = 22;// led pin

const int BUZZER_PIN = 32;//buzzer pin

#include "pitches.h"
// notes in the melody:
int melody[] = {
  NOTE_E5, NOTE_E5, NOTE_E5,
  NOTE_E5, NOTE_E5, NOTE_E5,
  NOTE_E5, NOTE_G5, NOTE_C5, NOTE_D5,
  NOTE_E5,
  NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5,
  NOTE_F5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5,
  NOTE_E5, NOTE_D5, NOTE_D5, NOTE_E5,
  NOTE_D5, NOTE_G5
};

// note durations: 4 = quarter note, 8 = eighth note, etc, also called tempo:
int noteDurations[] = {
  8, 8, 4,
  8, 8, 4,
  8, 8, 8, 8,
  2,
  8, 8, 8, 8,
  8, 8, 8, 16, 16,
  8, 8, 8, 8,
  4, 4
};


void setup() {
	Serial.begin(9600);
	pinMode(REED_PIN, INPUT_PULLUP);	// Enable internal pull-up for the reed switch
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

}

void loop() {
	int fridgeStatus = digitalRead(REED_PIN); // Read the state of the switch

  if (fridgeStatus == LOW) {// If the pin reads low, the fridge is open
      Serial.println("beginning of timer");
      delay(5000);//wait 5 seconds
      Serial.println("end of timer");
      fridgeStatus = digitalRead(REED_PIN);//check if fridge got closed
      if(fridgeStatus == LOW){
        Serial.println("Fridge open");
		    digitalWrite(LED_PIN, HIGH);	// Turn the LED on
        playMelody();//play buzzer
    }
  }

	else {
		Serial.println("Fridge closed");
		digitalWrite(LED_PIN, LOW);		// Turn the LED off
	}
}

	
	


void playMelody() {
  // iterate over the notes of the melody:
  int size = sizeof(noteDurations) / sizeof(int);

  for (int thisNote = 0; thisNote < size; thisNote++) {
    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(BUZZER_PIN, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(BUZZER_PIN);
  }
}
