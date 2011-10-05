var
EventQueue = function() {
var that = this,
    events = [],
    locked = false
    ;
    
    this.add = function(eventCallback /*, and callback arguments*/) {
        events.push({
            callback: eventCallback,
            arguments: Array.prototype.slice.call(arguments, 1)
        });
    
        if (!locked) {
            // only the current event is there
            // start event loop
            this.run();
        }
    };
    
    this.addFront = function(eventCallback /*, and callback arguments*/) {
        events.unshift({
            callback: eventCallback,
            arguments: Array.prototype.slice.call(arguments, 1)
        });
    
        if (!locked) {
            // only the current event is there
            // start event loop
            this.run();
        }
    };

    this.run = function() {
        var event,
            arguments;
            
        locked = false;
        
        if (events.length > 0) {
            locked = true;
            
            event = events.shift();
            
            arguments = event.arguments || new Array();
            arguments.push(that.run);
            
            event.callback.apply(this, arguments);
        }
    };
    
    this.lock = function() {
        locked = true;
    };
};