# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'adminUI.ui'
#
# Created by: PyQt5 UI code generator 5.13.0
#
# WARNING! All changes made in this file will be lost!


from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(800, 523)
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.horizontalLayoutWidget = QtWidgets.QWidget(self.centralwidget)
        self.horizontalLayoutWidget.setGeometry(QtCore.QRect(20, 460, 761, 41))
        self.horizontalLayoutWidget.setObjectName("horizontalLayoutWidget")
        self.horizontalLayout = QtWidgets.QHBoxLayout(self.horizontalLayoutWidget)
        self.horizontalLayout.setContentsMargins(0, 0, 0, 0)
        self.horizontalLayout.setObjectName("horizontalLayout")
        self.adduserButton = QtWidgets.QPushButton(self.horizontalLayoutWidget)
        self.adduserButton.setObjectName("adduserButton")
        self.horizontalLayout.addWidget(self.adduserButton)
        self.deleteuserButton = QtWidgets.QPushButton(self.horizontalLayoutWidget)
        self.deleteuserButton.setObjectName("deleteuserButton")
        self.horizontalLayout.addWidget(self.deleteuserButton)
        self.updateuserButton = QtWidgets.QPushButton(self.horizontalLayoutWidget)
        self.updateuserButton.setObjectName("updateuserButton")
        self.horizontalLayout.addWidget(self.updateuserButton)
        self.selectuserButton = QtWidgets.QPushButton(self.horizontalLayoutWidget)
        self.selectuserButton.setObjectName("selectuserButton")
        self.horizontalLayout.addWidget(self.selectuserButton)
        self.sellerTable = QtWidgets.QTableWidget(self.centralwidget)
        self.sellerTable.setGeometry(QtCore.QRect(20, 111, 761, 181))
        self.sellerTable.setObjectName("sellerTable")
        self.sellerTable.setColumnCount(0)
        self.sellerTable.setRowCount(0)
        self.buyerTable = QtWidgets.QTableWidget(self.centralwidget)
        self.buyerTable.setGeometry(QtCore.QRect(20, 301, 761, 141))
        self.buyerTable.setObjectName("buyerTable")
        self.buyerTable.setColumnCount(0)
        self.buyerTable.setRowCount(0)
        self.label = QtWidgets.QLabel(self.centralwidget)
        self.label.setGeometry(QtCore.QRect(30, 20, 91, 16))
        self.label.setObjectName("label")
        self.adminnolabel = QtWidgets.QLabel(self.centralwidget)
        self.adminnolabel.setGeometry(QtCore.QRect(110, 20, 72, 15))
        self.adminnolabel.setText("")
        self.adminnolabel.setObjectName("adminnolabel")
        self.label_2 = QtWidgets.QLabel(self.centralwidget)
        self.label_2.setGeometry(QtCore.QRect(190, 20, 91, 16))
        self.label_2.setObjectName("label_2")
        self.adminnamelabel = QtWidgets.QLabel(self.centralwidget)
        self.adminnamelabel.setGeometry(QtCore.QRect(270, 20, 72, 15))
        self.adminnamelabel.setText("")
        self.adminnamelabel.setObjectName("adminnamelabel")
        self.label_3 = QtWidgets.QLabel(self.centralwidget)
        self.label_3.setGeometry(QtCore.QRect(360, 20, 81, 16))
        self.label_3.setObjectName("label_3")
        self.adminsexlabel = QtWidgets.QLabel(self.centralwidget)
        self.adminsexlabel.setGeometry(QtCore.QRect(450, 20, 72, 15))
        self.adminsexlabel.setText("")
        self.adminsexlabel.setObjectName("adminsexlabel")
        self.label_5 = QtWidgets.QLabel(self.centralwidget)
        self.label_5.setGeometry(QtCore.QRect(550, 20, 81, 16))
        self.label_5.setObjectName("label_5")
        self.admintellabel = QtWidgets.QLabel(self.centralwidget)
        self.admintellabel.setGeometry(QtCore.QRect(640, 20, 141, 16))
        self.admintellabel.setText("")
        self.admintellabel.setObjectName("admintellabel")
        self.adminnamelabel_2 = QtWidgets.QLabel(self.centralwidget)
        self.adminnamelabel_2.setGeometry(QtCore.QRect(270, 70, 72, 15))
        self.adminnamelabel_2.setText("")
        self.adminnamelabel_2.setObjectName("adminnamelabel_2")
        self.adminsexlabel_2 = QtWidgets.QLabel(self.centralwidget)
        self.adminsexlabel_2.setGeometry(QtCore.QRect(450, 70, 72, 15))
        self.adminsexlabel_2.setText("")
        self.adminsexlabel_2.setObjectName("adminsexlabel_2")
        self.noLine = QtWidgets.QLineEdit(self.centralwidget)
        self.noLine.setGeometry(QtCore.QRect(120, 50, 113, 21))
        self.noLine.setObjectName("noLine")
        self.nameLine = QtWidgets.QLineEdit(self.centralwidget)
        self.nameLine.setGeometry(QtCore.QRect(390, 50, 151, 21))
        self.nameLine.setObjectName("nameLine")
        self.sexLine = QtWidgets.QLineEdit(self.centralwidget)
        self.sexLine.setGeometry(QtCore.QRect(120, 80, 113, 21))
        self.sexLine.setObjectName("sexLine")
        self.telLine = QtWidgets.QLineEdit(self.centralwidget)
        self.telLine.setGeometry(QtCore.QRect(390, 80, 151, 21))
        self.telLine.setObjectName("telLine")
        self.nocheckBox = QtWidgets.QCheckBox(self.centralwidget)
        self.nocheckBox.setGeometry(QtCore.QRect(20, 50, 91, 19))
        self.nocheckBox.setObjectName("nocheckBox")
        self.sexcheckBox = QtWidgets.QCheckBox(self.centralwidget)
        self.sexcheckBox.setGeometry(QtCore.QRect(20, 80, 91, 19))
        self.sexcheckBox.setObjectName("sexcheckBox")
        self.namecheckBox = QtWidgets.QCheckBox(self.centralwidget)
        self.namecheckBox.setGeometry(QtCore.QRect(290, 50, 91, 19))
        self.namecheckBox.setObjectName("namecheckBox")
        self.telcheckBox = QtWidgets.QCheckBox(self.centralwidget)
        self.telcheckBox.setGeometry(QtCore.QRect(290, 80, 91, 19))
        self.telcheckBox.setObjectName("telcheckBox")
        self.buyerradioButton = QtWidgets.QRadioButton(self.centralwidget)
        self.buyerradioButton.setGeometry(QtCore.QRect(590, 50, 115, 19))
        self.buyerradioButton.setObjectName("buyerradioButton")
        self.sellerradioButton = QtWidgets.QRadioButton(self.centralwidget)
        self.sellerradioButton.setGeometry(QtCore.QRect(590, 80, 115, 19))
        self.sellerradioButton.setObjectName("sellerradioButton")
        # MainWindow.setCentralWidget(self.centralwidget)
        self.statusbar = QtWidgets.QStatusBar(MainWindow)
        self.statusbar.setObjectName("statusbar")
        # MainWindow.setStatusBar(self.statusbar)

        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "MainWindow"))
        self.adduserButton.setText(_translate("MainWindow", "添加用户"))
        self.deleteuserButton.setText(_translate("MainWindow", "删除用户"))
        self.updateuserButton.setText(_translate("MainWindow", "修改用户信息"))
        self.selectuserButton.setText(_translate("MainWindow", "查找用户"))
        self.label.setText(_translate("MainWindow", "管理员编号"))
        self.label_2.setText(_translate("MainWindow", "管理员姓名"))
        self.label_3.setText(_translate("MainWindow", "管理员性别"))
        self.label_5.setText(_translate("MainWindow", "管理员电话"))
        self.nocheckBox.setText(_translate("MainWindow", "用户编号"))
        self.sexcheckBox.setText(_translate("MainWindow", "用户性别"))
        self.namecheckBox.setText(_translate("MainWindow", "用户姓名"))
        self.telcheckBox.setText(_translate("MainWindow", "用户电话"))
        self.buyerradioButton.setText(_translate("MainWindow", "买家"))
        self.sellerradioButton.setText(_translate("MainWindow", "卖家"))
