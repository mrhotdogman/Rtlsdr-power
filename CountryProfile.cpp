#include "CountryProfile.h"
#include <cstdlib>

CountryProfile CountryManager::getProfile(const std::string& countryCode)
{
    CountryProfile profile;
    profile.countryCode = countryCode;

    if(countryCode == "SE") {
        // Sverige
        profile.ranges = {
            {380000000, 382500000},
            {382500000, 385000000}
        };
    }
    else if(countryCode == "DE") {
        // Tyskland
        profile.ranges = {
            {380000000, 385000000}
        };
    }
    else if(countryCode == "UK") {
        // Storbritannien
        profile.ranges = {
            {380000000, 385000000},
            {390000000, 395000000}
        };
    }
    else if(countryCode == "FR") {
        // Frankrike
        profile.ranges = {
            {380000000, 385000000}
        };
    }
    else {
        // Default EU TETRA
        profile.ranges = {
            {380000000, 385000000}
        };
    }

    return profile;
}

std::string CountryManager::detectSystemCountry()
{
    const char* locale = std::getenv("LANG");

    if(!locale) return "DEFAULT";

    std::string loc(locale);

    if(loc.find("sv") != std::string::npos) return "SE";
    if(loc.find("de") != std::string::npos) return "DE";
    if(loc.find("en_GB") != std::string::npos) return "UK";
    if(loc.find("fr") != std::string::npos) return "FR";

    return "DEFAULT";
}
