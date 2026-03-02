#include "SignalScanner.h"
#include <cmath>
#include <iostream>
#include <random>

double SignalScanner::calculateDbm(const std::vector<uint8_t>& samples) {
    // Enkel RMS-beräkning som proxy för dBm
    double sum = 0.0;
    for(auto s : samples) {
        double val = static_cast<double>(s) - 127.5; // centrerar kring 0
        sum += val * val;
    }
    double rms = sqrt(sum / samples.size());
    double dbm = 20 * log10(rms / 127.0); // ungefärlig dBm
    return dbm;
}

double SignalScanner::simulateVehicleSignal() {
    // Generera ett slumpmässigt dBm-värde för falskt fordon
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-90.0, -50.0); // realistiska TETRA-signalnivåer

    return dis(gen);
}
