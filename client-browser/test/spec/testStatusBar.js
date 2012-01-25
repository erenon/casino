describe('StatusBar', function() {
var target = $('<div/>'),
    i18n_spy = jasmine.createSpy().andCallFake(function(text) {
        return text + '_translated';
    }),
    pubsub = PubSub(),
    sb = StatusBar({
        pubsub: pubsub,
        $: $,
        target: target,
        _: i18n_spy
    })
    ;
    
    it('displays message', function() {
        var message = 'invalid_move_message',
            found = false;
            
        pubsub.emitSync('invalid_move', {
            message: message
        });
        
        target.find('li').each(function(index, item){
            if ($(item).text() === message+'_translated') {
                found = true;
            }
        });
        
        expect(found).toBeTruthy();
    });
    
    it('uses i18n', function() {
        pubsub.emitSync('invalid_move', {
            message: 'message'
        });
        
        expect(i18n_spy).toHaveBeenCalledWith('message');
    });
});
