#pragma once

enum class CHANNEL :int
{
	CH1,
	CH2,
	CH3,
	CH4,
	CH5,
	CH6,
	CH7,
	CH8,
	CH9,
	CH10,
	CH11,
	CH12,
	CH13,
	CH14,
	CH15,
	CH16,
	
	LAST,
};

constexpr int CHANNEL_MAX_COUNT = (int)(CHANNEL::LAST);

struct SoundMap
{
	MCI_OPEN_PARMSA parms;
	std::string filename;
};

class Sound
{
public:
	void Reset();
	void Destroy();
	
	// (최적화) 프로그램 시작 후, 미리 MCI_OPEN_PARMSA을 생성하는 함수
	void RegisterSound(const std::string& key, const std::string& filename);

	void Play(CHANNEL channel, const std::string key, bool isLoop = false);
	void Stop(CHANNEL channel);
	void Resume(CHANNEL channel);
	void Close(CHANNEL channel);

	// ratio: [0.0, 1.0]
	void SetVolume(CHANNEL channel, float ratio);
	bool IsPlaying(CHANNEL channel);

private:
	std::map<std::string, SoundMap> _fileContainer = {};
	MCIDEVICEID _soundId[CHANNEL_MAX_COUNT] = {};
};
