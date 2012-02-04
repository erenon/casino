
var
Control = function(options, control) {
    
},

DrawButton = function(options, control) {
var validator = options.validator,
    socket = options.socket,
    target = options.target,
    pubsub = options.pubsub
    ;
    
    target.click(function() {
        var msg = validator.isDrawValid();
        if (msg === true) {
            socket.emit('drawCard');
        } else {
            pubsub.emit('invalid_move', {message: msg});
        }
    });
    
    control = control || {};
    Control(options, control);
},

UnoButton = function(options, control) {
var validator = options.validator,
    socket = options.socket,
    target = options.target
    ;
    
    target.click(function() {
        socket.emit('sayUno');
        target.addClass('buttonPressed');
        setTimeout(function() {
            target.removeClass('buttonPressed');            
        }, 3000);        
    });    

    control = control || {};
    Control(options, control);    
}
;