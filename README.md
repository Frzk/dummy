This minimal SailfishOS app tries to demonstrate the issues you get when using a QSqlTableModel and trying to remove items from it.

I was first surprised to discover that `QSqlTableModel::removeRows` doesn't call `beginRemoveRows` nor `endRemoveRows`.

I was also surprised to see that `rowCount` always return the right value when you add items the model, but that it doesn't when you remove items from the model !


Behavior is as follows :

  - With model.editStrategy set to QSqlTableModel::OnManualSubmit :

      1. First case : without `beginRemoveRows` and `endRemoveRows` :

          * *Expected* : The database isn't updated unless you call `submitAll`.
          * *Unexpected* : The view isn't either : the deleted item remains visible in the SilicaListView with original values.
          * *Unexpected* : `rowCount` doesn't return the right value after a deletion.
          * *Expected* : Calling `submitAll` automatically calls `select` which resets the model : if there is a remorse running, the app crashes.

      2. Second case : with `beginRemoveRows` and `endRemoveRows` :

          * *Expected* : The database isn't updated until you call `submitAll`.
          * *Unexpected* : The last item of the SilicaListView is removed (!!), no matter what item you wanted to delete.
          * *Unexpected* : `rowCount` doesn't return the right value after a deletion.
          * *Expected* : Calling `submitAll` automatically calls `select` which resets the model : if there is a remorse running, the app crashes.


  - With model.editStrategy set to QSqlTableModel::OnFieldChanged :

      1. First case : without `beginRemoveRows` and `endRemoveRows` :

          * *Expected* : The database is updated immediately.
          * *Unexpected* : The deleted item remains visible in the SilicaListView with *undefined* values unless you call `select`.
          * *Unexpected* : `rowCount` doesn't return the right value after a deletion.
          * *Expected* : Calling `select` refreshes the model : if there is a remorse running, the app crashes.

      2. Second case : with `beginRemoveRows` and `endRemoveRows` :

          * *Expected* : The database is updated immediately.
          * *Unexpected* : The deleted item remains visible in the SilicaListView with *undefined* values.
          * *Unexpected* : The last item of the SilicaListView is removed (!!), no matter what item you wanted to delete.
          * *Unexpected* : `rowCount` doesn't return the right value after a deletion.
          * *Expected* : Calling `select` refreshes the model : if there is a remorse running, the app crashes.


I've tried to keep the code easy to read and understand. Hope this will be useful.
