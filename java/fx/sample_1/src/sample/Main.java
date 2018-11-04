package sample;

import sample.core.Window;
import sample.sandbox.example;

import java.awt.Color;

public class Main {
    public static void main(String[] args){
        Window window = new Window("Sample", 640, 480);
        window.addLayer(new example("First rectangle", Color.BLUE));
        window.addLayer(new example("Second rectangle", Color.RED));
    }
}
