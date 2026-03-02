#ifndef RTL_SDR_DEVICE_H
#define RTL_SDR_DEVICE_H

#include <cstdint>
#include <vector>
#include <rtl-sdr.h>

class RtlSdrDevice {
public:
    RtlSdrDevice();
    ~RtlSdrDevice();

    bool openDevice(uint32_t deviceIndex = 0);
    void closeDevice();

    bool setFrequency(uint32_t freq);
    bool setSampleRate(uint32_t rate);
    bool setGain(int gain);

    std::vector<uint8_t> readSamples(size_t numSamples);

private:
    rtlsdr_dev_t* dev;
};

#endif
