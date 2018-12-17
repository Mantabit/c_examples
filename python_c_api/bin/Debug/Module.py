import matplotlib.pyplot as plt
import numpy as np

def sayHello():
    print("Hello!\n")
    
def setX(argx):
    global x
    x=argx
    
def plotFunction(argx,argy):
    if type(argx)==list or type(argx)==np.ndarray and type(argy)==list or type(argy)==np.ndarray:
        plt.plot(argx,argy)
        plt.grid()
        plt.show()
    else:
        print("Not all arguments passed are lists. Call failed.")
        
xs=np.linspace(0,2*np.pi,100)
ys=np.sin(xs)