#include "stdafx.h"
#include "Sound.h"

void Sound::Start()
{
	// lpstrDeviceType의 종류
	// mpegvideo : mp3
	// waveaudio : wav
	// avivideo : avi

	MCI_OPEN_PARMSA mciOpen = {};
	mciOpen.lpstrDeviceType = "mpegvideo";
	mciOpen.lpstrElementName = "test.mp3";
	mciSendCommandA(0, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, (DWORD_PTR)&mciOpen);

	// 재생
	// MCI_NOTIFY : 기본
	// MCI_DGV_PLAY_REPEAT : 반복
	MCI_PLAY_PARMS mciPlay = {};
	mciSendCommandA(mciOpen.wDeviceID, MCI_PLAY, MCI_NOTIFY, (DWORD_PTR)&mciPlay);

	// 볼륨을 설정합니다
	MCI_DGV_SETAUDIO_PARMS mciSetAudioParams = {};
	mciSetAudioParams.dwItem = MCI_DGV_SETAUDIO_VOLUME;
	mciSetAudioParams.dwValue = 500; // [0, 1000]

	mciSendCommandA(mciOpen.wDeviceID, MCI_SETAUDIO, MCI_DGV_SETAUDIO_VALUE | MCI_DGV_SETAUDIO_ITEM, (DWORD_PTR)&mciSetAudioParams);

	// 일시정지
	mciSendCommandA(mciOpen.wDeviceID, MCI_PAUSE, MCI_NOTIFY, (DWORD_PTR)&mciPlay);

	// 다시시작
	mciSendCommandA(mciOpen.wDeviceID, MCI_RESUME, 0, NULL);

	MCI_STATUS_PARMS mciStatusParms = {};
	mciStatusParms.dwItem = MCI_STATUS_MODE;

	mciSendCommandA(mciOpen.wDeviceID, MCI_STATUS, MCI_STATUS_ITEM, (DWORD_PTR)&mciStatusParms);

	if (mciStatusParms.dwReturn == MCI_MODE_PLAY)
		DEBUG_PRINT("현재 음악이 재생중이군 !\n")

		// 정지
		// mciSendCommandA(mciOpen.wDeviceID, MCI_CLOSE, 0, NULL);
}