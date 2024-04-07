#ifndef UTILS_H
#define UTILS_H

#pragma once
#include <QString>
#include <QObject>
#include <memory>


class Utils
{
public:
    Utils();
    static void DestructorMsg(const QString& value);
    static void DestructorMsg(const QObject* const object);

    template<typename T, typename... Args>
    static std::unique_ptr<T> make_unique(Args&&... args) {
        return std::unique_ptr<T> (new T(std::forward<Args>(args)...));
    }

};

#endif // UTILS_H
