# 
# Interface de controle BatPod

import sys
import select
import tty
import termios
import bluetooth
import time
import  evdev
from Tkinter import *

sock = bluetooth.BluetoothSocket( bluetooth.RFCOMM )

def eventInfo(eventName, char, keysym, ctrl, shift):
    msg = "[" + char + "] " 
    if char == "8":
        msg += "Avancer Droit"
        sock.send('8')
        time.sleep(0.5);
    elif char == "2":
        msg += "Reculer Droit"
        sock.send('2')
        time.sleep(0.5);
    elif char == "7":
        msg += "Tourner Gauche"
        sock.send('7')
        time.sleep(0.5);
    elif char == "9":
        msg += "Tourner Droite"
        sock.send('9')
        time.sleep(0.5);
    elif char == "1":
        msg += "Reculer Gauche"
        sock.send('1')
        time.sleep(0.5);
    elif char == "3":
        msg += "Reculer Droit"
        sock.send('3')
        time.sleep(0.5);
    elif char == "5":
        msg += "Stop"
        sock.send('5')
        time.sleep(0.5);

    elif char == "0":
        msg += "Stand"
        sock.send('0')
        time.sleep(0.5);

    elif char == "a":
        msg += "Speed +"
        sock.send('a')
        time.sleep(0.5);
    elif char == "q":
        msg += "Speed -"
        sock.send('q')
        time.sleep(0.5);

    elif char == "z":
        msg += "Claw open"
        sock.send('z')
        time.sleep(0.5);
    elif char == "s":
        msg += "Claw close"
        sock.send('s')
        time.sleep(0.5);

    elif char == "e":
        msg += "Arm Right 1 +"
        sock.send('e')
        time.sleep(0.5);
    elif char == "d":
        msg += "Arm Right 1 -"
        sock.send('d')
        time.sleep(0.5);


    elif char == "r":
        msg += "Arm Right 2 +"
        sock.send('r')
        time.sleep(0.5);
    elif char == "f":
        msg += "Arm Right 2 -"
        sock.send('f')
        time.sleep(0.5);

    elif char == "t":
        msg += "Arm Right 3 +"
        sock.send('t')
        time.sleep(0.5);
    elif char == "g":
        msg += "Arm Right 3 -"
        sock.send('g')
        time.sleep(0.5);



    else:
        msg += ""   

    return msg

def ignoreKey(event):
    ignoreSyms = [ "Shift_L", "Shift_R", "Control_L", "Control_R", "Caps_Lock" ]
    return (event.keysym in ignoreSyms)
    
def keyPressed(event):
    canvas = event.widget.canvas
    ctrl  = ((event.state & 0x0004) != 0)
    shift = ((event.state & 0x0001) != 0)
    if (ignoreKey(event) == False):
        canvas.data["info"] = eventInfo("keyPressed", event.char, event.keysym, ctrl, shift)
    if ((len(event.keysym) == 1) and (event.keysym.isalpha())):
        if (event.keysym not in canvas.data["pressedLetters"]):
            canvas.data["pressedLetters"].append(event.keysym)
    redrawAll(canvas)    


def redrawAll(canvas):
    canvas.delete(ALL)
    font = ("Arial", 16, "bold")
    info = canvas.data["info"]
    canvas.create_text(400, 50, text=info, font=font)

def init(canvas):
    canvas.data["info"] = "Mouvement"
    canvas.data["pressedLetters"] = [ ]
    redrawAll(canvas)

def run():
    # Mettre adresse Bluetooth du BatPod
    bd_addr = "00:18:A1:12:16:C5"
    port = 1
    sock.connect((bd_addr, port))
    
    root = Tk()
    root.title("Controleur BatPod")
    canvas = Canvas(root, width=800, height=200)
    canvas.pack()
    root.canvas = canvas.canvas = canvas
    canvas.data = { }
    init(canvas)
    root.bind("<KeyPress>", keyPressed)
    root.mainloop()

run()
