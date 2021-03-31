#include <iostream>
#include <fstream>
#include <string.h>
#include "WaveFormat.h"


size_t getSampleSize(FormatCode code)
{
	switch (code)
	{
		case(FormatCode::int8):
			return sizeof(int8_t);

		case(FormatCode::int16):
			return sizeof(int16_t);

		case(FormatCode::int32):
			return sizeof(int32_t);

		case(FormatCode::float32):
			return sizeof(float);

		case(FormatCode::default):
		default:
			return 0;
	}

	return 0;
}

std::string getSampleType(FormatCode code)
{
	switch (code)
	{
	case(FormatCode::int8):
		return std::string("int 8");

	case(FormatCode::int16):
		return std::string("int 16");

	case(FormatCode::int32):
		return std::string("int 32");

	case(FormatCode::float32):
		return std::string("float 32");

	case(FormatCode::default):
	default:
		return std::string("unknown format");
	}

	return std::string("unknown format");
}

void WaveFile::ReadWav(const std::string & fname)
{
	filename = fname;
	
	//read the header
	std::fstream in(filename, std::fstream::binary | std::fstream::in);
	in.read((char *)&header, sizeof(WaveFileHeader) - sizeof(int32_t));

	switch (header.audioFormat)
	{
		//PCM
		case(0x0001):
		{
			if (header.bitsPerSample == 8)
			{
				fmt = FormatCode::int8;
				break;
			}

			if (header.bitsPerSample == 16)
			{
				fmt = FormatCode::int16;
				break;
			}

			if (header.bitsPerSample == 32)
			{
				fmt = FormatCode::int32;
				break;
			}
		}

		//IEEE float
		case(0x0003):
		{
			if (header.bitsPerSample == 32)
			{
				fmt = FormatCode::float32;
			}
			break;
		}
	}

	//if subchunk2id is not 'data'
	while (!((char)header.subchunk2Id == 'd' && (char)(header.subchunk2Id >> 8) == 'a' && (char)(header.subchunk2Id >> 16) == 't' && (char)(header.subchunk2Id >> 24) == 'a'))
	{
		in.read((char*)&header.subchunk2Id, sizeof(int32_t));
	}


	int32_t tempSubchunk2Size;

	//read the data size
	in.read((char*)&tempSubchunk2Size, sizeof(int32_t));

	if (data)
	{
		if (header.subchunk2Size != tempSubchunk2Size)
		{
			delete[] data;
			data = nullptr;
		}
	}

	header.subchunk2Size = tempSubchunk2Size;


	countSize = header.subchunk2Size / header.blockAlign;
	duration = countSize /(float) header.sampleRate;

	data = (void *) new int32_t[header.subchunk2Size / sizeof(int32_t)];

	in.read((char *)data, header.subchunk2Size);

	std::cout << "Done\n";
}



void WaveFile::ReadFileInfo() const
{
	std::cout << "--Wav File Information--\n";
	std::cout << "1. Full File Name: " << filename << "\n";
	std::cout << "2. There are " << countSize << " samples in file and the type of sample is " << getSampleType(fmt)<<"\n";
	std::cout << "3. There are " << header.numChannels << " channels in file (" << ((header.numChannels == 1) ? "Mono" : "Stereo") << " Mode) \n";
	std::cout << "4. File frequency is " << header.sampleRate << "\n";
	std::cout << "5. There are " << header.bitsPerSample << "bits per sample for all channels\n";
	std::cout << "6. File duration is " << duration << " s\n";

	std::cout << "\n--Header stuff--\n";

	std::cout << "1. Chunk Id: ";
	printf("%c%c%c%c\n", header.chunkId, header.chunkId >> 8, header.chunkId >> 16, header.chunkId >> 24);

	std::cout << "2. Chunck Size: " << header.chunkSize<<"\n";

	std::cout << "3. Format : ";
	printf("%c%c%c%c\n", header.format, header.format >> 8, header.format >> 16, header.format >> 24);

	std::cout << "4. Subchunk1 Id: ";
	printf("%c%c%c%c\n", header.subchunk1Id, header.subchunk1Id >> 8, header.subchunk1Id >> 16, header.subchunk1Id >> 24);

	std::cout << "5. Subchunck1 Size: " << header.subchunk1Size << "\n";

	std::cout << "6. Audio Format: " << header.audioFormat<<"\n";

	std::cout << "7. Num Channels: " << header.numChannels << "\n";

	std::cout << "8. Sample Rate: " << header.sampleRate << "\n";

	std::cout << "9. Byte Rate: " << header.byteRate << "\n";

	std::cout << "10. Block Align: " << header.blockAlign << "\n";

	std::cout << "11. Bits Per Sample: " << header.bitsPerSample << "\n";

	std::cout << "12. Subchunk2 Id: ";
	printf("%c%c%c%c\n", header.subchunk2Id, header.subchunk2Id >> 8, header.subchunk2Id >> 16, header.subchunk2Id >> 24);

	std::cout << "13. Subchunck2 Size: " << header.subchunk2Size << "\n";

}



void WaveFile::WriteWaveFile(std::ofstream & fout) const
{
	//Write Header
	fout.write((char *)this, sizeof(*this));

	//WriteData
	fout.write((char *)data, header.subchunk2Size);
}


void WaveFile::UpdateWav(size_t datasizebytes, int16_t audioFormat, int16_t numChannels, int32_t sampleRate, int32_t byteRate, int16_t bitsPerSample, void * newdata)
{
	header.chunkId = 0x52494646;
	header.chunkSize = datasizebytes + 44 - 8; //for pcm
	header.format = 0x57415645;
	header.subchunk1Id = 0x666d7420;

	header.audioFormat = audioFormat;
	header.subchunk1Size = 16;//for pcm! fix

	header.numChannels = numChannels;
	header.sampleRate = sampleRate;
	header.byteRate = byteRate;

	header.bitsPerSample = bitsPerSample;
	header.blockAlign = header.byteRate / header.sampleRate;

	header.subchunk2Id = 0x64617461;

	if (header.subchunk2Size != datasizebytes)
	{
		header.subchunk2Size = datasizebytes;

		if (data) 
		{
			delete[] data;
			data = nullptr;
		}
			
	}

	data = (void *) new int32_t[header.subchunk2Size / sizeof(int32_t)];

	memcpy(data, newdata, header.subchunk2Size);
}