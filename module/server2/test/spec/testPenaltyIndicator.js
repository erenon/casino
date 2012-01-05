describe('PenaltyIndicator', function() {
var target = $('<div/>').first(),
    pubsub = PubSub(),
    pi = PenaltyIndicator({
        pubsub: pubsub,
        target: target,
        $: $
    });

    it("displays 2 on +2", function() {
        pubsub.emitSync('card_played', {
            played_card: {
                value: '+2'
            }
        });
        
        expect(target.text()).toEqual('2');
    });
    
    it("increments from 2 to 6", function() {
        pubsub.emitSync('card_played', {
            played_card: {
                value: '+4'
            }
        });
        
        expect(target.text()).toEqual('6');            
    });
    
    it("resets to 0", function() {
        pubsub.emitSync('draw_card');
        expect(target.text()).toEqual('');            
    });
});
