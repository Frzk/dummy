#ifndef MMODEL_H
#define MMODEL_H

#include <QDebug>
#include <QSqlTableModel>

class MModel : public QSqlTableModel
{
    Q_OBJECT
    Q_ENUMS(Strategies)
    Q_PROPERTY(Strategies strategy READ strategy WRITE setStrategy NOTIFY strategyChanged)

    public:
        enum Roles {
            IdRole = Qt::UserRole + 1,
            ItemRole
        };

        enum Strategies {
            OnFieldChange,
            OnManualSubmit
        };

        explicit MModel(QObject *parent = 0);
        QHash<int, QByteArray> roleNames() const;
        QVariant data(const QModelIndex &index, int role) const;

        Strategies  strategy() const;
        void        setStrategy(const Strategies &newStrategy);

        Q_INVOKABLE bool deleteItem(const int itemId);

    signals:
        void    strategyChanged();

    private:
        Strategies m_strategy;

    private slots:
        void strategyChangedSlot();
};

#endif // MMODEL_H
