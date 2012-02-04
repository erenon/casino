PlayerCollection = require('../../../src/game/PlayerCollection.js');

describe("PlayerCollecton", function() {
    var pc;
    
    beforeEach(function() {
        pc = PlayerCollection();
    });
    
    it("adds players", function() {
        pc.addPlayer({});
        expect(pc.length()).toEqual(1);
    });
    
    it("calls players in order", function() {
        var p1 = {name: 'p1'},
            p2 = {name: 'p2'},
            p3 = {name: 'p3'}
            ;
            
        pc.addPlayer(p1);
        pc.addPlayer(p2);
        pc.addPlayer(p3);
        
        pc.reset();
        
        expect(pc.getCurrentPlayer()).toEqual(p1);
        
        expect(pc.next()).toEqual(p2);
        expect(pc.next()).toEqual(p3);
        expect(pc.next()).toEqual(p1);
        expect(pc.next()).toEqual(p2);
        expect(pc.next()).toEqual(p3);
    });
    
    it("reverses turn", function() {
        var p1 = {name: 'p1'},
            p2 = {name: 'p2'},
            p3 = {name: 'p3'}
            ;
            
        pc.addPlayer(p1);
        pc.addPlayer(p2);
        pc.addPlayer(p3);
        
        pc.reset();
        pc.next();
        
        pc.reverseTurn();
        expect(pc.next()).toEqual(p1);        
    });
    
    it("reverses turn - on first player", function() {
        var p1 = {name: 'p1'},
            p2 = {name: 'p2'},
            p3 = {name: 'p3'}
            ;
            
        pc.addPlayer(p1);
        pc.addPlayer(p2);
        pc.addPlayer(p3);
        
        pc.reset();
        
        pc.reverseTurn();
        expect(pc.next()).toEqual(p3);        
    });
});

