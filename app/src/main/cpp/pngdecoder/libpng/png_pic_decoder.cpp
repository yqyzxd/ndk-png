#include <errno.h>
#include "./png_pic_decoder.h"


#define LOG_TAG "PngPicDecoder"

PngPicDecoder::PngPicDecoder() {
}

PngPicDecoder::~PngPicDecoder() {
}

int PngPicDecoder::openFile(char *pngFilePath) {
	LOGI(" fopen before");
	pngFile = fopen(pngFilePath, "rb");
	int errNum = 0;
	if (pngFile == nullptr)
	{
		errNum = errno;
		LOGE("[openFile] open fail errno = %d, reason = %s", errNum, strerror(errNum));
	}
	LOGI(" fopen after");
	fseek(pngFile, 0, SEEK_END);
	int data_length = ftell(pngFile);
	rewind(pngFile);
	compressedData = new byte[data_length];
	LOGI(" fread before");
	actualSize = fread(compressedData, 1, data_length, pngFile);
	LOGI(" fread after: %d",actualSize);

	return 0;
}

RawImageData PngPicDecoder::getRawImageData(){
	RawImageData data = get_raw_image_data_from_png((void*) compressedData, actualSize);
	return data;
}

void PngPicDecoder::releaseRawImageData(const RawImageData* data){
	release_raw_image_data(data);
}

void PngPicDecoder::closeFile(){
	delete[] compressedData;
	fclose(pngFile);
}
