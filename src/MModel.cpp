#include "MModel.h"

MModel::MModel(QObject *parent) : QSqlTableModel(parent)
{
    this->setTable("items");
    this->setEditStrategy(QSqlTableModel::OnManualSubmit);
    this->setSort(0, Qt::AscendingOrder);
    this->select();
}

QHash<int, QByteArray> MModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[ItemIdRole] = "item_id";
    roles[ItemNameRole] = "item";

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
        MModel::ItemIdRole,
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
        int row = idx.row();

        // Make sure we do the right thing :
        qDebug() << "DELETE item with item_id =" << itemId << "stored at row" << row;


        // Keep in mind that we can't call submitAll() when a remorse is running.
        // If we do so, the app segfaults and crashes.

        // If we don't call `beginRemoveRows` and `endRemoveRows`,
        // the removed item remains visible in the listview until `submitAll` is called.
        // Sadly, we can't call `submitAll` each time because another remorse might be running...

        // If we **do** call `beginRemoveRows` and `endRemoveRows`,
        // the **last** item of the listview is removed (WTF ?!).
        // Calling `submitAll` refreshes the view and shows that the items have been properly removed.

        this->beginRemoveRows(QModelIndex(), row, row);
        r = this->removeRows(row, 1);
        this->endRemoveRows();
    }
    else
    {
        // The index could not be found.
        // This isn't supposed to happen.
        // A real app should throw an Exception, print an error or whatever.
    }

    return r;
}

int MModel::count() const
{
    return this->rowCount();
}
