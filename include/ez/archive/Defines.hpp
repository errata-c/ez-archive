#pragma once
#include <array>
#include <string>

namespace ez {
	enum class ReadFilter: int {
		None = 0,
		bzip2 = 1 << 0,
		compress = 1 << 1,
		grzip = 1 << 2,
		gzip = 1 << 3,
		lrzip = 1 << 4,
		lz4 = 1 << 5,
		lzma = 1 << 6,
		lzop = 1 << 7,
		rpm = 1 << 9,
		uu = 1 << 10,
		xz = 1 << 11,
		zstd = 1 << 12,
		all = bzip2 | compress | grzip | gzip | lrzip | lz4 | lzma | lzop | None | rpm | uu | xz | zstd,

	};
	const std::string& getReadFilterName(ReadFilter filt);

	enum class WriteFilter : int {
		b64encode = 1 << 0,
		bzip2 = 1 << 1,
		compress = 1 << 2,
		grzip = 1 << 3,
		gzip = 1 << 4,
		lrzip = 1 << 5,
		lz4 = 1 << 6,
		lzip = 1 << 7,
		lzma = 1 << 8,
		lzop = 1 << 9,
		uuencode = 1 << 11,
		xz = 1 << 12,
		zstd = 1 << 13,

		None = 0
	};
	const std::string& getWriteFilterName(WriteFilter filt);

	enum class ReadFormat : int {
		sevenzip = 1,
		ar = 1 << 1,
		cab = 1 << 2,
		cpio = 1 << 3,
		iso9660 = 1 << 4,
		lha = 1 << 5,
		mtree = 1 << 6,
		rar = 1 << 7,
		raw = 1 << 8,
		tar = 1 << 9,
		xar = 1 << 10,
		zip = 1 << 11,

		all = sevenzip | ar | cab | cpio | iso9660 | lha | mtree | rar | tar | xar | zip,

		// Support for these cannot be enabled in the read, must be automatic?
		// Libarchive docs say warc is read/write capable, but doesn't say what format to enable for its support.
		// If I had to guess it would be under the iso support, but I can't be sure.
		empty = 1 << 12,
		warc = 1 << 13,
		
		None = 0
	};
	const std::string& getReadFormatName(ReadFormat form);

	enum class WriteFormat : int {
		sevenzip = 1 << 0,
		ar = 1 << 1,
		ar_bsd,
		ar_svr4,
		cpio = 1 << 3,
		cpio_newc = 1 << 4,
		gnutar = 1 << 5,
		iso9660 = 1 << 6,
		mtree = 1 << 7,
		mtree_classic = 1 << 8,
		mtree_default = 1 << 9,
		pax = 1 << 10,
		pax_restricted = 1 << 11,
		raw = 1 << 12,
		shar = 1 << 13,
		shar_dump = 1 << 14,
		ustar = 1 << 15,
		v7tar = 1 << 16,
		warc = 1 << 17,
		xar = 1 << 18,
		zip = 1 << 19,

		None = 0,
	};
	const std::string& getWriteFormatName(WriteFormat form);

	enum class EntryType {
		File,
		SymLink,
		Socket,
		CharacterDevice,
		BlockDevice,
		Directory,
		NamedPipe,
		None,
	};
	const std::string& getEntryTypeName(EntryType type);

	static constexpr std::array<const char*, 12> FormatExtentions{
		".7z",
		".zip",
		".jar",
		".cpio",

		".iso",
		".a",
		".ar",
		".tar",

		 ".tgz",
		 ".tar.gz",
		 ".tar.bz2",
		 ".tar.xz"
	};
}