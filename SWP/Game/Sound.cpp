#include "stdafx.h"
#include "Sound.h"

void Sound::Reset()
{
}

void Sound::Destroy()
{
}

void Sound::RegisterSound(const std::string& key, const std::string& filename)
{
	MCI_OPEN_PARMSA mciOpen = {};
	std::string name = "";
	std::string extension = "";

	bool dot = false;
	for (int i = filename.size() - 1; i >= 0; --i)
	{
		if (filename[i] == '.' && !dot)
		{
			dot = true;
			continue;
		}

		if (!dot)
			extension = filename[i] + extension;
		else
			name = filename[i] + name;
	}

	 // DEBUG_MSG("name: %s | extension : %s", name.data(), extension.data());

	// mpegvideo : mp3
	// waveaudio : wav
	// avivideo : avi
	if (extension == "mp3")
		mciOpen.lpstrDeviceType = "mpegvideo";
	else if (extension == "wav")
		mciOpen.lpstrDeviceType = "waveaudio";
	else
		mciOpen.lpstrDeviceType = "avivideo";

	mciOpen.lpstrElementName = filename.data();

	SoundMap map = {};
	map.filename = filename;
	map.parms = mciOpen;

	_fileContainer[key] = map;
}

void Sound::Play(CHANNEL channel, const std::string key, bool isLoop)
{
	if (_soundId[(int)(channel)] != 0)
		Close(channel);

	MCI_OPEN_PARMSA parms = _fileContainer[key].parms;
	parms.lpstrElementName = _fileContainer[key].filename.data();

	mciSendCommandA(0, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, (DWORD_PTR)&parms);
	_soundId[(int)(channel)] = parms.wDeviceID;

	MCI_PLAY_PARMS mciPlay = {};
	mciSendCommandA(_soundId[(int)(channel)], MCI_PLAY, isLoop ? MCI_DGV_PLAY_REPEAT : MCI_NOTIFY, (DWORD_PTR)&mciPlay);
}

void Sound::Stop(CHANNEL channel)
{
	MCI_PLAY_PARMS mciPlay = {};
	mciSendCommandA(_soundId[(int)(channel)], MCI_PAUSE, MCI_NOTIFY, (DWORD_PTR)&mciPlay);
}

void Sound::Resume(CHANNEL channel)
{
	mciSendCommandA(_soundId[(int)(channel)], MCI_RESUME, 0, NULL);
}

void Sound::Close(CHANNEL channel)
{
	mciSendCommandA(_soundId[(int)(channel)], MCI_CLOSE, 0, NULL);
	_soundId[(int)(channel)] = 0;
}

void Sound::SetVolume(CHANNEL channel, float ratio)
{
	int clippedRatio = (int)(ratio * 1000.0F);
	MCI_DGV_SETAUDIO_PARMS mciSetAudioParms = {};
	mciSetAudioParms.dwItem = MCI_DGV_SETAUDIO_VOLUME;
	mciSetAudioParms.dwValue = clippedRatio; // [0, 1000]

	mciSendCommandA(_soundId[(int)(channel)], MCI_SETAUDIO, MCI_DGV_SETAUDIO_VALUE | MCI_DGV_SETAUDIO_ITEM, (DWORD_PTR)&mciSetAudioParms);
}

bool Sound::IsPlaying(CHANNEL channel)
{
	MCI_STATUS_PARMS mciStatusParms = {};
	mciStatusParms.dwItem = MCI_STATUS_MODE;

	mciSendCommand(_soundId[(int)(channel)], MCI_STATUS, MCI_STATUS_ITEM, (DWORD_PTR)&mciStatusParms);

	return (mciStatusParms.dwReturn == MCI_MODE_PLAY);
}
