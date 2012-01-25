describe("Player", function() {
    var pubsubSpy,
        player = {}
        ;
    
    beforeEach(function() {
        pubsubSpy = { 
            on: jasmine.createSpy() 
        };
        
        Player({
            $: $,
            pubsub: pubsubSpy,
            cardBuilder: {
                get: jasmine.createSpy().andReturn($('<div>')),
                getBackside: jasmine.createSpy().andReturn($('<div>')),
                getCardWidth: jasmine.createSpy().andReturn(100),
                getCardHeight: jasmine.createSpy().andReturn(200),    
            }
        }, player);
    });
        
    it("has name", function () {       
        player.setName("foo");
        expect(player.getName()).toEqual("foo");
    });
});

describe("OppositePlayer", function () {
    var pubsubSpy,
        player
        ;
    
    beforeEach(function() {
        pubsubSpy = { 
            on: jasmine.createSpy() 
        };
        
        player = OppositePlayer({
            $: $,
            pubsub: pubsubSpy,
            cardBuilder: {
                get: jasmine.createSpy().andReturn($('<div>')),
                getBackside: jasmine.createSpy().andReturn($('<div>')),
                getCardWidth: jasmine.createSpy().andReturn(100),
                getCardHeight: jasmine.createSpy().andReturn(200),    
            }
        });
    });
    
    it("inherits from player (has name)", function () {       
        player.setName("foo");
        expect(player.getName()).toEqual("foo");        
    });
});

describe("ControlledPlayer", function () {
    var pubsubSpy,
        player
        ;

    beforeEach(function() {
        pubsubSpy = { 
            on: jasmine.createSpy() 
        };
        
        player = ControlledPlayer({
            $: $,
            pubsub: pubsubSpy,
            cardBuilder: {
                get: jasmine.createSpy().andReturn($('<div>')),
                getBackside: jasmine.createSpy().andReturn($('<div>')),
                getCardWidth: jasmine.createSpy().andReturn(100),
                getCardHeight: jasmine.createSpy().andReturn(200),    
            }
        });
    });    
    
    it("inherits from player (has name)", function () {
        player.setName("bar");
        expect(player.getName()).toEqual("bar");        
    });
});
