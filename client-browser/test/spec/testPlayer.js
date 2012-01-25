describe("Player", function() {
    var pubsubSpy,
        nameContainerSpy,
        player = {}
        ;
    
    beforeEach(function() {
        pubsubSpy = { 
            on: jasmine.createSpy(),
            emitSync: jasmine.createSpy()
        };
        
        nameContainerSpy = {
            text: jasmine.createSpy()
        };
        
        Player({
            $: $,
            pubsub: pubsubSpy,
            cardBuilder: {
                get: jasmine.createSpy().andReturn($('<div>')),
                getBackside: jasmine.createSpy().andReturn($('<div>')),
                getCardWidth: jasmine.createSpy().andReturn(100),
                getCardHeight: jasmine.createSpy().andReturn(200),    
            },
            nameContainer: nameContainerSpy
        }, player);
    });
        
    it("has name", function () {       
        player.setName("foo");
        expect(player.getName()).toEqual("foo");
    });
});

describe("OppositePlayer", function () {
    var pubsubSpy,
        nameContainerSpy,
        player
        ;
    
    beforeEach(function() {
        pubsubSpy = { 
            on: jasmine.createSpy(),
            emitSync: jasmine.createSpy() 
        };
        
        nameContainerSpy = {
            text: jasmine.createSpy()
        };        
        
        player = OppositePlayer({
            $: $,
            pubsub: pubsubSpy,
            cardBuilder: {
                get: jasmine.createSpy().andReturn($('<div>')),
                getBackside: jasmine.createSpy().andReturn($('<div>')),
                getCardWidth: jasmine.createSpy().andReturn(100),
                getCardHeight: jasmine.createSpy().andReturn(200),    
            },
            nameContainer: nameContainerSpy
        });
    });
    
    it("inherits from player (has name)", function () {       
        player.setName("foo");
        expect(player.getName()).toEqual("foo");        
    });
});

describe("ControlledPlayer", function () {
    var pubsubSpy,
        nameContainer,
        validatorSpy,
        player
        ;

    beforeEach(function() {
        pubsubSpy = { 
            on: jasmine.createSpy(),
            emitSync: jasmine.createSpy() 
        };
        
        nameContainerSpy = {
            text: jasmine.createSpy()
        };
        
        validatorSpy = {
            setPlayerName: jasmine.createSpy(),
            isCardValid: jasmine.createSpy(),
            isDrawValid: jasmine.createSpy()
        };     
        
        player = ControlledPlayer({
            $: $,
            pubsub: pubsubSpy,
            cardBuilder: {
                get: jasmine.createSpy().andReturn($('<div>')),
                getBackside: jasmine.createSpy().andReturn($('<div>')),
                getCardWidth: jasmine.createSpy().andReturn(100),
                getCardHeight: jasmine.createSpy().andReturn(200),    
            },
            nameContainer: nameContainerSpy,
            validator: validatorSpy
        });
    });    
    
    it("inherits from player (has name)", function () {
        player.setName("bar");
        expect(player.getName()).toEqual("bar");        
    });
});
