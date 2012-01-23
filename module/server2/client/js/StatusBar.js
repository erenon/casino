/**
 * options:
 *  - $: jQuery object
 *  - pubsub: PubSub object
 *  - target: DOM element to write into
 *  - _: i18n module | TODO out of use
 * 
 * TODO subscribe to all statusbar related events
 * TODO use changeGameSpeed
 */

var 
StatusBar = function(options) {
var $ = options.$,
    pubsub = options.pubsub,
    target = options.target,
    //_ = options._,
    setMargin = function() {
        target.css('margin-bottom', target.outerHeight() * -1);    
    },
    displayItem = function(text) {
        var item = $('<li/>').text(text);
        
        target.append(item);
        setMargin();
        
        target.show();
        
        setTimeout(function() {
            item.remove();
            if (target.children().length == 0) {
                target.hide();
            } else {
                setMargin();
            }
        }, 3000);
    } 
    ;
    
    target.hide();
    
    pubsub.on('invalid_move', function(data) {
        //displayItem(_(data.message));
        displayItem(data.message);
    });
};