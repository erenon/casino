var
EventReceiver = function(er) {
var subscriptions = [];
    
    er = er || {};
    
    er.on = function(event, callback) {
        if (!subscriptions[event]) {
            subscriptions[event] = [];
        }
        
        subscriptions[event].push(callback);
    };
    
    er.notify = function(event, data) {
        var sub;
        
        if (subscriptions[event]) {
            for (sub = subscriptions[event].length - 1; sub >= 0; sub--){
                subscriptions[event][sub](data);
            }
        }
    } 
}
;

module.exports = EventReceiver;