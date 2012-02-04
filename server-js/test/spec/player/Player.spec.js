Player = require('../../../src/player/Player.js');

describe('Player', function() {
    var p,
        game;
    
    beforeEach(function() {
        p = {};
        game = {
            sayUno: jasmine.createSpy()
        };
        
        Player({
            game: game,
            name: 'player-test'
        }, p);
    });
    
    it('adds cards', function() {
        expect(p.getCardCount()).toEqual(0);
        
        p.notify('cardAdded', { card: {}});
        expect(p.getCardCount()).toEqual(1);
        p.notify('cardAdded', { card: {}});
        expect(p.getCardCount()).toEqual(2);
    });
    
    it('blocks and unblocks', function() {
        expect(p.block()).toBeFalsy();
        p.block(true);
        expect(p.block()).toBeTruthy();
        p.block(false);
        expect(p.block()).toBeFalsy();
    });
    
    it('sets and unsets uno', function() {
        expect(p.uno()).toBeFalsy();
        p.uno(true);
        expect(p.uno()).toBeTruthy();
        expect(game.sayUno).toHaveBeenCalled();
        
        p.uno(false);
        expect(p.uno()).toBeFalsy();
    });
});
