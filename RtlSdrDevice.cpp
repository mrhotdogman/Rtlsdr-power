#include "RtlSdrDevice.h"
#include <iostream>

RtlSdrDevice::RtlSdrDevice() : dev(nullptr) {}

RtlSdrDevice::~RtlSdrDevice() {
    closeDevice();
}

bool RtlSdrDevice::openDevice(uint32_t deviceIndex) {
    if(rtlsdr_open(&dev, deviceIndex) < 0) {
        std::cerr << "Cannot open RTL-SDR device" << std::endl;
        return false;
    }
    rtlsdr_reset_buffer(dev);
    return true;
}

void RtlSdrDevice::closeDevice() {
    if(dev) {
        rtlsdr_close(dev);
        dev = nullptr;
    }
}

bool RtlSdrDevice::setFrequency(uint32_t freq) {
    if(dev && rtlsdr_set_center_freq(dev, freq) >= 0)
        return true;
    return false;
}

bool RtlSdrDevice::setSampleRate(uint32_t rate) {
    if(dev && rtlsdr_set_sample_rate(dev, rate) >= 0)
        return true;
    return false;
}

bool RtlSdrDevice::setGain(int gain) {
    if(dev && rtlsdr_set_tuner_gain_mode(dev, 1) >= 0 &&
       rtlsdr_set_tuner_gain(dev, gain) >= 0)
        return true;
    return false;
}

std::vector<uint8_t> RtlSdrDevice::readSamples(size_t numSamples) {
    std::vector<uint8_t> buffer(numSamples);
    int nRead;
    if(dev)
        rtlsdr_read_sync(dev, buffer.data(), buffer.size(), &nRead);
    return buffer;
}
