import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import matzman666.advsettings 1.0


MyStackViewPage {
    headerText: "Revive Settings"

    content: ColumnLayout {
        spacing: 32

        RowLayout {
            MyToggleButton {
                id: pixelsPerDisplayPixelToggle
                text: "Render Target Override:"
                Layout.preferredWidth: 350
                onCheckedChanged: {
                    ReviveTabController.setPixelsPerDisplayPixelOverrideEnabled(checked, false)
                }
            }

            MyPushButton2 {
                text: "-"
                Layout.preferredWidth: 40
                onClicked: {
                    pixelsPerDisplayPixelSlider.decrease()
                }
            }

            MySlider {
                id: pixelsPerDisplayPixelSlider
                from: 0.1
                to: 4.0
                stepSize: 0.1
                value: 1.0
                Layout.fillWidth: true
                onPositionChanged: {
                    var val = this.from + ( this.position  * (this.to - this.from))
                    pixelsPerDisplayPixelText.text = val.toFixed(1)
                }
                onValueChanged: {
                    ReviveTabController.setPixelsPerDisplayPixelOverride(value)
                }
            }

            MyPushButton2 {
                text: "+"
                Layout.preferredWidth: 40
                onClicked: {
                    pixelsPerDisplayPixelSlider.increase()
                }
            }

            MyTextField {
                id: pixelsPerDisplayPixelText
                text: "0.00"
                keyBoardUID: 221
                Layout.preferredWidth: 100
                Layout.leftMargin: 10
                horizontalAlignment: Text.AlignHCenter
                function onInputEvent(input) {
                    var val = parseFloat(input)
                    if (!isNaN(val)) {
                        if (val < 0.1) {
                            val = 0.1
                        }
                        var v = val.toFixed(1)
                        pixelsPerDisplayPixelSlider.value = v
                        ReviveTabController.setPixelsPerDisplayPixelOverride(v, false)
                        text = v
                    } else {
                        text = ReviveTabController.pixelsPerDisplayPixelOverride.toFixed(1)
                    }
                }
            }
        }


        RowLayout {
            MyText {
                text: "Grip Button Mode:"
                Layout.preferredWidth: 350
            }

            MyComboBox {
                id: gripButtonModeComboBox
                Layout.fillWidth: true
                model: ["Normal Mode", "Toggle Mode", "Hybrid Mode"]
                onCurrentIndexChanged: {
                    ReviveTabController.setGripButtonMode(currentIndex, false)
                }
            }
        }

        GroupBox {
            Layout.fillWidth: true

            label: MyText {
                leftPadding: 10
                text: "Thumbstick Settings"
                bottomPadding: -10
            }
            background: Rectangle {
                color: "transparent"
                border.color: "#ffffff"
                radius: 8
            }
            ColumnLayout {
                anchors.fill: parent

                Rectangle {
                    color: "#ffffff"
                    height: 1
                    Layout.fillWidth: true
                    Layout.bottomMargin: 5
                }

                ColumnLayout {

                    RowLayout {
                        MyText {
                            text: "Deadzone:"
                            Layout.rightMargin: 12
                        }

                        MyPushButton2 {
                            id: thumbDeadzoneMinusButton
                            Layout.preferredWidth: 40
                            text: "-"
                            onClicked: {
                                thumbDeadzoneSlider.decrease()
                            }
                        }

                        MySlider {
                            id: thumbDeadzoneSlider
                            from: 0.0
                            to: 1.0
                            stepSize: 0.01
                            value: 0.5
                            Layout.fillWidth: true
                            onPositionChanged: {
                                var val = this.from + ( this.position  * (this.to - this.from))
                                thumbDeadzoneText.text = val.toFixed(2)
                            }
                            onValueChanged: {
                                ReviveTabController.setThumbDeadzone(value.toFixed(2))
                            }
                        }

                        MyPushButton2 {
                            id: thumbDeadzonePlusButton
                            Layout.preferredWidth: 40
                            text: "+"
                            onClicked: {
                                thumbDeadzoneSlider.increase()
                            }
                        }

                        MyTextField {
                            id: thumbDeadzoneText
                            text: "0.00"
                            keyBoardUID: 222
                            Layout.preferredWidth: 100
                            Layout.leftMargin: 10
                            horizontalAlignment: Text.AlignHCenter
                            function onInputEvent(input) {
                                var val = parseFloat(input)
                                if (!isNaN(val)) {
                                    if (val < 0.0) {
                                        val = 0.0
                                    } else if (val > 1.0) {
                                        val = 1.0
                                    }
                                    var v = val.toFixed(2)
                                    thumbDeadzoneSlider.value = v
                                    ReviveTabController.setThumbDeadzone(v, false)
                                    text = v
                                } else {
                                    text = ReviveTabController.thumbDeadzone.toFixed(2)
                                }
                            }
                        }
                    }

                    RowLayout {
                        MyText {
                            text: "Sensitivity:"
                            Layout.rightMargin: 12
                        }

                        MyPushButton2 {
                            id: thumbRangeMinusButton
                            Layout.preferredWidth: 40
                            text: "-"
                            onClicked: {
                                thumbRangeSlider.decrease()
                            }
                        }

                        MySlider {
                            id: thumbRangeSlider
                            from: 1.0
                            to: 5.0
                            stepSize: 0.01
                            value: 2.0
                            Layout.fillWidth: true
                            onPositionChanged: {
                                var val = this.from + ( this.position  * (this.to - this.from))
                                thumbRangeText.text = val.toFixed(2)
                            }
                            onValueChanged: {
                                ReviveTabController.setThumbRange(value.toFixed(2))
                            }
                        }

                        MyPushButton2 {
                            id: thumbRangePlusButton
                            Layout.preferredWidth: 40
                            text: "+"
                            onClicked: {
                                thumbRangeSlider.increase()
                            }
                        }

                        MyTextField {
                            id: thumbRangeText
                            text: "0.00"
                            keyBoardUID: 223
                            Layout.preferredWidth: 100
                            Layout.leftMargin: 10
                            horizontalAlignment: Text.AlignHCenter
                            function onInputEvent(input) {
                                var val = parseFloat(input)
                                if (!isNaN(val)) {
                                    if (val < 0.01) {
                                        val = 0.01
                                    }
                                    var v = val.toFixed(2)
                                    thumbRangeSlider.value = v
                                    ReviveTabController.setThumbRange(v, false)
                                    text = v
                                } else {
                                    text = ReviveTabController.thumbRange.toFixed(2)
                                }
                            }
                        }
                    }
                }
            }
        }

        GroupBox {
            Layout.fillWidth: true

            label: MyText {
                leftPadding: 10
                text: "Controller Offsets"
                bottomPadding: -10
            }
            background: Rectangle {
                color: "transparent"
                border.color: "#ffffff"
                radius: 8
            }
            ColumnLayout {
                anchors.fill: parent

                Rectangle {
                    color: "#ffffff"
                    height: 1
                    Layout.fillWidth: true
                    Layout.bottomMargin: 5
                }

                GridLayout {
                    columns: 12

                    MyText {
                        text: "Pitch:"
                        horizontalAlignment: Text.AlignRight
                        Layout.preferredWidth: 80
                        Layout.rightMargin: 12
                    }

                    MyPushButton2 {
                        id: touchPitchMinusButton
                        Layout.preferredWidth: 40
                        text: "-"
                        onClicked: {
                            var val = ReviveTabController.touchPitch - 0.1
                            if (val < -180.0) {
                                val = -180.0
                            }
                            ReviveTabController.setTouchPitch(val.toFixed(1))
                        }
                    }

                    MyTextField {
                        id: touchPitchInputField
                        text: "0.00"
                        keyBoardUID: 201
                        Layout.preferredWidth: 140
                        Layout.leftMargin: 10
                        Layout.rightMargin: 10
                        horizontalAlignment: Text.AlignHCenter
                        function onInputEvent(input) {
                            var val = parseFloat(input)
                            if (!isNaN(val)) {
                                if (val < -180.0) {
                                    val = -180.0
                                } else if (val > 180.0) {
                                    val = 180.0
                                }
                                var v = val.toFixed(1)
                                ReviveTabController.setTouchPitch(v, false)
                                text = v + "°"
                            } else {
                                text = ReviveTabController.touchPitch.toFixed(1) + "°"
                            }
                        }
                    }

                    MyPushButton2 {
                        id: touchPitchPlusButton
                        Layout.preferredWidth: 40
                        text: "+"
                        onClicked: {
                            var val = ReviveTabController.touchPitch + 0.1
                            if (val > 180.0) {
                                val = 180.0
                            }
                            ReviveTabController.setTouchPitch(val.toFixed(1))
                        }
                    }

                    MyText {
                        text: "Yaw:"
                        Layout.fillWidth: true
                        horizontalAlignment: Text.AlignRight
                        Layout.leftMargin: 12
                        Layout.rightMargin: 12
                    }

                    MyPushButton2 {
                        id: touchYawMinusButton
                        Layout.preferredWidth: 40
                        text: "-"
                        onClicked: {
                            var val = ReviveTabController.touchYaw - 0.1
                            if (val < -180.0) {
                                val = -180.0
                            }
                            ReviveTabController.setTouchYaw(val.toFixed(1))
                        }
                    }

                    MyTextField {
                        id: touchYawInputField
                        text: "0.00"
                        keyBoardUID: 202
                        Layout.preferredWidth: 140
                        Layout.leftMargin: 10
                        Layout.rightMargin: 10
                        horizontalAlignment: Text.AlignHCenter
                        function onInputEvent(input) {
                            var val = parseFloat(input)
                            if (!isNaN(val)) {
                                if (val < -180.0) {
                                    val = -180.0
                                } else if (val > 180.0) {
                                    val = 180.0
                                }
                                var v = val.toFixed(1)
                                ReviveTabController.setTouchYaw(v, false)
                                text = v + "°"
                            } else {
                                text = ReviveTabController.touchYaw.toFixed(1) + "°"
                            }
                        }
                    }

                    MyPushButton2 {
                        id: touchYawPlusButton
                        Layout.preferredWidth: 40
                        text: "+"
                        onClicked: {
                            var val = ReviveTabController.touchYaw + 0.1
                            if (val > 180.0) {
                                val = 180.0
                            }
                            ReviveTabController.setTouchYaw(val.toFixed(1))
                        }
                    }

                    MyText {
                        text: "Roll:"
                        Layout.fillWidth: true
                        horizontalAlignment: Text.AlignRight
                        Layout.leftMargin: 12
                        Layout.rightMargin: 12
                    }

                    MyPushButton2 {
                        id: touchRollMinusButton
                        Layout.preferredWidth: 40
                        text: "-"
                        onClicked: {
                            var val = ReviveTabController.touchRoll - 0.1
                            if (val < -180.0) {
                                val = -180.0
                            }
                            ReviveTabController.setTouchRoll(val.toFixed(1))
                        }
                    }

                    MyTextField {
                        id: touchRollInputField
                        text: "0.00"
                        keyBoardUID: 203
                        Layout.preferredWidth: 140
                        Layout.leftMargin: 10
                        Layout.rightMargin: 10
                        horizontalAlignment: Text.AlignHCenter
                        function onInputEvent(input) {
                            var val = parseFloat(input)
                            if (!isNaN(val)) {
                                if (val < -180.0) {
                                    val = -180.0
                                } else if (val > 180.0) {
                                    val = 180.0
                                }
                                var v = val.toFixed(1)
                                ReviveTabController.setTouchRoll(v, false)
                                text = v + "°"
                            } else {
                                text = ReviveTabController.touchRoll.toFixed(1) + "°"
                            }
                        }
                    }

                    MyPushButton2 {
                        id: touchRollPlusButton
                        Layout.preferredWidth: 40
                        text: "+"
                        onClicked: {
                            var val = ReviveTabController.touchRoll + 0.1
                            if (val > 180.0) {
                                val = 180.0
                            }
                            ReviveTabController.setTouchRoll(val.toFixed(1))
                        }
                    }

                    MyText {
                        text: "X:"
                        horizontalAlignment: Text.AlignRight
                        Layout.preferredWidth: 80
                        Layout.rightMargin: 12
                    }

                    MyPushButton2 {
                        id: touchXMinusButton
                        Layout.preferredWidth: 40
                        text: "-"
                        onClicked: {
                            ReviveTabController.setTouchX((ReviveTabController.touchX - 0.001).toFixed(3))
                        }
                    }

                    MyTextField {
                        id: touchXInputField
                        text: "0.00"
                        keyBoardUID: 204
                        Layout.preferredWidth: 140
                        Layout.leftMargin: 10
                        Layout.rightMargin: 10
                        horizontalAlignment: Text.AlignHCenter
                        function onInputEvent(input) {
                            var val = parseFloat(input)
                            if (!isNaN(val)) {
                                var v = val.toFixed(3)
                                ReviveTabController.setTouchX(v, false)
                                text = v
                            } else {
                                text = ReviveTabController.touchX.toFixed(3)
                            }
                        }
                    }

                    MyPushButton2 {
                        id: touchXPlusButton
                        Layout.preferredWidth: 40
                        text: "+"
                        onClicked: {
                            ReviveTabController.setTouchX((ReviveTabController.touchX + 0.001).toFixed(3))
                        }
                    }

                    MyText {
                        text: "Y:"
                        Layout.fillWidth: true
                        horizontalAlignment: Text.AlignRight
                        Layout.leftMargin: 12
                        Layout.rightMargin: 12
                    }

                    MyPushButton2 {
                        id: touchYMinusButton
                        Layout.preferredWidth: 40
                        text: "-"
                        onClicked: {
                            ReviveTabController.setTouchY((ReviveTabController.touchY - 0.001).toFixed(3))
                        }
                    }

                    MyTextField {
                        id: touchYInputField
                        text: "0.00"
                        keyBoardUID: 205
                        Layout.preferredWidth: 140
                        Layout.leftMargin: 10
                        Layout.rightMargin: 10
                        horizontalAlignment: Text.AlignHCenter
                        function onInputEvent(input) {
                            var val = parseFloat(input)
                            if (!isNaN(val)) {
                                var v = val.toFixed(3)
                                ReviveTabController.setTouchY(v, false)
                                text = v
                            } else {
                                text = ReviveTabController.touchY.toFixed(3)
                            }
                        }
                    }

                    MyPushButton2 {
                        id: touchYPlusButton
                        Layout.preferredWidth: 40
                        text: "+"
                        onClicked: {
                            ReviveTabController.setTouchY((ReviveTabController.touchY + 0.001).toFixed(3))
                        }
                    }

                    MyText {
                        text: "Z:"
                        Layout.fillWidth: true
                        horizontalAlignment: Text.AlignRight
                        Layout.leftMargin: 12
                        Layout.rightMargin: 12
                    }

                    MyPushButton2 {
                        id: touchZMinusButton
                        Layout.preferredWidth: 40
                        text: "-"
                        onClicked: {
                            ReviveTabController.setTouchZ((ReviveTabController.touchZ - 0.001).toFixed(3))
                        }
                    }

                    MyTextField {
                        id: touchZInputField
                        text: "0.00"
                        keyBoardUID: 206
                        Layout.preferredWidth: 140
                        Layout.leftMargin: 10
                        Layout.rightMargin: 10
                        horizontalAlignment: Text.AlignHCenter
                        function onInputEvent(input) {
                            var val = parseFloat(input)
                            if (!isNaN(val)) {
                                var v = val.toFixed(3)
                                ReviveTabController.setTouchZ(v, false)
                                text = v
                            } else {
                                text = ReviveTabController.touchZ.toFixed(3)
                            }
                        }
                    }

                    MyPushButton2 {
                        id: touchZPlusButton
                        Layout.preferredWidth: 40
                        text: "+"
                        onClicked: {
                            ReviveTabController.setTouchZ((ReviveTabController.touchZ + 0.001).toFixed(3))
                        }
                    }
                }
            }
        }


        MyDialogOkCancelPopup {
            id: revivePersonalInfoDialog
            property double playerHeight: 0.0
            property double eyeHeight: 0.0
            dialogWidth: 600
            dialogHeight: 440
            dialogTitle: "Personal Information"
            dialogContentItem: GridLayout {
                rowSpacing: 6
                columnSpacing: 18
                columns: 2
                MyText {
                    text: "Username:"
                }
                MyTextField {
                    id: rpidUsername
                    text: "0.00"
                    keyBoardUID: 211
                    Layout.fillWidth: true
                    function onInputEvent(input) {
                        rpidUsername.text = input
                    }
                }
                MyText {
                    text: "Name:"
                }
                MyTextField {
                    id: rpidName
                    text: "0.00"
                    keyBoardUID: 212
                    Layout.fillWidth: true
                    function onInputEvent(input) {
                        rpidName.text = input
                    }
                }
                MyText {
                    text: "Gender:"
                }
                MyComboBox {
                    id: rpidGender
                    Layout.fillWidth: true
                    currentIndex: 2
                    model: ["Unknown", "Male", "Female"]
                }
                MyText {
                    text: "Player Height:"
                }
                RowLayout {
                    Item {
                        Layout.fillWidth: true
                    }
                    MyPushButton2 {
                        id: pridPlayerHeighMinusButton
                        Layout.preferredWidth: 40
                        text: "-"
                        onClicked: {
                            if (revivePersonalInfoDialog.playerHeight > 0.01) {
                                revivePersonalInfoDialog.playerHeight = (revivePersonalInfoDialog.playerHeight - 0.01).toFixed(2)
                            }
                            pridPlayerHeighInputField.text = revivePersonalInfoDialog.playerHeight.toFixed(2)
                        }
                    }
                    MyTextField {
                        id: pridPlayerHeighInputField
                        text: "0.00"
                        keyBoardUID: 213
                        Layout.preferredWidth: 120
                        Layout.leftMargin: 10
                        Layout.rightMargin: 10
                        horizontalAlignment: Text.AlignHCenter
                        function onInputEvent(input) {
                            var val = parseFloat(input)
                            if (!isNaN(val)) {
                                if (val < 0.01) {
                                    val = 0.01
                                }
                                revivePersonalInfoDialog.playerHeight = val.toFixed(2)
                                text = val.toFixed(2)
                            } else {
                                text = val.toFixed(2)
                            }
                        }
                    }
                    MyPushButton2 {
                        id: pridPlayerHeighPlusButton
                        Layout.preferredWidth: 40
                        text: "+"
                        onClicked: {
                            revivePersonalInfoDialog.playerHeight = (revivePersonalInfoDialog.playerHeight + 0.01).toFixed(2)
                            pridPlayerHeighInputField.text = revivePersonalInfoDialog.playerHeight.toFixed(2)
                        }
                    }
                    Item {
                        Layout.fillWidth: true
                    }
                }
                MyText {
                    text: "Eye Height:"
                }
                RowLayout {
                    Item {
                        Layout.fillWidth: true
                    }
                    MyPushButton2 {
                        id: pridEyeHeighMinusButton
                        Layout.preferredWidth: 40
                        text: "-"
                        onClicked: {
                            if (revivePersonalInfoDialog.eyeHeight > 0.01) {
                                revivePersonalInfoDialog.eyeHeight = (revivePersonalInfoDialog.eyeHeight - 0.01).toFixed(2)
                            }
                            pridEyeHeighInputField.text = revivePersonalInfoDialog.eyeHeight.toFixed(2)
                        }
                    }
                    MyTextField {
                        id: pridEyeHeighInputField
                        text: "0.00"
                        keyBoardUID: 214
                        Layout.preferredWidth: 120
                        Layout.leftMargin: 10
                        Layout.rightMargin: 10
                        horizontalAlignment: Text.AlignHCenter
                        function onInputEvent(input) {
                            var val = parseFloat(input)
                            if (!isNaN(val)) {
                                if (val < 0.01) {
                                    val = 0.01
                                }
                                revivePersonalInfoDialog.eyeHeight = val.toFixed(2)
                                text = val.toFixed(2)
                            } else {
                                text = val.toFixed(2)
                            }
                        }
                    }
                    MyPushButton2 {
                        id: pridEyeHeighPlusButton
                        Layout.preferredWidth: 40
                        text: "+"
                        onClicked: {
                            revivePersonalInfoDialog.eyeHeight = (revivePersonalInfoDialog.eyeHeight + 0.01).toFixed(2)
                            pridEyeHeighInputField.text = revivePersonalInfoDialog.eyeHeight.toFixed(2)
                        }
                    }
                    Item {
                        Layout.fillWidth: true
                    }
                }
            }
            function openPopup() {
                rpidUsername.text = ReviveTabController.piUsername
                rpidName.text = ReviveTabController.piName
                rpidGender.currentIndex = ReviveTabController.piGender
                playerHeight = ReviveTabController.piPlayerHeight
                pridPlayerHeighInputField.text = playerHeight.toFixed(2)
                eyeHeight = ReviveTabController.piEyeHeight
                pridEyeHeighInputField.text = eyeHeight.toFixed(2)
                open()
            }
            onClosed: {
                if (okClicked) {
                    ReviveTabController.setPiUsername(rpidUsername.text, false)
                    ReviveTabController.setPiName(rpidName.text, false)
                    ReviveTabController.setPiGender(rpidGender.currentIndex, false)
                    ReviveTabController.setPiPlayerHeight(playerHeight, false)
                    ReviveTabController.setPiEyeHeight(eyeHeight, false)
                }
            }
        }

        MyPushButton {
            id: revivePersonalInfoButton
            Layout.preferredWidth: 300
            text: "Personal Information"
            onClicked: {
                revivePersonalInfoDialog.openPopup()
            }
        }

        Item {
            Layout.fillHeight: true
        }

        Component.onCompleted: {
            pixelsPerDisplayPixelToggle.checked = ReviveTabController.pixelsPerDisplayPixelOverrideEnabled
            var v = ReviveTabController.pixelsPerDisplayPixelOverride.toFixed(1)
            pixelsPerDisplayPixelSlider.value = v
            pixelsPerDisplayPixelText.text = v

            gripButtonModeComboBox.currentIndex = ReviveTabController.gripButtonMode

            v = ReviveTabController.thumbDeadzone.toFixed(2)
            thumbDeadzoneSlider.value = v
            thumbDeadzoneText.text = v

            v = ReviveTabController.thumbRange.toFixed(2)
            thumbRangeSlider.value = v
            thumbRangeText.text = v

            touchPitchInputField.text = ReviveTabController.touchPitch.toFixed(1) + "°"
            touchYawInputField.text = ReviveTabController.touchYaw.toFixed(1) + "°"
            touchRollInputField.text = ReviveTabController.touchRoll.toFixed(1) + "°"
            touchXInputField.text = ReviveTabController.touchX.toFixed(3)
            touchYInputField.text = ReviveTabController.touchY.toFixed(3)
            touchZInputField.text = ReviveTabController.touchZ.toFixed(3)
        }

        Connections {
            target: ReviveTabController
            onGripButtonModeChanged : {
                gripButtonModeComboBox.currentIndex = ReviveTabController.gripButtonMode
            }
            onPixelsPerDisplayPixelOverrideEnabledChanged : {
                pixelsPerDisplayPixelToggle.checked = ReviveTabController.pixelsPerDisplayPixelOverrideEnabled
            }
            onPixelsPerDisplayPixelOverrideChanged : {
                var v = ReviveTabController.pixelsPerDisplayPixelOverride.toFixed(1)
                pixelsPerDisplayPixelSlider.value = v
                pixelsPerDisplayPixelText.text = v
            }
            onThumbDeadzoneChanged : {
                var v = ReviveTabController.thumbDeadzone.toFixed(2)
                thumbDeadzoneSlider.value = v
                thumbDeadzoneText.text = v
            }
            onThumbRangeChanged : {
                var v = ReviveTabController.thumbRange.toFixed(2)
                thumbRangeSlider.value = v
                thumbRangeText.text = v
            }
            onTouchPitchChanged : {
                touchPitchInputField.text = ReviveTabController.touchPitch.toFixed(1) + "°"
            }
            onTouchYawChanged : {
                touchYawInputField.text = ReviveTabController.touchYaw.toFixed(1) + "°"
            }
            onTouchRollChanged : {
                touchRollInputField.text = ReviveTabController.touchRoll.toFixed(1) + "°"
            }
            onTouchXChanged : {
                touchXInputField.text = ReviveTabController.touchX.toFixed(3)
            }
            onTouchYChanged : {
                touchYInputField.text = ReviveTabController.touchY.toFixed(3)
            }
            onTouchZChanged : {
                touchZInputField.text = ReviveTabController.touchZ.toFixed(3)
            }
        }
    }
}
