describe("Player", function() {
    it("has name", function () {
        var player = {},
            pubsubSpy = { 
                on: jasmine.createSpy() 
            }
            ;
        
        Player({
            $: $,
            pubsub: pubsubSpy
        }, player);
        
        player.setName("foo");
        expect(player.getName()).toEqual("foo");
    });
});

describe("OppositePlayer", function () {
    it("inherits from player (has name)", function () {
        var pubsubSpy = { 
                on: jasmine.createSpy() 
            },
            player = OppositePlayer({
                $: $,
                pubsub: pubsubSpy
            });
            ;
        
        player.setName("foo");
        expect(player.getName()).toEqual("foo");        
    });
});

describe("ControlledPlayer", function () {
    it("inherits from player (has name)", function () {
        var pubsubSpy = { 
                on: jasmine.createSpy() 
            },
            player = ControlledPlayer({
                $: $,
                pubsub: pubsubSpy
            });
            ;
        
        player.setName("bar");
        expect(player.getName()).toEqual("bar");        
    });
});
