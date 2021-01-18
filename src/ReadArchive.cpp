#include "ez/archive/ReadArchive.hpp"
#include <archive.h>
#include <archive_entry.h>
#include <cstdio>
#include <cassert>

namespace ez {
	ReadArchive::ReadArchive()
		: ptr(nullptr)
		, entry(nullptr)
		, entryErr(ARCHIVE_EOF)
		, formats((int)ReadFormat::all)
		, filters((int)ReadFilter::all)
	{}
	ReadArchive::~ReadArchive()
	{
		if (isOpen()) {
			close();
		}
	}

	bool ReadArchive::open(FILE * file) {
		if (isOpen()) {
			if (!close()) {
				return false;
			}
		}

		if (!createArchive()) {
			return false;
		}

		int err = archive_read_open_FILE(ptr, file);
		if (err != ARCHIVE_OK) {
			archive_read_free(ptr);
			ptr = nullptr;

			return false;
		}

		entry = archive_entry_new();
		if (entry == nullptr) {
			archive_read_free(ptr);
			ptr = nullptr;

			return false;
		}

		entryErr = archive_read_next_header2(ptr, entry);
		return true;
	}
	bool ReadArchive::open(const char* filename, size_t blockSize) {
		if (isOpen()) {
			if (!close()) {
				return false;
			}
		}

		if (!createArchive()) {
			return false;
		}

		int err = archive_read_open_filename(ptr, filename, blockSize);
		if (err != ARCHIVE_OK) {
			archive_read_free(ptr);
			ptr = nullptr;

			return false;
		}

		entry = archive_entry_new();
		if (entry == nullptr) {
			archive_read_free(ptr);
			ptr = nullptr;

			return false;
		}

		entryErr = archive_read_next_header2(ptr, entry);
		return true;
	}

	bool ReadArchive::open(const void* buffer, size_t bufferSize) {
		if (isOpen()) {
			if (!close()) {
				return false;
			}
		}

		if (!createArchive()) {
			return false;
		}

		int err = archive_read_open_memory(ptr, buffer, bufferSize);
		if (err != ARCHIVE_OK) {
			archive_read_free(ptr);
			ptr = nullptr;

			return false;
		}

		entry = archive_entry_new();
		if (entry == nullptr) {
			archive_read_free(ptr);
			ptr = nullptr;

			return false;
		}

		entryErr = archive_read_next_header2(ptr, entry);
		return true;
	}

	bool ReadArchive::isOpen() const {
		return ptr != nullptr;
	}

	int ReadArchive::getFilterCount() const {
		if (isOpen()) {
			return archive_filter_count(ptr);
		}
		else {
			return 0;
		}
	}
	ReadFilter ReadArchive::getFilter(int index) const {
		if (isOpen()) {
			int code = archive_filter_code(ptr, index);
			
			switch (code) {
			case ARCHIVE_FILTER_BZIP2:
				return ReadFilter::bzip2;
			case ARCHIVE_FILTER_COMPRESS:
				return ReadFilter::compress;
			case ARCHIVE_FILTER_GRZIP:
				return ReadFilter::grzip;
			case ARCHIVE_FILTER_GZIP:
				return ReadFilter::gzip;
			case ARCHIVE_FILTER_LRZIP:
				return ReadFilter::lrzip;
			case ARCHIVE_FILTER_LZ4:
				return ReadFilter::lz4;
			case ARCHIVE_FILTER_LZMA:
				return ReadFilter::lzma;
			case ARCHIVE_FILTER_LZOP:
				return ReadFilter::lzop;
			case ARCHIVE_FILTER_RPM:
				return ReadFilter::rpm;
			case ARCHIVE_FILTER_UU:
				return ReadFilter::uu;
			case ARCHIVE_FILTER_XZ:
				return ReadFilter::xz;
			case ARCHIVE_FILTER_ZSTD:
				return ReadFilter::zstd;
			default:
				return ReadFilter::None;
			}
		}
		else {
			return ReadFilter::None;
		}
	}
	const char* ReadArchive::getFilterName(int index) const {
		if (isOpen()) {
			const char* name = archive_filter_name(ptr, index);
			if (name != nullptr) {
				return name;
			}
			else {
				return "none";
			}
		}
		else {
			return "none";
		}
	}

	bool ReadArchive::close() {
		entryErr = ARCHIVE_EOF;

		if (ptr != nullptr) {
			archive_read_free(ptr);
			ptr = nullptr;
		}

		if (entry != nullptr) {
			archive_entry_free(entry);
			entry = nullptr;
		}

		return false;
	}

	ReadFormat ReadArchive::getEntryFormat() const {
		if (hasEntry()) {
			int form = archive_format(ptr);
			switch (form) {
			case ARCHIVE_FORMAT_7ZIP:
				return ReadFormat::sevenzip;
			case ARCHIVE_FORMAT_AR:
			case ARCHIVE_FORMAT_AR_BSD:
			case ARCHIVE_FORMAT_AR_GNU:
				return ReadFormat::ar;
			case ARCHIVE_FORMAT_CAB:
				return ReadFormat::cab;
			case ARCHIVE_FORMAT_CPIO:
			case ARCHIVE_FORMAT_CPIO_AFIO_LARGE:
			case ARCHIVE_FORMAT_CPIO_BIN_BE:
			case ARCHIVE_FORMAT_CPIO_BIN_LE:
			case ARCHIVE_FORMAT_CPIO_POSIX:
			case ARCHIVE_FORMAT_CPIO_SVR4_CRC:
			case ARCHIVE_FORMAT_CPIO_SVR4_NOCRC:
				return ReadFormat::cpio;
			case ARCHIVE_FORMAT_EMPTY:
				return ReadFormat::empty;
			case ARCHIVE_FORMAT_ISO9660:
			case ARCHIVE_FORMAT_ISO9660_ROCKRIDGE:
				return ReadFormat::iso9660;
			case ARCHIVE_FORMAT_LHA:
				return ReadFormat::lha;
			case ARCHIVE_FORMAT_MTREE:
				return ReadFormat::mtree;
			case ARCHIVE_FORMAT_RAR:
				return ReadFormat::rar;
			case ARCHIVE_FORMAT_RAW:
				return ReadFormat::raw;
			case ARCHIVE_FORMAT_TAR:
			case ARCHIVE_FORMAT_TAR_GNUTAR:
			case ARCHIVE_FORMAT_TAR_PAX_INTERCHANGE:
			case ARCHIVE_FORMAT_TAR_PAX_RESTRICTED:
			case ARCHIVE_FORMAT_TAR_USTAR:
				return ReadFormat::tar;
			case ARCHIVE_FORMAT_WARC:
				return ReadFormat::warc;
			case ARCHIVE_FORMAT_XAR:
				return ReadFormat::xar;
			case ARCHIVE_FORMAT_ZIP:
				return ReadFormat::zip;
			default:
				return ReadFormat::None;
			}
		}
		else {
			return ReadFormat::None;
		}
	}
	const char* ReadArchive::getEntryFormatName() const {
		if (hasEntry()) {
			const char * name = archive_format_name(ptr);
			if (name != nullptr) {
				return name;
			}
			else {
				return "";
			}
		}
		else {
			return "";
		}
	}

	bool ReadArchive::hasEntry() const {
		return entryErr == ARCHIVE_OK;
	}
	void ReadArchive::nextEntry() {
		entryErr = archive_read_next_header2(ptr, entry);
	}

	EntryType ReadArchive::getEntryType() const {
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
	const char* ReadArchive::getEntryPath() const {
		if (hasEntry()) {
			const char * str = archive_entry_pathname(entry);
			if (str == nullptr) {
				return "";
			}
			else {
				return str;
			}
		}
		else {
			return "";
		}
	}
	const char* ReadArchive::getEntryHardLink() const {
		if (hasEntry()) {
			const char * str = archive_entry_hardlink(entry);
			if (str == nullptr) {
				return "";
			}
			else {
				return str;
			}
		}
		else {
			return "";
		}
	}

	void ReadArchive::skipData() {
		if (entry != nullptr) {
			archive_read_data_skip(ptr);
		}
	}

	std::vector<char> ReadArchive::readData() {
		const void* buffer = nullptr;
		size_t len = 0;
		int64_t offset = 0;
		archive_read_data_block(ptr, &buffer, &len, &offset);
		return std::vector<char>((char*)buffer, (char*)buffer + len);
	}
	size_t ReadArchive::readData(void* bufferPtr, size_t bufferLen) {
		size_t bytesWritten = archive_read_data(ptr, bufferPtr, bufferLen);
		return bytesWritten;
	}

	int ReadArchive::processedEntryCount() const {
		if (isOpen()) {
			return archive_file_count(ptr);
		}
		else {
			return 0;
		}
	}
	int ReadArchive::previousErrorCode() const {
		if (isOpen()) {
			return archive_errno(ptr);
		}
		else {
			return ARCHIVE_OK;
		}
	}
	const char* ReadArchive::previousErrorString() const {
		if (isOpen()) {
			return archive_error_string(ptr);
		}
		else {
			return "";
		}
	}

	bool ReadArchive::createArchive() {
		ptr = archive_read_new();
		if (ptr == nullptr) {
			return false;
		}
		int err;

		if ((formats & (int)ReadFormat::ar) != 0) {
			err = archive_read_support_format_ar(ptr);
			assert(err == ARCHIVE_OK);
		}

		if ((formats & (int)ReadFormat::cab) != 0) {
			err = archive_read_support_format_cab(ptr);
			assert(err == ARCHIVE_OK);
		}

		if ((formats & (int)ReadFormat::cpio) != 0) {
			err = archive_read_support_format_cpio(ptr);
			assert(err == ARCHIVE_OK);
		}

		if ((formats & (int)ReadFormat::iso9660) != 0) {
			err = archive_read_support_format_iso9660(ptr);
			assert(err == ARCHIVE_OK);
		}

		if ((formats & (int)ReadFormat::lha) != 0) {
			err = archive_read_support_format_lha(ptr);
			assert(err == ARCHIVE_OK);
		}

		if ((formats & (int)ReadFormat::mtree) != 0) {
			err = archive_read_support_format_mtree(ptr);
			assert(err == ARCHIVE_OK);
		}

		if ((formats & (int)ReadFormat::rar) != 0) {
			err = archive_read_support_format_rar(ptr);
			assert(err == ARCHIVE_OK);
		}

		if ((formats & (int)ReadFormat::raw) != 0) {
			err = archive_read_support_format_raw(ptr);
			assert(err == ARCHIVE_OK);
		}

		if ((formats & (int)ReadFormat::sevenzip) != 0) {
			err = archive_read_support_format_7zip(ptr);
			assert(err == ARCHIVE_OK);
		}

		if ((formats & (int)ReadFormat::tar) != 0) {
			err = archive_read_support_format_tar(ptr);
			assert(err == ARCHIVE_OK);
		}
		
		if ((formats & (int)ReadFormat::xar) != 0) {
			err = archive_read_support_format_xar(ptr);
			assert(err == ARCHIVE_OK);
		}

		if ((formats & (int)ReadFormat::zip) != 0) {
			err = archive_read_support_format_zip(ptr);
			assert(err == ARCHIVE_OK);
		}
		
		// Enable the filters.

		if ((filters & (int)ReadFilter::bzip2) != 0) {
			err = archive_read_support_filter_bzip2(ptr);
			assert(err == ARCHIVE_OK || err == ARCHIVE_WARN);
		}

		if ((filters & (int)ReadFilter::compress) != 0) {
			err = archive_read_support_filter_compress(ptr);
			assert(err == ARCHIVE_OK || err == ARCHIVE_WARN);
		}

		if ((filters & (int)ReadFilter::grzip) != 0) {
			err = archive_read_support_filter_grzip(ptr);
			assert(err == ARCHIVE_OK || err == ARCHIVE_WARN);
		}

		if ((filters & (int)ReadFilter::gzip) != 0) {
			err = archive_read_support_filter_gzip(ptr);
			assert(err == ARCHIVE_OK || err == ARCHIVE_WARN);
		}

		if ((filters & (int)ReadFilter::lrzip) != 0) {
			err = archive_read_support_filter_lrzip(ptr);
			assert(err == ARCHIVE_OK || err == ARCHIVE_WARN);
		}

		if ((filters & (int)ReadFilter::lz4) != 0) {
			err = archive_read_support_filter_lz4(ptr);
			assert(err == ARCHIVE_OK || err == ARCHIVE_WARN);
		}

		if ((filters & (int)ReadFilter::lzma) != 0) {
			err = archive_read_support_filter_lzma(ptr);
			assert(err == ARCHIVE_OK || err == ARCHIVE_WARN);
		}

		if ((filters & (int)ReadFilter::lzop) != 0) {
			err = archive_read_support_filter_lzop(ptr);
			assert(err == ARCHIVE_OK || err == ARCHIVE_WARN);
		}

		if ((filters & (int)ReadFilter::None) != 0) {
			err = archive_read_support_filter_none(ptr);
			assert(err == ARCHIVE_OK || err == ARCHIVE_WARN);
		}

		if ((filters & (int)ReadFilter::rpm) != 0) {
			err = archive_read_support_filter_rpm(ptr);
			assert(err == ARCHIVE_OK || err == ARCHIVE_WARN);
		}

		if ((filters & (int)ReadFilter::uu) != 0) {
			err = archive_read_support_filter_uu(ptr);
			assert(err == ARCHIVE_OK || err == ARCHIVE_WARN);
		}

		if ((filters & (int)ReadFilter::xz) != 0) {
			err = archive_read_support_filter_xz(ptr);
			assert(err == ARCHIVE_OK || err == ARCHIVE_WARN);
		}

		if ((filters & (int)ReadFilter::zstd) != 0) {
			err = archive_read_support_filter_zstd(ptr);
			assert(err == ARCHIVE_OK || err == ARCHIVE_WARN);
		}

		return true;
	}
}