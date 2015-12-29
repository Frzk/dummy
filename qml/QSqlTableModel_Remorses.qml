/*
  Copyright (C) 2013 Jolla Ltd.
  Contact: Thomas Perl <thomas.perl@jollamobile.com>
  All rights reserved.

  You may use this file under the terms of BSD license as follows:

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the Jolla Ltd nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR
  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

import QtQuick 2.0
import Sailfish.Silica 1.0

import com.example 1.0

ApplicationWindow
{
    initialPage: Component {
        Page {
            id: mainPage

            SilicaListView {
                anchors.fill: parent

                delegate: ListItem {
                    id: listItem

                    function deleteItem()
                    {
                        remorseAction(qsTr("Deleting item"), function() {
                            var deleted = itemsModel.deleteItem(model.item_id)
                            console.log("Deleted:", deleted);
                        })
                    }

                    menu: Component {
                        id: contextMenu

                        ContextMenu {
                            MenuItem {
                                text: qsTr("Delete")
                                onClicked: {
                                    deleteItem()
                                }
                            }
                        }
                    }

                    Label {
                        id: lbl

                        anchors {
                            fill: parent
                            bottomMargin: Theme.paddingMedium
                            leftMargin: Theme.horizontalPageMargin
                            rightMargin: anchors.leftMargin
                            topMargin: anchors.bottomMargin
                        }
                        color: highlighted ? Theme.highlightColor : Theme.primaryColor
                        font {
                            pixelSize: Theme.fontSizeMedium
                        }
                        text: model.item + " (" + model.item_id + ")"
                        width: parent.width
                    }

                    ListView.onAdd: AddAnimation { target: listItem }
                    ListView.onRemove: RemoveAnimation { target: listItem }
                }
                header: PageHeader {
                    title: itemsModel.strategy === MModel.OnFieldChange ?
                               "With \"OnFieldChange\"" :
                               "With \"OnManualSubmit\""
                }
                model: itemsModel

                PullDownMenu {
                    MenuItem {
                        text: "Switch to OnManualSubmit"
                        visible: itemsModel.strategy === MModel.OnFieldChange
                        onClicked: {
                            itemsModel.strategy = MModel.OnManualSubmit
                        }
                    }

                    MenuItem {
                        text: "Switch to OnFieldChange"
                        visible: itemsModel.strategy === MModel.OnManualSubmit
                        onClicked: {
                            itemsModel.strategy = MModel.OnFieldChange
                        }
                    }
                }
            }

            MModel {
                id: itemsModel

                strategy: MModel.OnFieldChange
            }
        }
    }

    cover: Qt.resolvedUrl("cover/CoverPage.qml")
    allowedOrientations: Orientation.All
    _defaultPageOrientations: Orientation.All
}


