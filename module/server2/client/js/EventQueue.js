
var
EventQueue = function() {
var events = [],
    running = false,
    run = function() {
        var eventCallback;

        running = false;
        
        if (events.length > 0) {
            eventCallback = events.shift();
            running = true;
            eventCallback(run);
        }
    }
    ;
    
    return {
        add: function(eventCallback) {
            events.push(eventCallback);
            
            if (events.length == 1 && !running) {
                run();
            }
        }
    };
};
