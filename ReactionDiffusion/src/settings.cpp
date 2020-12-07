#include "settings.h"
#include <QFile>
#include <QSettings>

Settings settings;


/**
  Loads the application settings, or, if no saved settings are available,
  loads default values for the settings. You can change the defaults here.
**/
void Settings::loadSettingsOrDefaults() {
    // Set the default values below
    QSettings s("CS123", "ReactionDiffusion");
    dt = s.value("dt", defaultDt).toFloat();
    diffusionRateA = s.value("diffusionRateA", defaultDiffusionRateA).toFloat();
    diffusionRateB = s.value("diffusionRateB", defaultDiffusionRateB).toFloat();
    feedRate = s.value("feedRate", defaultFeedRate).toFloat();
    killRate = s.value("killRate", defaultKillRate).toFloat();
    imagePath = s.value("imagePath", QString()).toString();
    isFirstPass = true;
}

void Settings::resetSettings() {
    dt = defaultDt;
    diffusionRateA = defaultDiffusionRateA;
    diffusionRateB = defaultDiffusionRateB;
    feedRate = defaultFeedRate;
    killRate = defaultKillRate;
}

void Settings::saveSettings() {
    QSettings s("CS123", "ReactionDiffusion");
    s.setValue("dt", dt);
    s.setValue("diffusionRateA", diffusionRateA);
    s.setValue("diffusionRateB", diffusionRateB);
    s.setValue("feedRate", feedRate);
    s.setValue("killRate", killRate);
    s.setValue("imagePath", imagePath);
}
