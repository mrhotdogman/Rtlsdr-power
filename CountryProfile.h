#ifndef COUNTRY_PROFILE_H
#define COUNTRY_PROFILE_H

#include <vector>
#include <string>
#include <cstdint>

struct FrequencyRange {
    uint32_t startFreq;
    uint32_t endFreq;
};

struct CountryProfile {
    std::string countryCode;
    std::vector<FrequencyRange> ranges;
};

class CountryManager {
public:
    static CountryProfile getProfile(const std::string& countryCode);
    static std::string detectSystemCountry();
};

#endif
