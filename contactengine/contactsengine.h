#ifndef CONTACTSENGINE_H
#define CONTACTSENGINE_H

#include <QAbstractListModel>
#include <QContactManager>
#include <QPointer>

#include "contactsengine.h"

using namespace QtMobility;

class ContactsEngine : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit ContactsEngine(QObject *parent = 0);
    ~ContactsEngine();

    // index() and parent()  are defined by QAbstractListModel. So we do not
    // need to define the QModelIndex
    // required by list model interface.
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;

    QStringList dataSources();

public:
    void populateAddresses();
    void dumpContactMgr(); // use for debugging. Hard to inspect it via Qt Creator.
    void enumerateMgrs();
    void createManager();
    void createManagerSF();

signals:
    void errorOccurred(QString errMsg); // when a error message

public slots:
    void setManager(const QString &aMgr);

private:
    QString errorString(QContactManager::Error);

private:
    QMap<QString, QString> m_availableManagers;
    // this is the default mgr. On device, it pull info from contacts as expected.
    QPointer<QContactManager> m_manager;
    // this one is simply in memory. Put the Symbian Foundation contacts here.
    QPointer<QContactManager> m_manager_sf;
    // cache list of all contacts.
    QList<QContact> m_allContacts;
};

#endif // CONTACTSENGINE_H
