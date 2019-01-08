#-*-coding:utf8;-*-
#qpy:3
#qpy:console
import os

cont=0
livre ='L'

class Controle:
 def __init__(self,m):
  self.m = m
  self.lista = [None for i in range(self.m)]
  print("Iniciar Hashing")

 def hashing(self,x):
  return x % self.m

 def main(self,n):
  global cont
  while True:
   if self.lista is not None:
    numero = int(n)#Insira o valor
    cont+=1
    if cont < self.m:
     pos=self.hashing(numero)
     self.lista[pos] = numero
     return  self.lista[pos]

    else:
       print("Hashi Cheia")
       cls = os.system('cls')
       break

 def pos(self,numero):
     pos=self.hashing(numero)
     return pos

 def imprima(self):
    print("lista hashing:{0} e Tamanho:{1}".format(self.lista,len(self.lista)))

 def moatra_hashi(self):
    if self.lista is not None:
     for i in range(self.m):
      print(self.lista[i])

'''
m = 5
hash = Controle(m)
hash.main(15)
hash.moatra_hashi()
'''
