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
    mode = s.value("mode", MODE_BLUR).toInt();
    dt = s.value("dt", 1.0).toFloat();
    diffusionRateA = s.value("diffusionRateA", 1.0).toFloat();
    diffusionRateB = s.value("diffusionRateB", 0.5).toFloat();
    feedRate = s.value("feedRate", 0.055).toFloat();
    killRate = s.value("killRate", 0.062).toFloat();
    imagePath = s.value("imagePath", QString()).toString();
}

void Settings::saveSettings() {
    QSettings s("CS123", "ReactionDiffusion");
    s.setValue("mode", mode);
    s.setValue("dt", dt);
    s.setValue("diffusionRateA", diffusionRateA);
    s.setValue("diffusionRateB", diffusionRateB);
    s.setValue("feedRate", feedRate);
    s.setValue("killRate", killRate);
    s.setValue("imagePath", imagePath);
}
