import curses
import time


class Janela:
    def __init__(self):
      self.Tempo = time.localtime()
      self.screen = curses.initscr()

    def windows(self,height,width,y,x):
        soft = ''' \n Python 3.7\n Data:{0}:{1}:{2}\n Sistema:Windows-10
 Data-Develop:27/12/2018 '''.format(self.Tempo[2],self.Tempo[1],self.Tempo[0])
        self.screen.addstr(8,1,f"\n\n\n\n\n\n\n Dados do Programa:\n{soft}")
        st= self.screen.subwin(height,width,y,x)
        st.box()
        self.screen.refresh()
        #self.screen.getch()



#wd = Janela()
#wd.windows(15,30,12,0)
