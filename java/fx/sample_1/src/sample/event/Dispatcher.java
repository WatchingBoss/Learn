package sample.event;

public class Dispatcher {
    private Event event;

    public Dispatcher(Event event) {
        this.event = event;
    }

    public void Dispatch(Event.Type type, EventHandler handler){
        if(event.handled)
            return;

        if(event.getType() == type)
            event.handled = handler.handle(event);
    }
}
