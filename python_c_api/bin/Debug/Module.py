import types

def sayHello():
    print("Hello!\n")
    
def setX(argx):
    global x
    x=argx
    
def printList(argx):
    if type(argx)==list:
        print("Size of List: "+str(len(argx))+"\n")
        for item in argx:
            print(str(item)+"\n")
    else:
        print("Passed argument is not a list")