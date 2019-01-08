#-*-coding:utf8;-*-
#qpy:3
#qpy:console

print("This is console module")


m=5
cont=0
livre ='L'
lista = [None for i in range(m)]

def hashing(x):
  return x % m

def main():
 global cont
 
 while True:
   if lista is not None:
    numero = int(input("Insira um numero:"))
    cont+=1
    if cont < m:
     pos=hashing(numero)
     lista[pos] = numero
     print("Contador:",cont)
    else:
       print("Hashi Cheia")
       break
          
    
def imprima():
    print("lista hashing:{0} e Tamanho:{1}".format(lista,len(lista)))
    
def moatra_hashi():
    if lista is not None:
     for i in range(m):
      if i < m:
        print(lista[i])
    else:
       print("N Elementos Maximo")
       
      
  
main()
#imprima()
moatra_hashi()




