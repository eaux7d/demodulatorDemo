#pragma once
#include <cstdint>
#include <string>
#include "DemodulateLibTypes.h"

enum FormatCode
{
	default = 0,
	int8,
	int16,
	int32,
	float32
};

struct WaveFileHeader 
{
	int32_t chunkId;
	int32_t chunkSize;
	int32_t format;

	int32_t subchunk1Id;
	int32_t subchunk1Size;
	int16_t audioFormat;
	int16_t numChannels;
	int32_t sampleRate;
	int32_t byteRate;
	int16_t blockAlign;
	int16_t bitsPerSample;

	int32_t subchunk2Id;
	int32_t subchunk2Size;

};

struct WaveFile
{
	WaveFile() :data(0) { }
	~WaveFile() { if (data) delete[] ((float*) data); }

	void ReadWav(const std::string & filename);
	void ReadFileInfo() const;
	void WriteWaveFile(std::ofstream & fout) const;
	void UpdateWav(size_t filesizebytes, int16_t audioFormat, int16_t numChannels, int32_t sampleRate, int32_t byteRate, int16_t bitsPerSample, void * newdata);



private:
	template <typename T> std::vector<T> PrepareData() const;

private:
	WaveFileHeader header;
	void * data;

	std::string filename;
	float duration;
	size_t countSize;
	FormatCode fmt;
};



template<typename T>
inline std::vector<T> WaveFile::PrepareData() const
{
	std::vector<T> vec;
	vec.resize(header.subchunk2Size / sizeof(T));
	memcpy(&vec[0], data, header.subchunk2Size);

	return vec;
}


