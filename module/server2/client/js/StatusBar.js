/**
 * options:
 *  - pubsub: PubSub object
 *  - $: jQuery
 *  - target: DOM element to write into
 *  - _: i18n module
 * 
 * TODO subscribe to all statusbar related events
 */

var 
StatusBar = function(options) {
var pubsub = options.pubsub,
    $ = options.$,
    target = options.target,
    _ = options._,
    list,
    displayItem = function(text) {
        var item = $('<li/>').text(text);
        list.append(item);
        setTimeout(function() {
            item.remove();
        }, 3000);
    } 
    ;
    
    list = $('<ul/>');
    target.append(list);
    
    pubsub.subscribe('invalid_move', function(data) {
        displayItem(_(data.message));
    });
};