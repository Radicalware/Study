import QtQuick 2.12 // version (look down at their chart): https://doc.qt.io/qt-5/qtquickcontrols-index.html
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1
import QtGraphicalEffects 1

import "JavaScript/Action.js" as Action

// https://doc.qt.io/qt-5/qtquickcontrols2-customize.html

Window {
    id: main

    visible: true
    width: 1280
    height: 600
    title: qsTr("Example Number 2")
    property var mFontSize: main.width / 45


    Button {
        id : mButtonExecute
        text: "Execute"
        font.pixelSize: main.mFontSize

        onClicked: {
            mTextArea1.text = mTextArea1.text.replace(/([^\d])/g,'')
            Core.AllNumbers = mTextArea1.text
            Core.FindNumberSequence();
        }
    }

    Item{
        id: spacer1
        anchors.left: mButtonExecute.right
        width: 7
    }

    Button {
        id : mButtonGenerate
        text: "Generate"
        font.pixelSize: main.mFontSize
        anchors.left:   spacer1.right
        onClicked: {
            Core.Generate()
        }
    }
    
    Switch {
        id: mSwitchThreading
        text: qsTr("Threaded")
        font.pixelSize: main.mFontSize
        anchors.left: mButtonGenerate.right
        onClicked: {
            Core.UseThreading = mSwitchThreading.checked
        }
    }

    Switch {
        id: mSwitchSize
        text: qsTr("8 Nums")
        font.pixelSize: main.mFontSize
        anchors.left: mSwitchThreading.right
        onClicked: {
            Core.UseEightNums = mSwitchSize.checked
        }
    }

    Text {
        id: mTextNumber
        //text: vNumberFound
        text: Core.DisplayNum
        font.pixelSize: main.mFontSize
        
        rightPadding: 30

        anchors.right:  mTextTimer.left
        anchors.top:    parent.top
        anchors.bottom: mScrollView1.top

        horizontalAlignment: Text.AlignRight
        verticalAlignment:   Text.AlignVCenter 
    }

    Text {
        id: mTextTimer

        text: vDisplayTimer; 
        font.pixelSize: main.mFontSize
        
        rightPadding: 30

        anchors.right:  parent.right
        anchors.top:    parent.top
        anchors.bottom: mScrollView1.top
        
        horizontalAlignment: Text.AlignRight
        verticalAlignment :  Text.AlignVCenter 
    }

    ScrollView {    
        //focus: true
        id : mScrollView1

        anchors.top:    mButtonExecute.bottom
        anchors.bottom: parent.bottom
        anchors.left:   parent.left
        width:          parent.width

        TextArea  {
            id : mTextArea1
            placeholderText:qsTr("Paste Your Numbers Here")
            text: "3766581235885941622054540050228447514162777869412307699482907769113268717216818322831603491835999456015306915009196661427591452909871214219792485776087253286386945942663949956280302377388971714236415605168862773550156548824873689737766284562457836197902674997734737908387650371844408009421100914050765521827781655182806129058522352838472989652688571683680665438395803243794489830567998343203397981373552644309879795957322883020671901669290704497751685870539575543632177623725028726840870016429503564354896057020404025619555440159796686935523081354355119387766201895202371147907112778884969266539280935452003712638970422340890791962244529017494651550289995762505866212386393472458374741386036991340760970327022447106502711257671708182087831698677130077927731626466195021513131952322762659409302452718743061757527857578831917621650745174966732316231446870605534431568974878576006012026939455247174486040603096495646182217557200423380237313587369836078574982810508277521659834594761360129982400036745363"
            font.pixelSize: main.width / 40
            color:          "#000000"
            wrapMode:       TextEdit.Wrap

            //anchors.fill: parent
            verticalAlignment: TextInput.AlignTop

            selectByMouse: true
            palette {
                highlight:      "#ffbb00"
                highlightedText:"#000000"
            }

            background: Item {
                Image {
                    id: backdrop
                    source:  "qrc:///resource/pictures/backdrop.jpg" 
                }

                FastBlur {
                    anchors.fill: backdrop
                    source: backdrop
                    radius: 32
                }
            }
        }
    }

    Connections {
        target: Core

        onSigGenerate: {
            mTextArea1.text = Action.GetRandomNumbers()
            Core.AllNumbers = mTextArea1.text;
        }
        onSigHighlightNumberSequence: {
            if (mSwitchSize.checked)
                mTextArea1.select(location, location + 8);
            else
                mTextArea1.select(location, location + 4);
        }
        onSigDisplayNumberFound: {
            //mTextNumber.text = Core.DisplayNum
        }
    }
}


