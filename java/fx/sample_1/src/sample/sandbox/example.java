package sample.sandbox;

import sample.event.Dispatcher;
import sample.event.Event;
import sample.event.types.MouseMotionEvent;
import sample.event.types.MousePressedEvent;
import sample.event.types.MouseReleasedEvent;
import sample.layers.Layer;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.Point;
import java.awt.Rectangle;
import java.util.Random;

public class example extends Layer {
    private String name;
    private Color color;
    private Rectangle rect;
    private boolean dragging;
    private double px, py;

    private static final Random rand = new Random();

    public example(String name, Color color){
        this.name = name;
        this.color = color;

        this.dragging = false;

        rect = new Rectangle(rand.nextInt(100) + 100, rand.nextInt(100) + 100,
                250, 100);
    }

    @Override
    public void onEvent(Event event){
        Dispatcher dispatcher = new Dispatcher(event);
        dispatcher.Dispatch(Event.Type.MOUSE_PRESSED, (Event e) -> onPressed((MousePressedEvent) e));
        dispatcher.Dispatch(Event.Type.MOUSE_RELEASED, (Event e) -> onReleased((MouseReleasedEvent) e));
        dispatcher.Dispatch(Event.Type.MOUSE_MOVED, (Event e) -> onMoved((MouseMotionEvent) e));
    }

    @Override
    public void onRender(Graphics g){
        g.setColor(color);
        g.fillRect(rect.x, rect.y, rect.width, rect.height);

        g.setColor(Color.WHITE);
        g.drawString(name, rect.x = 5, rect.y + 30);
    }

    private boolean onPressed(MousePressedEvent e){
        if(rect.contains(new Point(e.getX(), e.getY())))
            this.dragging = true;
        return this.dragging;
    }

    private boolean onReleased(MouseReleasedEvent e){
        this.dragging = false;
        return false;
    }

    private boolean onMoved(MouseMotionEvent e){
        if(this.dragging){
            rect.x += e.getX() - px;
            rect.y += e.getY() - py;
        }
        px = e.getX();
        py = e.getY();

        return this.dragging;
    }
}
