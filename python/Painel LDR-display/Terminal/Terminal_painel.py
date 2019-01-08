import serial
import curses
from curses.textpad import Textbox, rectangle
from quadro import Janela
import time
from dados import controle as USB
usb = USB('COM3',57600)


x = 20; y = 7
height = 5; width = 40
ldr = 50.0
cusorY = 0
cusorX = 0
delay = 1

prog = ''' Programa, para controle de dados e visualisação de recursos
  que são transmitido via porta COM...'''


''' Iniciar o Terminal'''
screen = curses.initscr()
curses.echo()
curses.cbreak()
screen.keypad(True)

curses.start_color()
curses.init_pair(1,curses.COLOR_WHITE,curses.COLOR_BLACK)
curses.init_pair(2,curses.COLOR_YELLOW,curses.COLOR_BLACK)
curses.init_pair(3,curses.COLOR_RED,curses.COLOR_BLACK)
curses.init_pair(4,curses.COLOR_BLUE,curses.COLOR_BLACK)

padra_1 = 1
padra_2 = 2
padra_3 = 3
padra_4 = 4


Normal_texto = curses.A_NORMAL
def screen_f():
 wd = Janela()
 while True:
    wd.windows(15,30,12,0)
    screen.addstr(1,1,"Usuario:")
    screen.refresh()
    user = screen.getstr(1,10, 10)
    aux = user

    if user == b'Allan':
     cusorY = 9
     cusorX = 10
     screen.border()
     screen.addstr(1,1,prog,curses.COLOR_GREEN)
     screen.refresh()
     time.sleep(delay)

     screen.clear()
     screen.border()
     screen.addstr(1,2,"Painel de Controle",curses.A_UNDERLINE)
     screen.addstr(3,2,"Porta:{0} \n  OFF/ON {1}".format(usb.usb_name(),usb.usb_open()))
     screen.addstr(6,2,"Painel de Cadastro",curses.A_UNDERLINE)
     screen.addstr(5,2," "+(((5*11) *2) + 5)*" ",curses.A_UNDERLINE)
     screen.addstr(8,2,"Login:\n" + "  Usuario: " + str(aux) + "\n  Senha:" + "\n", curses.color_pair(1))
     screen.hline(20,1,curses.ACS_HLINE,118)
     senha_us()


    else:
     screen.clear()
     curses.beep()

def senha_us():
 while True:
    screen.refresh()
    try:
     c = screen.getstr(10,8, 10)
     if c == b'zirdof989':
       tmp = padra_4
       screen.addstr("\n  Senha correta \n\n  Precione S/N",curses.color_pair(tmp))
       s = screen.getch()
       if s == ord('N') or s == ord('n'):
        screen.clear()
        time.sleep(delay+1)
        break

       elif s == ord('S') or s == ord('s'):
        #curses.flash()
        screen.clear()
        height= 15
        width= 70
        Painel(0,0,height,width)



     else :
        tmp = padra_3
        screen.addstr(10,15,"Senha Incorreto", curses.color_pair(tmp))
        screen.refresh()
        time.sleep(delay+1)
        screen.clear()
        break

    except:
        pass


def Painel(y,x,height,width):
    screen.addstr(1, 25," \n  Painel de Dados:\n\n\n  Lux:(S) \n  Graus:(N) \n")
    rectangle(screen, y,x, 1+height+1, 1+width+1)
    rectangle(screen, y,x, 1+height+1, 1+width+1)
    screen.addstr(7,25,"\n  Taxa de Lux minima:{0}\n".format(ldr),curses.color_pair(padra_2))
    screen.refresh()

    while True:
     screen.addstr(9,20,"{0}".format(usb.rodar()),curses.color_pair(padra_2))
     screen.refresh()
     #Fim do Programa
    # Let the user edit until Ctrl-G is struck.

'''
 try:
  while True:
     screen.refresh()
     c =  screen.getch()
     height,width = screen.getmaxyx()
     screen.addstr(cusorY,cusorX,"*")

     if c == ord('N'):
         curses.beep()
         break
     elif c == curses.KEY_DOWN:
         cusorY  = cusorY +1
     elif c == curses.KEY_UP:
         cusorY  = cusorY -1
     elif c == curses.KEY_RIGHT:
        cusorX  = cusorX + 1
     elif c == curses.KEY_LEFT:
        cusorX  = cusorX - 1

     cusorX = max(0,cusorX )
     cusorX = min(width-1,cusorX )

     cusorY = max(0,cusorY )
     cusorY  = min(height-1,cusorY)


 finally:
  curses.nobreak()
  screen.keypad(0)
'''


def main ():
 screen_f()
 usb.setDaemon(True)
 usb.start()

try:
 curses.wrapper(main())
except:
 pass
