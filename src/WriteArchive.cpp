#include "ez/archive/WriteArchive.hpp"
#include <archive.h>
#include <archive_entry.h>

namespace ez {
	WriteArchive::WriteArchive()
		: ptr(nullptr)
		, entry(nullptr)
		, entryErr(ARCHIVE_OK)
		, format(0)
		, filter(0)
	{}
	WriteArchive::~WriteArchive()
	{}

	bool WriteArchive::open(FILE* file) {
		return false;
	}
	bool WriteArchive::open(const char* filename, size_t blockSize) {
		return false;
	}
	bool WriteArchive::open(const void* buffer, size_t bufferSize) {
		return false;
	}

	bool WriteArchive::isOpen() const {
		return ptr != nullptr;
	}

	bool WriteArchive::close() {
		if (!isOpen()) {
			return false;
		}



		return true;
	}

	bool WriteArchive::hasEntry() const {
		return entry != nullptr;
	}
	void WriteArchive::nextEntry() {

	}
	bool WriteArchive::writeData(const void*& bufferPtr, size_t& bufferLen) {
		return false;
	}

	const char* WriteArchive::getEntryPath() const {
		if (hasEntry()) {
			return archive_entry_pathname(entry);
		}
		else {
			return "";
		}
	}
	void WriteArchive::setEntryPath(const char* path) {
		if (hasEntry()) {
			archive_entry_set_pathname(entry, path);
		}
	}

	void WriteArchive::setEntryType(EntryType type) {
		if (hasEntry()) {
			int _type = AE_IFREG;
			switch (type) {
			case EntryType::File:
				_type = AE_IFREG;
			case EntryType::SymLink:
				_type = AE_IFLNK;
			case EntryType::Socket:
				_type = AE_IFSOCK;
			case EntryType::CharacterDevice:
				_type = AE_IFCHR;
			case EntryType::BlockDevice:
				_type = AE_IFBLK;
			case EntryType::Directory:
				_type = AE_IFDIR;
			case EntryType::NamedPipe:
				_type = AE_IFIFO;
			}

			archive_entry_set_filetype(entry, _type);
		}
	}
	EntryType WriteArchive::getEntryType() const {
		if (hasEntry()) {
			int _type = archive_entry_filetype(entry);
			switch (_type) {
			case AE_IFLNK:
				return EntryType::SymLink;
			case AE_IFSOCK:
				return EntryType::Socket;
			case AE_IFCHR:
				return EntryType::CharacterDevice;
			case AE_IFBLK:
				return EntryType::BlockDevice;
			case AE_IFDIR:
				return EntryType::Directory;
			case AE_IFIFO:
				return EntryType::NamedPipe;
			default://case AE_IFREG:
				return EntryType::File;
			}
		}
		else {
			return EntryType::None;
		}
	}

	int WriteArchive::previousErrorCode() const {
		return entryErr;
	}
	const char* WriteArchive::previousErrorString() const {
		return archive_error_string(ptr);
	}
}
