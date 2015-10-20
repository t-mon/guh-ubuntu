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
import Ubuntu.Components 1.2
import Ubuntu.Components.ListItems 1.0
import Guh 1.0

Component {
    id: root

    Rectangle {
        id: mainRectangle
        anchors.fill: parent
        color: "transparent"

        Loader {
            id: inputLoader
            anchors.fill: parent
            anchors.margins: units.gu(2)
            sourceComponent: paramType.minValue ? sliderInputLine : numberInputLine
        }

        Component {
            id: numberInputLine

            Rectangle {
                id: rectangle
                anchors.fill: parent
                color: "transparent"

                Label {
                    anchors.left: rectangle.left
                    anchors.verticalCenter: rectangle.verticalCenter
                    font.capitalization: Font.Capitalize
                    text: paramType.name
                }

                TextField {
                    id: textField
                    anchors.right: rectangle.right
                    anchors.verticalCenter: rectangle.verticalCenter
                    width: units.gu(10)
                    inputMethodHints: Qt.ImhFormattedNumbersOnly
                    onTextChanged: {
                        value =  textField.text
                    }
                }
            }
        }

        Component {
            id: sliderInputLine

            Rectangle {
                id: rectangle
                anchors.fill: parent
                color: "transparent"

                Label {
                    id: nameLable
                    anchors.left: parent.left
                    anchors.verticalCenter: parent.verticalCenter
                    font.capitalization: Font.Capitalize
                    text: paramType.name
                }

                Slider {
                    id: slider
                    anchors.right: parent.right
                    anchors.verticalCenter: parent.verticalCenter
                    width: units.gu(20)
                    maximumValue: paramType.maxValue
                    minimumValue: paramType.minValue
                    onValueChanged: {
                        value =  slider.value
                    }
                }
            }
        }
    }
}

