import PySimpleGUI as gui


def first_window(theme, title):
    gui.theme(theme)

    layout = [
        [gui.Text("Enter number"), gui.InputText()],
        [gui.Text("Enter exponent"), gui.InputText()],
        [gui.Text("Result"), gui.Output()],
        [gui.Button("Calc"), gui.Button("Exit")]
    ]

    window = gui.Window(title, layout)

    while True:
        event, values = window.read()
        if event in (None, "Exit"):
            break
        elif event in (None, "Calc"):
            print("{:.0f}".format(float(values[0]) ** float(values[1])))

    window.close()


if __name__ == "__main__":
    first_window("DarkAmber", "First window")
