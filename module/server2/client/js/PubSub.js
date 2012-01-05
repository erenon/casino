// Original code is written by Morgan Roderick http://roderick.dk

/**
 * options:
 *  - socket: Socket.IO object (optional)
 */
var
PubSub = function(options) {
    "use strict";
    
var options = options || {},
    socket = options.socket || false,
    events = {},
    lastUid = -1,
    
    publish = function(event, data, sync){
        // if there are no subscribers to this event, just return here
        if (!events.hasOwnProperty(event)){
            return false;
        }
        
        var emitEvent = function(){
            var subscribers = events[event];
            var throwException = function(e){
                return function(){
                    throw e;
                };
            }; 
            for (var i = 0, j = subscribers.length; i < j; i++){
                try {
                    subscribers[i].func(data);
                } catch( e ){
                    setTimeout(throwException(e), 0);
                }
            }
        };
        
        if (sync === true){
            emitEvent();
        } else {
            setTimeout(emitEvent, 0);
        }
        return true;
    }
    ;

    return {
        version: '0.2-erenon',
        
        /**
         *  PubSub.publish(event[, data]) -> Boolean
         *  - event (String): The event to publish
         *  - data: The data to pass to subscribers
         *  Publishes the the event, passing the data to it's subscribers
        **/
        publish: function(event, data) {
            return publish(event, data, false);
        },
        
        /**
         *  PubSub.publishSync(event[, data]) -> Boolean
         *  - event (String): The event to publish
         *  - data: The data to pass to subscribers
         *  Publishes the the event synchronously, passing the data to it's subscribers
        **/
        publishSync: function(event, data) {
            return publish(event, data, true);
        },
        
        /**
         *  PubSub.subscribe(event, func) -> String
         *  - event (String): The event to subscribe to
         *  - func (Function): The function to call when a new event is published
         *  Subscribes the passed function to the passed event. 
         * Every returned token is unique and should be stored if you need to unsubscribe
        **/
        subscribe: function(event, func) {
            // event is not registered yet
            if (!events.hasOwnProperty(event) ){
                events[event] = [];
                
                // subscribe to socket.io events
                if (socket) {
                    socket.on(event, function(data) {
                        publish(event, data, true);
                    });
                }
            }
            
            // forcing token as String, to allow for future expansions without breaking usage
            // and allow for easy use as key names for the 'events' object
            var token = (++lastUid).toString();
            events[event].push( { token: token, func: func } );
            
            // return token for unsubscribing
            return token;
        },
        
        /**
         *  PubSub.unsubscribe(token) -> String | Boolean
         *  - token (String): The token of the function to unsubscribe
         *  Unsubscribes a specific subscriber from a specific event using the unique token
        **/
        unsubscribe: function(token){
            for (var e in events){
                if (events.hasOwnProperty(e)){
                    for (var i = 0, j = events[e].length; i < j; i++){
                        if (events[e][i].token === token){
                            events[e].splice( i, 1 );
                            return token;
                        }
                    }
                }
            }
            return false;
        }                
    };
};