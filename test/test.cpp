#include <fmt/format.h>
#include <cstdlib>

#include <ez/archive/ReadArchive.hpp>

int main() {
	fmt::print("Test.\n");

	system("cd");

	ez::ReadArchive archive;
	const char* archiveName = "sprites.7z";
	
	if (archive.open(archiveName, 2 << 14)) {
		fmt::print("Successfully opened the archive \'{}\'.\n", archiveName);
	}
	else {
		fmt::print("Failed to open the archive!\n");
		fmt::print("The previous error string was: {}\n", archive.previousErrorString());
		return -1;
	}

	fmt::print("Listing the contents of the archive:\n\n");
	while (archive.hasEntry()) {
		fmt::print("\tPath: {}\n", archive.getEntryPath());
		int filterCount = archive.getFilterCount();
		for (int i = 0; i < filterCount; ++i) {
			fmt::print("\tFilter {}: {}\n", i, archive.getFilterName(i));
			fmt::print("\tFormat: {}\n", archive.getEntryFormatName());
		}
		fmt::print("\n");

		archive.nextEntry();
	}

	archive.close();

	return 0;
}