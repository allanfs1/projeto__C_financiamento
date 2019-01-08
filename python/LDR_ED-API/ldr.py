import serial
import time
from threading import Thread
import io

class Controle(Thread):

  def __init__(self,PORT):

     Thread.__init__(self)

     self.PORT = PORT #porta serial
     self.usb= serial.Serial(self.PORT,9600,timeout=1,bytesize=8,parity='N',stopbits=1,rtscts=1)
     print(f'PORT={self.usb.name} off/on= {self.usb.is_open}')
     self.lum = None



  def tempo(self):
      Tempo = time.localtime()
      return str(Tempo[2]) +":"+ str(Tempo[1]) +":"+ str(Tempo[0]) + "T:"+ str(Tempo[3]) + ":"+str(Tempo[4]) +":"+ str(Tempo[5])

  def readData(self):
      oneByte=0
      buffer = ""
      while True:
        oneByte = self.usb.read(1)
        if oneByte == b'\r':
            return buffer
        else:
            buffer += oneByte.decode("ascii")

      return oneByte

  def leitura_LDR(self,readData):
         self.lum = readData
         return self.lum

  def run (self):
      while True:
        return ("{"+str(self.leitura_LDR(self.readData()))+"}"+"Data:" + str(self.tempo()))

#ldr = Controle('COM3')
#ldr.run()
