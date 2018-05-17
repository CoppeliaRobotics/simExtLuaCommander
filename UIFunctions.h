#ifndef UIFUNCTIONS_H_INCLUDED
#define UIFUNCTIONS_H_INCLUDED

#include "config.h"

#include <QObject>
#include <QString>

#include "stubs.h"
#include "PersistentOptions.h"

class UIFunctions : public QObject
{
    Q_OBJECT

public:
    virtual ~UIFunctions();

    static UIFunctions * getInstance(QObject *parent = 0);
    static void destroyInstance();

    void connectSignals();

    void setOptions(const PersistentOptions &options);

    void loadHistory();
    void appendHistory(QString code);

    void showMessage(QString s, bool html = false);
    void showWarning(QString s, bool html = false);
    void showError(QString s, bool html = false);

public slots:
    void clearHistory();

private:

    UIFunctions(QObject *parent = 0);

    static UIFunctions *instance;

    std::string getStackTopAsString(int stackHandle, const PersistentOptions &opts, int depth = 0, bool quoteStrings = true, bool insideTable = false, std::string *strType = nullptr);

    void initStringRenderingFlags();
    QStringList getMatchingStringRenderingFlags(QString shortFlag);
    void parseStringRenderingFlags(PersistentOptions *popts, const QString &code);

    QStringList getCompletion(int scriptHandleOrType, QString scriptName, QString word);

public slots:
    void onExecCode(QString code, int scriptHandleOrType, QString scriptName);
    void onGetPrevCompletion(int scriptHandleOrType, QString scriptName, QString prefix, QString selection);
    void onGetNextCompletion(int scriptHandleOrType, QString scriptName, QString prefix, QString selection);
    void onAskCallTip(int scriptHandleOrType, QString symbol);

signals:
    void scriptListChanged(QMap<int,QString> childScripts, QMap<int,QString> customizationScripts, bool simRunning);
    void setCompletion(QString s);
    void setCallTip(QString s);
    void historyChanged(QStringList history);
    void addStatusbarMessage(const QString &s, bool html);
    void addStatusbarWarning(const QString &s, bool html);
    void addStatusbarError(const QString &s, bool html);

private:
    PersistentOptions options;
    QStringList stringRenderingFlags;
};

#endif // UIFUNCTIONS_H_INCLUDED

