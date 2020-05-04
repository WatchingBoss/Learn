import PySimpleGUI as gui
import os


def get_text_from_file(file_path):
    with open(file_path) as file:
        text = file.read()

    return text


def first_window(theme, title):
    gui.theme(theme)

    layout = [
        [gui.Text("Enter number", text_color="lightgreen"), gui.InputText()],
        [gui.Text("Enter exponent", text_color="cyan"), gui.InputText()],
        [gui.Text("For text"), gui.Output(size=(100, 20))],
        [gui.Input(), gui.FileBrowse("Browse your file")],
        [gui.Button("Calc"), gui.Button("Popup"), gui.Button("Exit")],
        [gui.Button("Open file")]
    ]

    window = gui.Window(title, layout)

    while True:
        event, values = window.read()
        if event in (None, "Exit"):
            break
        elif event in (None, "Calc"):
            print("{:.0f}".format(float(values[0]) ** float(values[1])))
        elif event in (None, "Popup"):
            gui.Popup(os.getcwd())
        elif event in (None, "Open file"):
            print("{}".format(get_text_from_file(values[2])))

    window.close()


if __name__ == "__main__":
    first_window("DarkAmber", "First window")
