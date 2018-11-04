package sample.core;

import sample.event.Event;
import sample.event.types.MouseMotionEvent;
import sample.event.types.MousePressedEvent;
import sample.event.types.MouseReleasedEvent;
import sample.layers.Layer;

import javax.swing.JFrame;
import java.awt.Canvas;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.EventQueue;
import java.awt.Graphics;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.MouseMotionListener;
import java.awt.image.BufferStrategy;

import java.util.ArrayList;
import java.util.List;

@SuppressWarnings("serial")
public class Window extends Canvas {
    private BufferStrategy bs;
    private List<Layer> layerList = new ArrayList<>();

    public Window(String name, int width, int height){
        setPreferredSize(new Dimension(width, height));
        Init(name);

        addMouseListener(new MouseAdapter(){
            @Override
            public void mousePressed(MouseEvent e){
                MousePressedEvent event = new MousePressedEvent(e.getButton(), e.getX(), e.getY());
                onEvent(event);
            }

            @Override
            public void mouseReleased(MouseEvent e){
                MouseReleasedEvent event = new MouseReleasedEvent(e.getButton(), e.getX(), e.getY());
                onEvent(event);
            }
        });

        addMouseMotionListener(new MouseMotionListener() {
            @Override
            public void mouseDragged(MouseEvent e) {
                MouseMotionEvent event = new MouseMotionEvent(e.getX(), e.getY(), false);
                onEvent(event);
            }

            @Override
            public void mouseMoved(MouseEvent e) {
                MouseMotionEvent event = new MouseMotionEvent(e.getX(), e.getY(), true);
                onEvent(event);
            }
        });

        Render();
    }

    private void Init(String name){
        JFrame frame = new JFrame(name);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.add(this);
        frame.pack();
        frame.setLocationRelativeTo(null);
        frame.setResizable(false);
        frame.setVisible(true);
    }

    private void Render(){
        if(bs == null)
            createBufferStrategy(3);
        bs = getBufferStrategy();

        Graphics graphics = bs.getDrawGraphics();
        graphics.setColor(Color.WHITE);
        graphics.fillRect(0, 0, getWidth(), getHeight());
        onRender(graphics);
        graphics.dispose();
        bs.show();

        try {
            Thread.sleep(3);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        EventQueue.invokeLater(() -> Render());
    }

    private void onRender(Graphics graphics){
        for(int i = 0; i < layerList.size(); ++i)
            layerList.get(i).onRender(graphics);
    }

    private void onEvent(Event event){
        for(int i = layerList.size() - 1; i >= 0; --i)
            layerList.get(i).onEvent(event);
    }

    public void addLayer(Layer layer){
        layerList.add(layer);
    }

}
