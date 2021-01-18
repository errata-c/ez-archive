#pragma once
#include "Defines.hpp"

struct archive;
struct archive_entry;

namespace ez {
	class WriteArchive {
	public:
		WriteArchive();
		~WriteArchive();

		bool open(FILE* file);
		bool open(const char* filename, size_t blockSize);
		bool open(const void* buffer, size_t bufferSize);

		bool isOpen() const;

		bool close();
		
		bool hasEntry() const;
		void nextEntry();

		bool writeData(const void*& bufferPtr, size_t& bufferLen);

		const char* getEntryPath() const;
		void setEntryPath(const char * path);

		void setEntryType(EntryType type);
		EntryType getEntryType() const;



		int previousErrorCode() const;
		const char* previousErrorString() const;
	private:
		archive* ptr;
		archive_entry* entry;
		int entryErr, format, filter;
	};
}