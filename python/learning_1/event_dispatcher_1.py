# Tutorial:
# https://expobrain.net/2010/07/31/simple-event-dispatcher-in-python/

class Event(object):
    def __init__(self, event_type, data=None):
        self._type = event_type
        self._data = data

    @property
    def type(self):
        return self._type

    @property
    def data(self):
        return self._data


class EventDispatcher(object):
    def __init__(self):
        self._events = {} # key: 'event_type', value: 'listeners'

    def __del__(self):
        self._events = None

    def has_listener(self, event_type, listener) -> bool:
        if event_type in self._events.keys():
            return listener in self._events[event_type]
        else:
            return False

    def dispatch_event(self, event: Event):
        if event.type in self._events.keys():
            listeners = self._events[event.type]

            for listener in listeners:
                listener(event)

    def add_event_listener(self, event_type, listener):
        if not self.has_listener(event_type, listener):
            listeners = self._events.get(event_type, [])
            listeners.append(listener)
            self._events[event_type] = listeners

    def remove_event_listeners(self, event_type, listener):
        if self.has_listener(event_type, listener):
            listeners = self._events[event_type]

            if len(listeners):
                del self._events[event_type]
            else:
                listeners.remove(listener)
                self._events[event_type] = listeners


class MyEvent(Event):
    ASK = 'askMyEvent'
    RESPOND = 'respondMyEvent'


class WhoAsk(object):
    def __init__(self, event_dispatcher: EventDispatcher):
        self.dispatcher = event_dispatcher
        self.dispatcher.add_event_listener(MyEvent.RESPOND, self.on_answer_event)

    def ask(self):
        print(f"I am instance {self}. Who is listening to me?")
        self.dispatcher.dispatch_event(
            MyEvent(MyEvent.ASK, self)
        )

    def on_answer_event(self, event):
        print(f"Thank you instance {event.data}")


class WhoRespond(object):
    def __init__(self, event_dispatcher: EventDispatcher):
        self.dispatcher = event_dispatcher
        self.dispatcher.add_event_listener(MyEvent.ASK, self.on_ask_event)

    def on_ask_event(self, event):
        print(f"\nThis is instance {self}. Hello {event.data}")
        self.dispatcher.dispatch_event(
            MyEvent(MyEvent.RESPOND, self)
        )


dispatcher = EventDispatcher()

who_ask = WhoAsk(dispatcher)
who_respond_1 = WhoRespond(dispatcher)
who_respond_2 = WhoRespond(dispatcher)

who_ask.ask()



