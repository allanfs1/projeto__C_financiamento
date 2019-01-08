import serial
from threading import Thread
import time



class controle(Thread):

     def __init__(self,COM,Blodrater):
      Thread.__init__(self)
      self.PortCOM = COM
      self.usb= serial.Serial(self.PortCOM ,Blodrater,timeout=1,bytesize=8,parity='N',stopbits=1,rtscts=1)
      self.lista = []

     def usb_name(self):
        return self.usb.name

     def usb_open(self):
        return self.usb.is_open


     def obter(self):
      oneByte=0
      buffer = ""
      while True:
        oneByte = self.usb.read(1)
        if oneByte == b'\r':
         return buffer

        else:
         buffer += oneByte.decode("ascii")

      return oneByte

     def run(self,obter):
       self.lista = obter
       return self.lista

     def rodar (self):
      while True:
       #return print(str(self.obter()))
       return self.obter()


#app = controle('COM3',57600)
#app.usb_name()
#app.usb_open()
#print(app.rodar())
