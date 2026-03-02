#include "RtlSdrDevice.h"
#include "SignalScanner.h"
#include "CountryProfile.h"
#include <iostream>
#include <thread>
#include <chrono>

#define LED_THRESHOLD   -40.0
#define LED_STEP         5.0
#define BANDWIDTH   2500000
#define LED_INTERVAL_SEC 4

void evaluateLed(double dbm)
{
    if (dbm < LED_THRESHOLD) {
        std::cout << "LED: OFF\n";
        return;
    }

    int level = static_cast<int>((dbm - LED_THRESHOLD) / LED_STEP) + 1;

    std::cout << "LED Level: ";
    for(int i = 0; i < level; i++)
        std::cout << "*";
    std::cout << " (" << dbm << " dBm)\n";
}

int main()
{
    RtlSdrDevice device;
    SignalScanner scanner;

    bool testMode = true;

    std::string detectedCountry = CountryManager::detectSystemCountry();
    CountryProfile profile = CountryManager::getProfile(detectedCountry);

    std::cout << "Detected country profile: " << profile.countryCode << "\n";

    if(!testMode) {
        if(!device.openDevice()) return -1;
        device.setSampleRate(2048000);
        device.setGain(30);
    }

    while(true)
    {
        std::cout << "\n--- 4 SECOND SCAN CYCLE ---\n";

        for(const auto& range : profile.ranges)
        {
            for(uint32_t freq = range.startFreq;
                freq <= range.endFreq;
                freq += BANDWIDTH)
            {
                double dbm;

                if(testMode) {
                    dbm = scanner.simulateVehicleSignal();
                } else {
                    device.setFrequency(freq);
                    auto samples = device.readSamples(16384);
                    dbm = scanner.calculateDbm(samples);
                }

                std::cout << "Freq: "
                          << freq / 1e6
                          << " MHz | ";

                evaluateLed(dbm);
            }
        }

        std::this_thread::sleep_for(
            std::chrono::seconds(LED_INTERVAL_SEC)
        );
    }

    if(!testMode)
        device.closeDevice();

    return 0;
}
