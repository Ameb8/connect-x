export class WebPlayerAdapter {
    constructor(name, Module) {
        this.name = name;
        this.Module = Module;

        this.player = new Module.WebPlayer(name);

        this.player.setCallbacks(
            this.selectMove.bind(this),
            this.retrySelectMove.bind(this),
            this.gameWon.bind(this),
            this.gameLost.bind(this),
            this.gameTie.bind(this),
            this.opponentForfeit.bind(this)
        );
    }

    selectMove(board) {
        console.log(`[selectMove] ${this.name} board:`, board.getBoard());
        return 0; // dummy move
    }

    retrySelectMove(board) {
        console.log(`[retrySelectMove] ${this.name} board:`, board.getBoard());
        return 1; // dummy move
    }

    gameWon(board) {
        console.log(`[gameWon] ${this.name} board:`, board.getBoard());
    }

    gameLost(board) {
        console.log(`[gameLost] ${this.name} board:`, board.getBoard());
    }

    gameTie(board) {
        console.log(`[gameTie] ${this.name} board:`, board.getBoard());
    }

    opponentForfeit(board) {
        console.log(`[opponentForfeit] ${this.name} board:`, board.getBoard());
    }

    getPlayer() {
        return this.player; // C++ object to use in the game engine
    }
}