#ifndef SIGNAL_SCANNER_H
#define SIGNAL_SCANNER_H

#include <vector>
#include <cstdint>

class SignalScanner {
public:
    double calculateDbm(const std::vector<uint8_t>& samples);

    // Testfunktion: simulera signal från ett falskt fordon
    double simulateVehicleSignal();
};

#endif
