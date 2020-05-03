import PySimpleGUI as gui
import sdl2

gui.theme('DarkAmber')   # Add a touch of color

# All the stuff inside your window.
layout = [
    [gui.Text('Some text on Row 1')],
    [gui.Text('Enter something on Row 2'), gui.InputText()],
    [gui.Button('Ok'), gui.Button('Cancel')]
]

# Create the Window
window = gui.Window('Window Title', layout)

# Event Loop to process "events" and get the "values" of the inputs
while True:
    event, values = window.read()
    if event in (None, 'Cancel'):   # if user closes window or clicks cancel
        break
    print('You entered ', values[0])

window.close()