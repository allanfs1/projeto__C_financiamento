# -*- coding: utf-8 -*-
"""
Created on Tue Dec 25 10:19:22 2018

@author: allan
"""

#from unicurses import *

#from curses import wrapper

import curses
from curses.textpad import Textbox, rectangle
import time



Max = 25
i=0

myscreen = curses.initscr()
myscreen.clear()

def bordas():
    myscreen.border('o','o','+',"+")
    myscreen.refresh()
bordas()
print("\n Arvore de Natal: 24/12/2018\n")
print("\n Feliz Natal !!!\n")
myscreen.getch()

while True:
 time.sleep(1)
 myscreen.clear()
 if i % 2 == 0:
     for i in range(0,Max):
      if i == 0:
        myscreen.addstr( Max*" " + "@"+"\n")

      elif i == Max-1:
        divi=(2*i+1)/2
        myscreen.addstr( int(divi)*" " +"| |"+"\n  Feliz Natal!")
        i = i+1
        myscreen.refresh()

      else:
       myscreen.addstr(" "*(Max-i) + "@" *(2*i+1)+"\n")


 else:
    for i in range(0,Max):
     if i == 0:
       myscreen.addstr( Max*" " + "*"+"\n")

     elif i == Max-1:
       divi=(2*i+1)/2
       myscreen.addstr( int(divi)*" " +"| |" + "\nFeliz Natal!")
       #i = i-1
       myscreen.refresh()

     else:
      myscreen.addstr(" "*(Max-i) + "*" *(2*i+1)+"\n")




#myscreen.addstr(12, 25,"{0} :{1}".format("Natal","Arvore"),curses.A_DIM)


#A_BLINK
#A_BOLD
#A_DIM
#A_REVERSE
#A_STANDOUT
#A_UNDERLINE
#curses.endwin()
