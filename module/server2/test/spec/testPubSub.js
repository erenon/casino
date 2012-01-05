describe('PubSub', function() {
    it('registers event on the passed in socket', function() {
        var socketSpy = { 
                on: jasmine.createSpy() 
            },
            pubsub = PubSub({socket: socketSpy});
        
        pubsub.on('foo', function() {});
        pubsub.on('foo', function() {});
        pubsub.on('foo', function() {});
        
        expect(socketSpy.on.callCount).toEqual(1);
        expect(socketSpy.on.argsForCall[0][0]).toEqual('foo');
    });
    
    it('notifies every subscribed client', function() {
        var pubsub = PubSub(),
            spyFooA = jasmine.createSpy('foo-A'),
            spyFooB = jasmine.createSpy('foo-B'),
            spyBarA = jasmine.createSpy('bar-A');
            
        pubsub.on('foo', spyFooA);
        pubsub.on('foo', spyFooB);
        pubsub.on('bar', spyBarA);
        
        pubsub.emitSync('foo', {bar: 'baz'});
        
        expect(spyFooA).toHaveBeenCalled();
        expect(spyFooB).toHaveBeenCalled();
        expect(spyBarA).not.toHaveBeenCalled();
        
        expect(spyFooA.mostRecentCall.args[0]).toEqual({bar: 'baz'});
    });
    
    it('doesn\'t notifies unsubscribed clients', function() {
        var pubsub = PubSub(),
            spy = jasmine.createSpy(),
            token;
            
        token = pubsub.on('baz', spy);
        pubsub.unsubscribe(token);
        pubsub.emitSync('baz');
        
        expect(spy).not.toHaveBeenCalled();
    });
});
