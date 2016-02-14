/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                         *
 *  Copyright (C) 2015 Simon Stuerz <stuerz.simon@gmail.com>               *
 *                                                                         *
 *  This file is part of guh-ubuntu.                                       *
 *                                                                         *
 *  guh-ubuntu is free software: you can redistribute it and/or modify     *
 *  it under the terms of the GNU General Public License as published by   *
 *  the Free Software Foundation, version 3 of the License.                *
 *                                                                         *
 *  guh-ubuntu is distributed in the hope that it will be useful,          *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the           *
 *  GNU General Public License for more details.                           *
 *                                                                         *
 *  You should have received a copy of the GNU General Public License      *
 *  along with guh-ubuntu. If not, see <http://www.gnu.org/licenses/>.     *
 *                                                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

import QtQuick 2.4
import QtQuick.Layouts 1.1
import Ubuntu.Components 1.3
import Ubuntu.Components.ListItems 1.3
import Guh 1.0

Item {
    id: root

    Loader {
        id: inputLoader
        sourceComponent: paramType.minValue ? sliderInputLine : numberInputLine
    }

    Component {
        id: numberInputLine
        Column {
            Item {
                width: parent.width
                height: units.gu(6)

                Label {
                    anchors.left: parent.left
                    anchors.leftMargin: units.gu(2)
                    anchors.verticalCenter: parent.verticalCenter
                    font.capitalization: Font.Capitalize
                    text: paramType.name
                }

                TextField {
                    id: textField
                    anchors.right: parent.right
                    anchors.rightMargin: units.gu(2)
                    anchors.verticalCenter: parent.verticalCenter
                    width: units.gu(12)
                    inputMethodHints: Qt.ImhFormattedNumbersOnly
                    onTextChanged: {
                        paramValue =  textField.text
                    }
                    Component.onCompleted: paramValue = 0
                }
            }

            ThinDivider {}
        }
    }

    Component {
        id: sliderInputLine
        Column {
            Item {
                width: parent.width
                height: units.gu(6)

                Label {
                    id: nameLable
                    anchors.left: parent.left
                    anchors.leftMargin: units.gu(2)
                    anchors.verticalCenter: parent.verticalCenter
                    font.capitalization: Font.Capitalize
                    text: paramType.name
                }

                Slider {
                    id: slider
                    anchors.right: parent.right
                    anchors.rightMargin: units.gu(2)
                    anchors.verticalCenter: parent.verticalCenter
                    width: units.gu(20)
                    maximumValue: paramType.maxValue
                    minimumValue: paramType.minValue
                    onValueChanged: {
                        paramValue =  slider.value
                    }
                    //Component.onCompleted: slider.value = paramType.defaultValue
                }
            }

            ThinDivider {}
        }
    }
}


