#pragma once
#include <cinttypes>
#include <cstdio>
#include <vector>
#include "Defines.hpp"

struct archive;
struct archive_entry;

namespace ez {
	class ReadArchive {
	public:
		ReadArchive();
		~ReadArchive();

		bool open(FILE * file);
		bool open(const char * filename, size_t blockSize);
		bool open(const void * buffer, size_t bufferSize);

		bool isOpen() const;

		bool close();

		int getFilterCount() const;
		ReadFilter getFilter(int index) const;
		const char* getFilterName(int index) const;

		bool hasEntry() const;
		void nextEntry();
		void skipData();

		// Reads all bytes from the current entry into a vector, and returns it.
		std::vector<char> readData();

		// Reads bytes into the buffer, returns the number written. Returns zero when there are no further bytes to read.
		size_t readData(void * bufferPtr, size_t bufferLen);

		EntryType getEntryType() const;
		const char* getEntryTypeName() const;
		const char* getEntryPath() const;
		const char* getEntryHardLink() const;
		ReadFormat getEntryFormat() const;
		const char* getEntryFormatName() const;

		int processedEntryCount() const;

		int previousErrorCode() const;
		const char* previousErrorString() const;
	private:
		bool createArchive();

		archive* ptr;
		archive_entry* entry;
		int entryErr, formats, filters;
	};
}