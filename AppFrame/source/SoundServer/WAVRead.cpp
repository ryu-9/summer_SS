#include "WAVRead.h"

bool WAVRead::Read(const char* path, WAVDATA* wavData) {
	if (wavData == nullptr) return false;
	
	HMMIO mmHandle = nullptr;
	
	MMCKINFO mmckInfo{};
	MMCKINFO rfckInfo{};

	mmHandle = mmioOpenA((LPSTR)path, nullptr, MMIO_READ);
	if (mmHandle == nullptr) return false;

	// riff�`�����N�Ɉړ�
	rfckInfo.fccType = mmioFOURCC('W', 'A', 'V', 'E');

	if (mmioDescend(mmHandle, &rfckInfo, nullptr, MMIO_FINDRIFF) != MMSYSERR_NOERROR) {
		mmioClose(mmHandle, MMIO_FHOPEN);
		return false;
	}

	// fmt�`�����N�Ɉړ�
	mmckInfo.ckid = mmioFOURCC('f', 'm', 't', ' ');

	if (mmioDescend(mmHandle, &mmckInfo, &rfckInfo, MMIO_FINDCHUNK) != MMSYSERR_NOERROR) {
		mmioClose(mmHandle, MMIO_FHOPEN);
		return false;
	}


	//fmt�`�����N�̓ǂݍ���
	uint32_t readSize = mmioRead(mmHandle, (HPSTR)&wavData->wFormat, mmckInfo.cksize);
	if (readSize != mmckInfo.cksize) {
		// �ǂݍ��ݎ��s
		mmioClose(mmHandle, MMIO_FHOPEN);
		return false;
	}

	// �t�H�[�}�b�g�`�F�b�N
	if (wavData->wFormat.wFormatTag != WAVE_FORMAT_PCM) {
		mmioClose(mmHandle, MMIO_FHOPEN);
		return false;
	}

	// �ޏo
	if (mmioAscend(mmHandle, &mmckInfo, 0) != MMSYSERR_NOERROR) {
		mmioClose(mmHandle, MMIO_FHOPEN);
		return false;
	}

	//data�`�����N�Ɉړ�
	mmckInfo.ckid = mmioFOURCC('d', 'a', 't', 'a');
	if (mmioDescend(mmHandle, &mmckInfo, &rfckInfo, MMIO_FINDCHUNK) != MMSYSERR_NOERROR) {
		mmioClose(mmHandle, MMIO_FHOPEN);
		return false;
	}

	//data�`�����N�̓ǂݍ���
	wavData->size = mmckInfo.cksize;
	wavData->sBuffer = new char[wavData->size];
	readSize = mmioRead(mmHandle, wavData->sBuffer, wavData->size);
	if (readSize != wavData->size) {
		// �ǂݍ��ݎ��s
		mmioClose(mmHandle, MMIO_FHOPEN);
		delete[] wavData->sBuffer;
		return false;
	}

	mmioClose(mmHandle, MMIO_FHOPEN);

	return true;
}
