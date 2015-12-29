#include "MModel.h"

MModel::MModel(QObject *parent) : QSqlTableModel(parent)
{
    QObject::connect(this, &MModel::strategyChanged, this, &MModel::strategyChangedSlot);
    this->setTable("items");
    this->select();
}

QHash<int, QByteArray> MModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[IdRole] = "item_id";
    roles[ItemRole] = "item";

    return roles;
}

QVariant MModel::data(const QModelIndex &index, int role) const
{
    QVariant r = QSqlTableModel::data(index, role);

    if(role >= Qt::UserRole)
    {
        int columnIndex = role - Qt::UserRole - 1;
        QModelIndex idx = this->index(index.row(), columnIndex);

        r = QSqlTableModel::data(idx, Qt::DisplayRole);
    }

    return r;
}

bool MModel::deleteItem(int itemId)
{
    bool r = false;

    // First we have to find the index of the given item:
    QModelIndexList list = this->match(
        this->index(0, 0),
        MModel::IdRole,
        itemId,
        1,
        Qt::MatchExactly);

    // And then we can delete it:
    //   The list length should be exactly 1.
    if(list.length() > 0)
    {
        // For some reason, if the list length is > 1,
        // we take the first result :
        QModelIndex idx = list[0];

        r = this->removeRows(idx.row(), 1);
    }
    else
    {
        // The index could not be found.
        // This isn't supposed to happen.
        // A real app should throw an Exception, print an error or whatever.
    }

    qDebug() << "";
    qDebug() << "I've just told the model to delete the item with id:" << itemId;
    qDebug() << "EditStrategy is set to" << this->editStrategy();

    if(this->m_strategy == MModel::OnFieldChange)
    {
        qDebug() << "Now I have to call select() to update the view. If I don't, the deleted item remain(s) visible.";
        qDebug() << "    (the item has been deleted in the database, but the view still shows it !)";
        qDebug() << "If this is the only running remorse, everything is OK.";
        qDebug() << "If there is another running remorse, I will segfault.";
        this->select();
    }
    else
    {

        qDebug() << "Now I have to call submitAll() to update the view. If I don't, the deleted item remain(s) visible.";
        qDebug() << "    (the item still exists in the db, but it has been removed from the model !)";
        qDebug() << "If this is the only running remorse, everything is OK.";
        qDebug() << "If there is another running remorse, I will segfault.";
        this->submitAll();
    }

    qDebug() << "";

    return r;
}

MModel::Strategies MModel::strategy() const
{
    return this->m_strategy;
}

void MModel::setStrategy(const Strategies &newStrategy)
{
    this->m_strategy = newStrategy;
    Q_EMIT strategyChanged();
}

void MModel::strategyChangedSlot()
{
    if(this->m_strategy == MModel::OnFieldChange)
        this->setEditStrategy(QSqlTableModel::OnFieldChange);
    else
        this->setEditStrategy(QSqlTableModel::OnManualSubmit);

    qDebug() << "Changed edit strategy for" << this->editStrategy();
}
