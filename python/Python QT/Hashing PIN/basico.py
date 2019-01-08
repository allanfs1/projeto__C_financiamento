from PyQt5 import QtCore,QtWidgets
from PyQt5.QtWidgets import QMainWindow,QWidget,QPushButton,QLabel,QLineEdit
from PyQt5.QtCore import QSize
import sys
from hashing import Controle as hashing

m=5

class janela(QMainWindow):
 def __init__(self):

   self.hash= hashing(m)


   QMainWindow.__init__(self)
   self.setMinimumSize(QSize(320,180))
   self.setWindowTitle("Key-Hashing")

   self.nameLabel = QLabel(self)
   self.nameLabel.setText("PIN")
   self.userLabel = QLabel(self)
   self.line_user = QLineEdit(self)

   self.line = QLineEdit(self)
   self.nameLabel.move(20,20)
   self.line.move(80,20)
   self.line.resize(200,32)

   btn = QPushButton('Ok',self)
   btn.clicked.connect(self.clicke)
   btn.resize(200,32)
   btn.move(80,60)
   self.caixa()

 def decoder(self,local):
     nome = None
     if local is 0:
         nome = "Allan"
     elif local is 1:
         nome = "Eduardo"
     elif local is 2:
         nome = "Elho"
     elif local is 3:
         nome = "Segato"
     return nome

 def clicke(self):
   aux = int(self.line.text())
   self.hash.main(aux)
   local = self.hash.pos(aux)
   return self.line_user.setText("ID:"+str(local) +" "+"Nome:"+ self.decoder(local))


 def clicke_senha(self):
   self.hash.moatra_hashi()#Mostra Tabela
   return self.line_user.setText(" ")


 def caixa(self):
   self.userLabel.setText("Usuario:")
   self.userLabel.move(20,98)
   self.line_user.move(80,98)
   self.line_user.resize(200,32)

   btn2 = QPushButton('Clear',self)
   btn2.clicked.connect(self.clicke_senha)
   btn2.resize(200,32)
   btn2.move(80,136)

if __name__ == "__main__":
    app = QtWidgets.QApplication(sys.argv)
    mainWin =  janela()
    mainWin.show()
    sys.exit(app.exec())
