#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

static QString const &data = R"(
{
    "persistentData": {
        "module": {
            "name": "fancy module",
            "options": {}
        },
        "module_1": {
            "name": "shiny module",
            "options": {
                "option 1": "nothing",
                "option 2": "nothing really!"
            }
        }
    },
    "window": {
        "x": 5,
        "y": 10,
        "width": 100,
        "height": 200
    },
    "applicationName": "test"
})";


/**
 * @brief getValue given a json object and a path, retrieve the value of the key at path
 * @param settings source json object
 * @param path path to the key, where individual keys are separated by "/"
 * @param defaultValue value to return when the key / it's parents are not found in the settings object
 * @return value if found, else defaultValue
 */
QVariant getValue(QJsonObject const &settings,
                  QString const &path,
                  QVariant const &defaultValue = QVariant())
{
    QVariant result = defaultValue;

    QStringList pathComponents = path.split("/");
    QJsonObject parentObject = settings;

    while (pathComponents.size() > 0)
    {
        QString const &currentKey = pathComponents.takeFirst();

        if (parentObject.contains(currentKey))
        {
            if (pathComponents.size() == 0)
            {
                result = parentObject.value(currentKey);
            }
            else
            {
                parentObject = parentObject.value(currentKey).toObject();
            }
        }
        else
        {
            qWarning() << "Settings could not access unknown key" << currentKey << " in " << parentObject;
            break;
        }
    }

    return result;
}

/**
 * @brief setValue given a json object, set the key at path, to value, creating the path up to there if necessary.
 * @param settings source json object
 * @param path to the key, where individual keys are separated by "/"
 * @param value value to set to
 * @return copy of settings object with the correct key at path set to value
 */
QJsonObject setValue(QJsonObject const &settings, QString const &path, QVariant const &value)
{
    QStringList pathComponents = path.split("/");

    QVector<QJsonObject> valuesUpToPath{settings};

    //Ensure the path up to the last value exists,
    for (int i = 0; i < pathComponents.size() - 1; i++)
    {
        QString const &currentKey = pathComponents[i];

        if (!valuesUpToPath.last().contains(currentKey))
        {
            valuesUpToPath.last()[currentKey] = QJsonObject();
        }

        valuesUpToPath.push_back(valuesUpToPath.last()[currentKey].toObject());
    }

    //Set the last item's key = value
    valuesUpToPath.last()[pathComponents.last()] = QJsonValue::fromVariant(value);

    //Now merge all the items back into one
    QJsonObject result = valuesUpToPath.takeLast();

    while (valuesUpToPath.size() > 0)
    {
        QJsonObject parent = valuesUpToPath.takeLast();
        parent[pathComponents[valuesUpToPath.size()]] = result;
        result = parent;
    }

    return result;
}

int main(void)
{
    QJsonObject settings = QJsonDocument::fromJson(data.toLocal8Bit()).object();

    Q_ASSERT(getValue(settings, "") == QVariant());
    Q_ASSERT(getValue(settings, "nonexistent") == QVariant());

    Q_ASSERT(getValue(settings, "applicationName") == "test");
    settings = setValue(settings, "applicationName", "shiny test");
    Q_ASSERT(getValue(settings, "applicationName") == "shiny test");

    Q_ASSERT(getValue(settings, "window/x", -1) == 5);
    settings = setValue(settings, "window/x", 20);
    Q_ASSERT(getValue(settings, "window/x", -1) == 20);

    Q_ASSERT(getValue(settings, "persistentData/module_1/options/option 1", "nothing") == "nothing");
    settings = setValue(settings, "persistentData/module_1/options/option 1", "meh");
    Q_ASSERT(getValue(settings, "persistentData/module_1/options/option 1", "nothing") == "meh");

    settings = setValue(settings, "nonExistentChild/nonExistentGrandChild/value", "hey there");
    Q_ASSERT(getValue(settings, "nonExistentChild/nonExistentGrandChild/value") == "hey there");

    qDebug() << settings;

    return 0;
}
