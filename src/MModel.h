#ifndef MMODEL_H
#define MMODEL_H

#include <QDebug>
#include <QSqlTableModel>

class MModel : public QSqlTableModel
{
    Q_OBJECT
    Q_PROPERTY(int count READ count NOTIFY countChanged)

    public:
        enum Roles {
            ItemIdRole = Qt::UserRole + 1,
            ItemNameRole
        };

        explicit MModel(QObject *parent = 0);
        QHash<int, QByteArray> roleNames() const;
        QVariant data(const QModelIndex &index, int role) const;
        int count() const;

        Q_INVOKABLE bool deleteItem(int itemId);

    signals:
        void    countChanged();

    public slots:
        void    printCount() const;
};

#endif // MMODEL_H
