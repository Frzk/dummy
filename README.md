This small SailfishOS app tries to demonstrate an issue when a user wants to **delete several items** from a SilicaListView **at the same time** (using a remorse timer) and the underlying model is a QSqlTableModel.

Behavior is as follows :

  - With model.editStrategy set to QSqlTableModel::OnManualSubmit :
      * The database isn't updated unless you call `submitAll()`.
      * The view isn't either : the deleted item remains.
      * Calling `submitAll()` automatically calls `select()` which resets the model : any other running remorse is lost and the app segfaults.

  - With model.editStrategy set to QSqlTableModel::OnFieldChanged :
      * The database is updated immediately, which is great.
      * BUT the view isn't updated : the deleted item remains.
      * To "hide" it, you have to call `select()`, which resets the model : any other running remorse is lost and the app segfaults.

Please read the console output for further details.

I've tried to keep the code easy to read and understand. Hope this will be useful.
