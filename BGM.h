#pragma once
#include <Novice.h>

class BGM
{
	struct sound
	{
		int VoiceHandle;
		int SoundHandle;
		bool isSound;
		bool isRoop;
		float volume;
		float maxVolume;
		float minVolume;
		float t;
		bool isFadeIn;
		bool isFadeOut;
	};

	enum soundKinds
	{
		Title,
		Select,
		Game,
		GameOver,
		GameClear,
		Manual
	};
	sound sound[6];

	float addT;

public:
	BGM() {

		for (int i = 0; i < 6; i++)
		{
			sound[i].isSound = false;
			sound[i].VoiceHandle = -1;
			sound[i].volume = 0.1f;
			sound[i].maxVolume = 0.1f;
			sound[i].minVolume = 0.0f;
			sound[i].t = 0;
			sound[i].isFadeIn = false;
			sound[i].isFadeOut = false;
		}
		sound[Title].volume = 0.5f;

		sound[Title].isRoop = true;
		sound[Select].isRoop = true;
		sound[Game].isRoop = true;
		sound[GameOver].isRoop = false;
		sound[GameClear].isRoop = false;

		sound[Title].SoundHandle = Novice::LoadAudio("./Resources/sounds/BGMTitle.mp3");
		sound[Select].SoundHandle = Novice::LoadAudio("./Resources/sounds/BGMTitle.mp3");
		sound[Game].SoundHandle = Novice::LoadAudio("./Resources/sounds/BGMgame.mp3");
		sound[GameOver].SoundHandle = Novice::LoadAudio("./Resources/sounds/BGMgameover.mp3");
		sound[GameClear].SoundHandle = Novice::LoadAudio("./Resources/sounds/BGMgameclear.mp3");

		addT = 0.02f;

	};

	void Sound(int scene,int sceneNum);

};