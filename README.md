Project ARS from Tod Gentille's course Integrating C++ with QML

A quiet shout-out and a millions thanks to [@Rolias](https://github.com/Rolias) for creating the excellent course.

Current problems:
* The knobs are set to display initial values set from config file or the preset buttons
* But sometimes the knobs could not be rotated from nearest positions when set from the preset buttons.
    * When set from the settings.json config file, the knobs can be dragged and rotated with any issues.
    * When set from preset buttons, the knobs sometimes are not responsive. Not always, just sometimes.
    * This is a bug pending investigation.
* I didn't look into the libs or dlls.

Further improvement:
* It's ideal to load settings from the settings.json after the system initalization is completed (the timer has timedout).
* There might be a logical connection between the RfPower button and the Instrument class.
* I haven't figured out the phasing-out animation for the Feedback panel, after displaying the Connection Success message or hitting the OK button after Connection Failure.
