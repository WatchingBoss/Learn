package sample.event.types;

import sample.event.Event;

public class MouseButtonEvent extends Event {
    private int keyCode, x, y;

    public MouseButtonEvent(Type type, int keyCode, int x, int y) {
        super(type);
        this.keyCode = keyCode;
        this.x = x;
        this.y = y;
    }

    public int getKeyCode() {
        return keyCode;
    }

    public int getX() {
        return x;
    }

    public int getY() {
        return y;
    }
}
