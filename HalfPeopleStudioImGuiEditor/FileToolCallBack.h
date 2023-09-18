#pragma once
#include <vector>
#include <imgui.h>
#include <GLFW/glfw3.h>
#include <lz4.h>
#include <string>
#include <sstream>
#include <thread>
#include <mutex>

#define GLuintToImTextureID (void*)(intptr_t)
namespace FileCallBack
{
	static ImTextureID* DefaultLogo;
	static bool (*HLoadImage1)(const char* filename, ImTextureID& out_texture);
	static bool (*HLoadImage2)(const char* filename, ImVec2& ImageSize, std::vector<unsigned char>& ImageData);
	static bool (*HLoadImage3)(const unsigned char* imageData, ImVec2 ImageSize, GLuint& ImageBuffer);
}

namespace EZ_Tool
{
	static std::mutex ossMutex;  // ����ͬ���� std::ostringstream �Ĳ���

	static void ConvertRangeToString(const std::vector<unsigned char>& data, size_t start, size_t end, std::ostringstream& oss, std::string Offset) {
		std::ostringstream localOss;
		int charsPerLine = 300;
		int charsWritten = 0;

		for (size_t i = start; i < end; ++i) {
			std::ostringstream tempOss;
			if (0 != start && start == i) {
				tempOss << ", ";
			}

			tempOss << "0x" << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(data[i]);

			if (charsWritten != 0) {
				localOss << ", ";
			}
			localOss << tempOss.str();
			charsWritten += 4;

			if (charsWritten >= charsPerLine) {
				localOss << '\n' << Offset << ", ";
				charsWritten = 0;
			}
		}

		std::lock_guard<std::mutex> lock(ossMutex);
		oss << localOss.str();  // ע���ڻ����������½����д���� oss ����
	}

	static std::string VectorToString(const std::vector<unsigned char>& data, std::string Offset) {
		int numThreads = std::thread::hardware_concurrency();  // ��ȡ���õ�Ӳ���߳���
		std::vector<std::thread> threads;

		size_t dataSize = data.size();
		size_t chunkSize = (dataSize + numThreads - 1) / numThreads;  // �������ݷ�Χ�������
		size_t start = 0;
		size_t end = chunkSize;
		std::vector<std::ostringstream> Buffers(numThreads);
		for (int i = 0; i < numThreads; ++i) {
			if (end > dataSize) {
				end = dataSize;  // ���һ���̴߳���ʣ�������
			}
			threads.emplace_back(ConvertRangeToString, std::ref(data), start, end, std::ref(Buffers[i]), Offset);
			start = end;
			end += chunkSize;
		}

		for (auto& thread : threads) {
			thread.join();  // �ȴ������߳����
		}
		std::ostringstream oss;
		for (auto& ossBuffer : Buffers)
		{
			oss << ossBuffer.str();
			ossBuffer.clear();
		}
		std::string result = oss.str();
		return result;
	}

	static int GetRecommendedSizes(int Input)
	{
		if (Input < 32)
		{
			return 16;
		}
		else if (Input > 32 && Input < 128)
		{
			return 32;
		}
		else if (Input > 128 && Input < 512)
		{
			return 512;
		}
		else if (Input > 512 && Input < 800)
		{
			return 512;
		}
		else if (Input > 800 && Input < 1024)
		{
			return 512;
		}
		else
		{
			return 1024;
		}
	}

#include <stdexcept>

	static std::vector<long long> compressLZ4(const std::vector<unsigned char>& inputData) {
		// ����ѹ�������󻺳�����С
		int maxCompressedSize = LZ4_compressBound(inputData.size());

		// ����ѹ�������ݵĻ�����
		std::vector<unsigned char> compressedData(maxCompressedSize);

		// ����ѹ��
		int compressedSize = LZ4_compress_default(
			reinterpret_cast<const char*>(inputData.data()),  // �������ݵ�ָ��
			reinterpret_cast<char*>(compressedData.data()),   // ���ѹ�����ݵ�ָ��
			inputData.size(),                                  // �������ݵĴ�С
			compressedData.size()                             // ����������Ĵ�С
		);

		if (compressedSize < 0) {
			throw std::runtime_error("LZ4 compression failed.");
		}

		// ����ѹ�������ݵĴ�С
		compressedData.resize(compressedSize);

		std::vector<long long> Buffer(compressedSize);
		memcpy(Buffer.data(), compressedData.data(), compressedSize);

		return Buffer;
	}

	static std::vector<unsigned char> decompressLZ4(const std::vector<long long>& Data, int originalSize) {
		std::vector<unsigned char> compressedData(Data.size() * sizeof(long long));
		memcpy(compressedData.data(), Data.data(), compressedData.size());

		std::vector<unsigned char> decompressedData(originalSize);

		// ���н�ѹ��
		int decompressedSize = LZ4_decompress_safe(
			reinterpret_cast<const char*>(compressedData.data()),   // ����ѹ�����ݵ�ָ��
			reinterpret_cast<char*>(decompressedData.data()),       // �����ѹ�����ݵ�ָ��
			compressedData.size(),                                   // ����ѹ�����ݵĴ�С
			originalSize                                             // ����������Ĵ�С
		);

		// ������ѹ�����ݵĴ�С
		if (decompressedSize >= 0 && decompressedSize <= originalSize) {
			decompressedData.resize(decompressedSize);
		}
		else {
			// �����ѹ��ʧ�ܵ����
			// ������Ը���ʵ��������д�����
			// �����׳��쳣�򷵻�һ���ض��Ĵ����ʶ
		}

		return decompressedData;
	}
}