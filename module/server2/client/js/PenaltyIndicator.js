/**
 * options:
 *  - pubsub: PubSub object
 *  - $: jQuery
 *  - target: DOM element to write into
 */

var
PenaltyIndicator = function(options) {
var $ = options.$ || $,
    pubsub = options.pubsub,
    target = options.target,
    
    currentPenalty = 0
    ;
    
    pubsub.on('card_played', function(data) {
        var value = data.played_card.value,
            addition = 0;
            ;
            
        if (value == '+2') {
            addition = 2;
        } else if (value == '+4') {
            addition = 4;
        }
        
        if (addition > 0) {
            currentPenalty += addition;
            target.text(currentPenalty);
        }
    });
    
    pubsub.on('draw_card', function() {
        currentPenalty = 0;
        target.text('');
    });
};
