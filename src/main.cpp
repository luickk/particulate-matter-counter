#include <Arduino.h>
#include <SDS011.h>

float p10, p25;
int error;

int sound_out=10;

// Random Volume - defines the random gen. volume
// Random Delay - defines the random gen. time between the random clicks
// "background radiation" 200
// "medium": 100
// "dangerous": 50
int ran_delay_vol = 200;


SDS011 my_sds;

void setup() {
	my_sds.begin(3, 2); //RX, TX
	Serial.begin(9600);

	randomSeed(analogRead(0));
	pinMode(sound_out, OUTPUT);
	digitalWrite(sound_out, LOW);
}
int ranNumVol;
int randNumber;
void loop() {

	error = my_sds.read(&p25, &p10);
	if (!error) {
		//particulate matter 2.5  (partical size) - health critical
		Serial.println("P2.5: " + String(p25));
		ran_delay_vol = 200-int(p25);
		if(ran_delay_vol<30){
			ran_delay_vol=30;
		}
		if(p25>400){
			ran_delay_vol=10;
		}
		//particulate matter 10 (partical size)
		//Serial.println("P10:  " + String(p10));
	}

	ranNumVol = random (ran_delay_vol);
	digitalWrite(sound_out, ranNumVol);
	randNumber = random(ran_delay_vol);
	delay(randNumber);
	digitalWrite(sound_out, LOW);
	
	//Serial.println(String(ran_delay_vol));

	//delay(50);
}