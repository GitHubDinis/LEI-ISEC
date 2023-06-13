'use strict';
// ------------------------
// Variáveis Globais
// ------------------------
const panelControl = document.querySelector('#panel-control');
const panelGame = document.querySelector('#panel-game');
const btLevel = document.querySelector('#btLevel');
let cards = panelGame.querySelectorAll('.card');

let cardsLogos = ['angular', 'bootstrap', 'html', 'javascript', 'vue', 'svelte', 'react', 'css', 'backbone', 'ember'];
let flippedCards = [];
let totalFlippedCards = 0;
let cardsListeners;

const TIMEOUTGAME = 20;
let labelGameTime = document.getElementById('gameTime');
let timer;
let timerId;

// Algoritmo Fisher-Yates -  Algoritmo que baralha um array.
const shuffleArray = array => {
    for (let i = array.length - 1; i > 0; i--) {
        const j = Math.floor(Math.random() * (i + 1));
        const temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

// ------------------------
// Funções Jogo memória
// ------------------------

function flipCard(selectedCard) {
    selectedCard.classList.add('flipped');
    flippedCards.push(selectedCard);
    if (flippedCards.length === 2)
        checkPair();
}

const gameOver = () => { return totalFlippedCards === cards.length; }

function checkPair() {
    let [card1, card2] = flippedCards;
    const isMatch = (card1.dataset.logo === card2.dataset.logo);
    if (isMatch) {
        setTimeout(() => {
            card1.classList.add('inative');
            card2.classList.add('inative');
            card1.querySelector('.card-front').classList.add('grayscale');
            card2.querySelector('.card-front').classList.add('grayscale');
            totalFlippedCards += 2;
            if (gameOver()) stopGame();
        }, 500);
    }
    else {
        setTimeout(() => {
            card1.classList.remove('flipped');
            card2.classList.remove('flipped');
            createEventListenerFlipCard(card1);
            createEventListenerFlipCard(card2);
        }, 500);
    }
    flippedCards = [];
}

const createAndShuffleCards = array => {
    shuffleArray(array);
    array.splice(cards.length / 2, Number.MAX_VALUE);
    array.push(...array);
    shuffleArray(array)
}

function startGame() {
    btPlay.textContent = 'Terminar Jogo';
    let [indice, newCardLogos] = [0, [...cardsLogos]];
    createAndShuffleCards(newCardLogos);
    cards.forEach(card => {
        card.querySelector('.card-front').src = `images/${newCardLogos[indice]}.png`;
        card.dataset.logo = newCardLogos[indice++];
        createEventListenerFlipCard(card);
    });
    flippedCards = [];
    totalFlippedCards = 0;
    timer = TIMEOUTGAME;
    timerId = setInterval(updateGameTime, 1000);
}

function stopGame() {
    modalGameOver.style.display = 'block';
    btPlay.textContent = 'Iniciar Jogo';
    clearInterval(timerId);
}
function reset() {
    btLevel.value = 1;
    btLevel.disabled = true;
    for (let card of cards) card.classList.remove('flipped');
    labelGameTime.removeAttribute('style');
    createPanelGame();
}

function updateGameTime(){
    timer--;
    labelGameTime.textContent = `${timer}`;
    
    if(timer < 10){
        labelGameTime.style.backgroundColor = 'red';
    }

    if(timer == 0){
        stopGame();
    }
}
// --------------------------------------------------------
// Event Listeners
// --------------------------------------------------------
btPlay.addEventListener('click', function () {
    if (btPlay.textContent === 'Terminar Jogo')
        stopGame()
    else startGame();
});

const createEventListenerFlipCard = (c) => {
    c.addEventListener('click', function fc() {
        flipCard(this);
    }, { once: true });
}

const backupCards = [...cards];
function createPanelGame() {
    panelGame.innerHTML = "";
    backupCards.forEach(c => panelGame.appendChild(c.cloneNode(true)));
    cards = panelGame.childNodes;
}

reset();