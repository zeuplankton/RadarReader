#include "settings.h"
#include <QStandardPaths>
#include <QMessageBox>


Settings::Settings(QObject *parent, QString filename)
    : QObject{parent},
    m_filename(filename),
    m_modelCommands(*new QStringListModel(this)),
    m_testMode(true),
    m_bootDelay(1000)
{

}

void Settings::parseJSONData()
{
    QString json_raw = readJSONFile();
    if (json_raw.size() == 0) { return; }

    auto json_pair = getJsonObject(json_raw);
    auto json_err = json_pair.second;

    if (json_err.error == QJsonParseError::NoError) {
        auto json_obj = json_pair.first;
        m_applicationName = json_obj["applicationTitle"].toString();
        m_appShortName = json_obj["appShortName"].toString();
        m_hostName = json_obj["hostName"].toString();
        m_portNumber = json_obj["portNumber"].toInt();
        m_waitMs = json_obj["tcpWaitMs"].toInt();
        m_readWaitMs = json_obj["readWaitMs"].toInt();

        m_velocity = json_obj["velocity"].toDouble();
        m_distance = json_obj["distance"].toDouble();
        m_radarFreqGhz = json_obj["radarFrequencyGhz"].toDouble();

        m_RxIfAttnDb = json_obj["rxIfAttenDb"].toInt();
        m_TxIfAttnDb = json_obj["txIfAttenDb"].toInt();
        m_powerState = json_obj["powerState"].toBool();
        m_testMode = json_obj["testMode"].toBool();
        m_bootDelay = json_obj["bootDelay"].toInt();

        m_distance1 = json_obj["distance1"].toDouble();
        m_distance2 = json_obj["distance2"].toDouble();
        m_distance3 = json_obj["distance3"].toDouble();
        m_distance4 = json_obj["distance4"].toDouble();

        m_velocity1 = json_obj["velocity1"].toDouble();
        m_velocity2 = json_obj["velocity2"].toDouble();
        m_velocity3 = json_obj["velocity3"].toDouble();
        m_velocity4 = json_obj["velocity4"].toDouble();
    } else {
        showJsonParseError(json_err);
    }
}

QString Settings::readJSONFile()
{
    auto default_settings = readJSONFromInternalResource();
    QDir config_dir = openConfigDirectory();
    auto path = config_dir.filePath(m_filename);
    QFile std_file(path);
    if (std_file.exists()) {
        if (!std_file.open(QFile::ReadOnly|QFile::Text)) {
            emit notifyFailure("Could not open " + path);
            return default_settings;
        }
        QString settings = std_file.readAll();
        std_file.close();
        return settings;
    } else {
        writeDefaultsToStdConfigFile(std_file, default_settings);
        return default_settings;
    }
}

QString Settings::readJSONFromInternalResource()
{
    QDir res_dir(":/json");
    if (!res_dir.exists()) {
        emit notifyFailure("Internal resource path missing " + res_dir.canonicalPath());
        return "";
    }
    auto path = res_dir.filePath(m_filename);
    QFile res_file(path);
    if (!res_file.open(QFile::ReadOnly|QFile::Text)) {
        emit notifyFailure("Could not open internal resource " + path);
        return "";
    }
    QString settings = res_file.readAll();
    return settings;
}


QDir Settings::openConfigDirectory()
{
    QDir config_dir(QStandardPaths::writableLocation(QStandardPaths::ConfigLocation));
    if (!config_dir.exists()) {
        QDir dir;
        dir.mkpath(config_dir.path());
    }
    return config_dir;
}

void Settings::writeDefaultsToStdConfigFile(QFile &stdConfigFile, const QString &settings)
{
    int length = settings.length();
    if (!stdConfigFile.open(QFile::WriteOnly|QFile::Text)) {
        emit notifyFailure("Could not open file to write " + stdConfigFile.fileName());
    }
    auto bytes_written = stdConfigFile.write(qPrintable(settings), length);
    if (bytes_written != length) {
        emit notifyFailure("Could not write the settings to " + stdConfigFile.fileName());
        if (!stdConfigFile.remove()) {
            emit notifyFailure("Could not remove configuration file. Please delete manually " + stdConfigFile.fileName());
        }
    }
    stdConfigFile.close();
}


JsonObjErrPair Settings::getJsonObject(const QString &rawJson)
{
    QJsonParseError jsonParseError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(rawJson.toUtf8(), &jsonParseError);
    QJsonObject jsonObj = jsonDoc.object();
    return std::make_pair(jsonObj, jsonParseError);
}

void Settings::showJsonParseError(QJsonParseError jsonParseError)
{
    if (jsonParseError.error != QJsonParseError::NoError) {
        QString message = tr("Error parsing Json settings file.\n");
        message.append(jsonParseError.errorString());
        message.append(tr("\nThe default values will be used."));
        QMessageBox::critical(0, tr("ARS"), message);
    }

}



