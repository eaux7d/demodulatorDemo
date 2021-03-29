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
	void ReadWav(const std::string & filename);
	void WriteFileInfo() const;
	void WriteWaveFile(const std::ofstream & fout) const;

private:
	WaveFileHeader header;
	void * data;

	std::string filename;
	float duration;
	size_t countSize;
	FormatCode fmt;
};