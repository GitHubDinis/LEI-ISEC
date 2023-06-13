'use strict';

// VARIÁVEIS GLOBAIS

const panelControl = document.querySelector('#panel-control');

const panelGame = document.querySelector('#game');

const btLevel = document.querySelector('#btLevel');

const btPlay = document.querySelector('#btPlay');

const message = document.querySelector('#message');

const gameStarted = document.querySelectorAll('#gameStarted');

// FUNÇÕES

function reset(){
    panelGame.style.display = 'none';
    message.textContent = '';
    message.classList.remove('hide');
    if(btLevel.value == '0'){
        btPlay.disabled = true;
    }else{
        btPlay.disabled = false;
        panelGame.style.display = 'grid';
    }
    
    for(let i of gameStarted){
        i.classList.remove('list-item');
    }
}

reset();

function startGame(){
    btLevel.disabled = true;
    btPlay.textContent = 'Terminar Jogo';
    message.classList.add('hide');

    for(let i of gameStarted){
        i.classList.add('list-item');
    }
}

function stopGame(){
    btPlay.textContent = 'Iniciar Jogo';
    btLevel.disabled = false;
    reset();
}

// EVENT LISTENER

btLevel.addEventListener('change', reset);

btPlay.addEventListener('click', function(){
    if (btPlay.textContent == 'Iniciar Jogo'){
        startGame();
    }
    else if(btPlay.textContent == 'Terminar Jogo') {
        stopGame();
    }
});

panelGame.addEventListener('click', function(){
    if(message.textContent == ''){
        message.textContent = 'Clique em Iniciar Jogo!';
    }else if(message.textContent == 'Clique em Inciar Jogo!'){
        message.textContent = '';
    }
});
