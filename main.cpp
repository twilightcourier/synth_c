#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "sound.h"

using namespace std;

int main() {
	sf::RenderWindow window(sf::VideoMode(800, 600), "my window");

	sf::SoundBuffer buffer;
	vector<sf::Int16> samples;
	
	for (int i = 0; i < 44100; i++) {
		//samples.push_back(sound::SineWave(i, 440, 0.9));
		//samples.push_back(sound::SquareWave(i, 440, 0.9));
		samples.push_back(sound::Noise(0.9));
	}

	buffer.loadFromSamples(&samples[0], samples.size(), 1, 44100);
	buffer.loadFromSamples(&samples[0], samples.size(), 1, 44100);
	if (!sf::SoundBufferRecorder::isAvailable())
	{
		// error: audio capture is not available on this system
		(...);
	}

	// create the recorder
	sf::SoundBufferRecorder recorder;
		// start the capture
	recorder.start();

	// wait...
	sf::Sound sound;
	sound.setBuffer(buffer);
	sound.play();
	// stop the capture
	recorder.stop();
		// retrieve the buffer that contains the captured audio data
	const sf::SoundBuffer& buffer = recorder.getBuffer();
	buffer.saveToFile("my_record.wav");
	
	while (window.isOpen()) {
		sf::Event event;
		
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
	}

	return 0;
}