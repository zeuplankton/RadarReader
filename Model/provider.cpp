#include "provider.h"
#include "Model/settings.h"
#include "utils.h"
#include "Model/connector.h"

Provider::Provider() {}



static QString SETTINGS_FILE = QStringLiteral(":/json/settings.json");
std::unique_ptr<Settings> Provider::m_settingsInstance = nullptr;
std::unique_ptr<Connector> Provider::m_connectorInstance = nullptr;

Settings &Provider::getSettingsAsSingleton()
{
    if (m_settingsInstance == nullptr) {
        m_settingsInstance = Utils::make_unique<Settings>(nullptr, SETTINGS_FILE);
    }
    return *m_settingsInstance;
}

Connector &Provider::getConnectorForSingleUse()
{
    if (m_connectorInstance == nullptr) {
        m_connectorInstance = Utils::make_unique<Connector>(nullptr, getSettingsAsSingleton());
    }
    return *m_connectorInstance;
}
