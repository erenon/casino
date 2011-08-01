var casino = require('../lib/casino'),
    //Player = require('../lib/player.js'),
    Player = function(session_id) {
        this.session_id = session_id;
        var that = this;
        
        this.registerCallback = function(cb_name, cb) {
            this[cb_name] = cb;
        };
        
        this.notify = function(event) {
            console.log('event: ', event);
            
            if (event.event_type == 'players_turn' && event.player.name == 'player') {
                native_player.playCard({});
            }
        };
        
        this.pickAction = function(callback) {
            console.log('picking action...');
                       
            console.log('+-----+');
            return 0;
        };
        
        this.addAction = function(action) {
            console.log('action added: ', action);
        };
        
        var native_player = new casino.Player(this);
    },
    player_a = new Player(123),
    //player_b = new Player(456),
    game = new casino.Game(4);
    
  
/*casino.Player.prototype.print = function(data) {
    console.log(data);
}

player_a = new casino.Player(123);
player_a.print('foobar');*/
        
game.joinPlayer(player_a);
//game.joinPlayer(player_b);


game.addBot(3);
game.start();
game.dispose();
