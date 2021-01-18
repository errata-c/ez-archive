#include "ez/archive/Defines.hpp"

namespace ez {
	const std::string& getReadFilterName(ReadFilter filt) {
		static const std::string names[]{
			"bzip2",
			"compress",
			"grzip",
			"gzip",
			"lrzip",
			"lz4",
			"lzma",
			"lzop",
			"None",
			"rpm",
			"uu",
			"xz",
			"zstd"
		};

		switch (filt) {
		case ReadFilter::bzip2:
			return names[0];
		case ReadFilter::compress:
			return names[1];
		case ReadFilter::grzip:
			return names[2];
		case ReadFilter::gzip:
			return names[3];
		case ReadFilter::lrzip:
			return names[4];
		case ReadFilter::lz4:
			return names[5];
		case ReadFilter::lzma:
			return names[6];
		case ReadFilter::lzop:
			return names[7];
		case ReadFilter::None:
			return names[8];
		case ReadFilter::rpm:
			return names[9];
		case ReadFilter::uu:
			return names[10];
		case ReadFilter::xz:
			return names[11];
		case ReadFilter::zstd:
			return names[12];
		default:
			return names[8];
		}
	}

	const std::string& getWriteFilterName(WriteFilter filt) {
		static const std::string names[]{
			"b64encode",
			"bzip2",
			"compress",
			"grzip",
			"gzip",
			"lrzip",
			"lz4",
			"lzip",
			"lzma",
			"lzop",
			"uuencode",
			"xz",
			"zstd",
			"None"
		};

		switch (filt) {
		case WriteFilter::b64encode:
			return names[0];
		case WriteFilter::bzip2:
			return names[1];
		case WriteFilter::compress:
			return names[2];
		case WriteFilter::grzip:
			return names[3];
		case WriteFilter::gzip:
			return names[4];
		case WriteFilter::lrzip:
			return names[5];
		case WriteFilter::lz4:
			return names[6];
		case WriteFilter::lzip:
			return names[7];
		case WriteFilter::lzma:
			return names[8];
		case WriteFilter::lzop:
			return names[9];
		case WriteFilter::uuencode:
			return names[10];
		case WriteFilter::xz:
			return names[11];
		case WriteFilter::zstd:
			return names[12];
		case WriteFilter::None:
			return names[13];
		default:
			return names[13];
		}
	}

	const std::string& getReadFormatName(ReadFormat form) {
		static std::string names[]{
			"sevenzip",
			"ar",
			"cab",
			"cpio",
			"iso9660",
			"lha",
			"mtree",
			"rar",
			"raw",
			"tar",
			"xar",
			"zip",
			"empty",
			"warc",
			"None"
		};

		switch (form) {
		case ReadFormat::sevenzip:
			return names[0];
		case ReadFormat::ar:
			return names[1];
		case ReadFormat::cab:
			return names[2];
		case ReadFormat::cpio:
			return names[3];
		case ReadFormat::iso9660:
			return names[4];
		case ReadFormat::lha:
			return names[5];
		case ReadFormat::mtree:
			return names[6];
		case ReadFormat::rar:
			return names[7];
		case ReadFormat::raw:
			return names[8];
		case ReadFormat::tar:
			return names[9];
		case ReadFormat::xar:
			return names[10];
		case ReadFormat::zip:
			return names[11];
		case ReadFormat::empty:
			return names[12];
		case ReadFormat::warc:
			return names[13];
		default:
			return names[14];
		}
	}

	const std::string& getWriteFormatName(WriteFormat form) {
		static std::string names[]{
			"ar",
			"ar_bsd",
			"ar_svr4",
			"cpio",
			"cpio_newc",
			"gnutar",
			"iso9660",
			"mtree",
			"mtree_classic",
			"mtree_default",
			"None",
			"pax",
			"pax_restricted",
			"raw",
			"sevenzip",
			"shar",
			"shar_dump",
			"ustar",
			"v7tar",
			"warc",
			"xar",
			"zip"
		};

		switch (form) {
		case WriteFormat::ar:
			return names[0];
		case WriteFormat::ar_bsd:
			return names[1];
		case WriteFormat::ar_svr4:
			return names[2];
		case WriteFormat::cpio:
			return names[3];
		case WriteFormat::cpio_newc:
			return names[4];
		case WriteFormat::gnutar:
			return names[5];
		case WriteFormat::iso9660:
			return names[6];
		case WriteFormat::mtree:
			return names[7];
		case WriteFormat::mtree_classic:
			return names[8];
		case WriteFormat::mtree_default:
			return names[9];
		case WriteFormat::None:
			return names[10];
		case WriteFormat::pax:
			return names[11];
		case WriteFormat::pax_restricted:
			return names[12];
		case WriteFormat::raw:
			return names[13];
		case WriteFormat::sevenzip:
			return names[14];
		case WriteFormat::shar:
			return names[15];
		case WriteFormat::shar_dump:
			return names[16];
		case WriteFormat::ustar:
			return names[17];
		case WriteFormat::v7tar:
			return names[18];
		case WriteFormat::warc:
			return names[19];
		case WriteFormat::xar:
			return names[20];
		case WriteFormat::zip:
			return names[21];
		default:
			return names[10];
		}
	}

	const std::string& getEntryTypeName(EntryType type) {
		static std::string names[]{
			"BlockDevice",
			"CharacterDevice",
			"Directory",
			"File",
			"NamedPipe",
			"None",
			"Socket",
			"SymLink"
		};

		switch (type) {
		case EntryType::BlockDevice:
			return names[0];
		case EntryType::CharacterDevice:
			return names[1];
		case EntryType::Directory:
			return names[2];
		case EntryType::File:
			return names[3];
		case EntryType::NamedPipe:
			return names[4];
		case EntryType::None:
			return names[5];
		case EntryType::Socket:
			return names[6];
		case EntryType::SymLink:
			return names[7];
		default:
			return names[5];
		}
	}
};