#include "BGM.h"

void BGM::Sound(int scene, int sceneNum)
{
	if (scene <= Select || scene == Manual)
		scene = Title;
	if (sceneNum <= Select || sceneNum == Manual)
		sceneNum = Title;

	if (scene == sceneNum && !sound[scene].isFadeOut)
	{
		sound[scene].isFadeIn = true;
	}

	if (scene != sceneNum)
	{
		sound[scene].isFadeOut = true;
	}

	if (sound[scene].isFadeOut)
	{
		sound[scene].t += addT;
		sound[scene].volume = (1.0f - sound[scene].t) * sound[scene].maxVolume + sound[scene].t * sound[scene].minVolume;
		Novice::SetAudioVolume(sound[scene].VoiceHandle, sound[scene].volume);
		if (sound[scene].t >= 1.0f)
		{
			sound[scene].t = 0;
			sound[scene].isFadeOut = false;
		}
	}
	if (sound[scene].isFadeIn)
	{
		sound[scene].t += addT / 2.0f;
		sound[scene].volume = (1.0f - sound[scene].t) * sound[scene].minVolume + sound[scene].t * sound[scene].maxVolume;
		Novice::SetAudioVolume(sound[scene].VoiceHandle, sound[scene].volume);
		if (sound[scene].t >= 1.0f)
		{
			sound[scene].t = 1;
			sound[scene].isFadeIn = false;
		}
	}


	for (int i = 0; i < 6; i++)
	{
		if (scene != i)
		{
			Novice::StopAudio(sound[i].VoiceHandle);
		}
	}

	if (!Novice::IsPlayingAudio(sound[scene].VoiceHandle) || sound[scene].VoiceHandle == -1)
	{
		sound[scene].VoiceHandle = Novice::PlayAudio(sound[scene].SoundHandle, sound[scene].isRoop, sound[scene].volume);
	}

}


