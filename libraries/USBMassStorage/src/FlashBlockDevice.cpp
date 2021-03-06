#include "FlashBlockDevice.h"


bool FlashBlockDevice::begin() {
	return true;
}
bool FlashBlockDevice::end() {
	return true;
}

bool FlashBlockDevice::readBlocks(uint32_t block, uint8_t* dst, size_t blocks) {
	PRINT_INFO("Reading block %d %d", block, blocks);
	for(uint32_t offset = 0; offset < blocks; offset++) {
		flashVariables->read(block + offset, dst + offset * 512);
	}
	return true;
}

bool FlashBlockDevice::writeBlocks(uint32_t block, uint8_t* src, size_t blocks) {
	PRINT_INFO("Writing block %d %d", block, blocks);

	for(uint32_t offset = 0; offset < blocks; offset++) {
		flashVariables->write(block + offset, src + offset * 512);
	}
	return true;
}

