This small SailfishOS app tries to demonstrate an issue when a user **deletes several items** from a SilicaListView *at the same time* and the underlying model is a QSqlTableModel.
*At the same time* means that several remorses have to run at the same time. So the user basically has to delete an item, and when the remorse for this item is running, the user has to launch the deletion of another item.

Behavior is as follows :

  - With model.editStrategy set to QSqlTableModel::OnManualSubmit :
      * The database isn't updated unless you call `submitAll()`.
      * The view isn't either : the deleted item remains.
      * Calling `submitAll()` automatically calls `select()` which resets the model : any other running remorse is lost and the app segfaults.

  - With model.editStrategy set to QSqlTableModel::OnFieldChanged :
      * The database is updated immediately, which is great.
      * BUT the view isn't updated : the deleted item remains.
      * To "hide" it, you have to call `select()`, which resets the model : any other running remorse is lost and the app segfaults.

**Please read the console output for further details.**

I've tried to keep the code easy to read and understand. Hope this will be useful.
