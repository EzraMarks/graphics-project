#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QColor>

// Enumeration values for the modes from which the user can choose in the GUI.
enum Mode
{
    MODE_BLUR,
    MODE_PARTICLES,
    NUM_MODES
};

/**

    @struct Settings
    @brief  Stores application settings for the CS123 GUI.

    You can access all app settings through the "settings" global variable.
    The settings will be automatically updated when things are changed in the
    GUI (the reverse is not true however: changing the value of a setting does
    not update the GUI).

*/
struct Settings {
    // Loads settings from disk, or fills in default values if no saved settings exist.
    void loadSettingsOrDefaults();

    // Saves the current settings to disk.
    void saveSettings();

    // Default simulation parameters
    const float defaultDt = 1.0;
    const float defaultDiffusionRateA = 1.0;
    const float defaultDiffusionRateB = 0.5;
    const float defaultFeedRate = 0.55;
    const float defaultKillRate = 0.62;
    const QColor defaultColor = QColor(255, 174, 12);


    // Current simulation parameters

    float dt; // Delta t, the size of the time step for each iteration.
    float diffusionRateA;
    float diffusionRateB;
    float feedRate;
    float killRate;
    bool isFirstPass;
    QString imagePath;
    QColor color;
};

// The global Settings object, will be initialized by MainWindow
extern Settings settings;

#endif // SETTINGS_H
