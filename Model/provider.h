#ifndef PROVIDER_H
#define PROVIDER_H

#pragma once
#include <memory>

class Settings;
class Connector;

class Provider final
{
public:
    Provider();
    static Settings& getSettingsAsSingleton();
    static Connector& getConnectorForSingleUse();

private:
    static std::unique_ptr<Settings> m_settingsInstance;
    static std::unique_ptr<Connector> m_connectorInstance;
};

#endif // PROVIDER_H
