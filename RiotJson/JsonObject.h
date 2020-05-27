#ifndef JSONOBJECT_H
#define JSONOBJECT_H

#include <QJsonObject>
#include <QList>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJSValue>
#include <QJSEngine>

class JsonObject : public QJsonObject
{
public:
    template <typename T>
    static QJsonArray listToArr(const QList<T> &list)
    {
        QJsonArray result;
        for (auto val : list) result.append(val);
        return result;
    }

    template <typename T>
    static QList<T> arrToList(const QJsonArray &arr)
    {
        QList<T> result;
        for (auto val : arr) result.append(static_cast<T>(val.toObject()));
        return result;
    }

    template <typename T>
    static QJSValue convertToJSValue(QJSEngine* engine, const QList<T> &list)
    {
        return JsonObject::convertToJSValue(engine, listToArr(list));
    }

    static QJSValue convertToJSValue(QJSEngine* engine, const QJsonValue &val)
    {
        if (val.isBool())
        {
            return QJSValue(val.toBool());
        }
        else if (val.isString())
        {
            return QJSValue(val.toString());
        }
        else if (val.isDouble())
        {
            return QJSValue(val.toDouble());
        }
        else if (val.isNull())
        {
            return QJSValue(QJSValue::NullValue);
        }
        else if (val.isUndefined())
        {
            return QJSValue(QJSValue::UndefinedValue);
        }
        else if (val.isObject())
        {
            QJsonObject obj = val.toObject();
            if (obj.isEmpty())
                return QJSValue(QJSValue::NullValue);
            QJSValue newobj = engine->newObject();
            for (auto itor = obj.begin(); itor != obj.end(); itor++)
            {
                QString key = itor.key();
                QJsonValue value = itor.value();
                QJSValue convertedValue = convertToJSValue(engine, value);
                newobj.setProperty(key, convertedValue);
            }
            return newobj;
        }
        else if (val.isArray())
        {
            QJsonArray arr = val.toArray();
            if (arr.isEmpty())
                return QJSValue(QJSValue::NullValue);
            QJSValue newobj = engine->newArray(uint(arr.size()));
            for (int i = 0; i < arr.size(); i++)
            {
                QJsonValue value = arr[i];
                QJSValue convertedValue = convertToJSValue(engine, value);
                newobj.setProperty(quint32(i), convertedValue);
            }
            return newobj;
        }
        return QJSValue(QJSValue::UndefinedValue);
    }
};

#endif // JSONOBJECT_H
