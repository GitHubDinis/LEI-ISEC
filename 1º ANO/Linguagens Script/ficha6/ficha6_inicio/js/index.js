'use strict';
const panelControl = document.querySelector('#panel-control');
const panelGame = document.querySelector('#game');
const btLevel = document.querySelector('#btLevel');
const btPlay = document.querySelector('#btPlay');
const labelGameTime = document.querySelector('#gameTime');
const labelPoints = document.querySelector('#points');

let cardsLogos = ['angular', 'bootstrap', 'html', 'javascript', 'vue', 'svelte', 'react', 'css', 'backbone', 'ember'];
let cards = document.querySelectorAll('.card');
let flippedCards = [];
let totalFlippedCards = 0;

const TIMEOUTGAME = 20;
let timer;
let timerId;
let totalPoints = 0;

let topGamers = [{nickname: 'Ze', points: 331}, {nickname: 'Maria', points: 321}];
const messageGameOver = document.getElementById('messageGameOver');

const gameOver = () => { return totalFlippedCards === cards.length; }

const shuffleArray = array => {
     for (let i = array.length - 1; i > 0; i--) {
          const j = Math.floor(Math.random() * (i + 1));
          const temp = array[i];
          array[i] = array[j];
          array[j] = temp;
     }
}

(function getLocalStorage(){
     localStorage.getItem('nickname');
     localStorage.getItem(topGamers);
 })();

function updatePoints(operation = '+') {
     operation === '+'
          ? totalPoints += (timer * (cards.length / 2))
          : totalPoints < 5 ? totalPoints = 0 : totalPoints -= 5;
     labelPoints.textContent = totalPoints;
}
function updateGameTime() {
     timer--;
     if (timer < 10) labelGameTime.style.backgroundColor = 'red';
     labelGameTime.textContent = `${timer}s`;
     if (timer == 0) stopGame();
}
function flipCard(selectedCard) {
     selectedCard.classList.add('flipped');
     flippedCards.push(selectedCard);
     if (flippedCards.length === 2)
          checkPair();
}
function checkPair() {
     let [card1, card2] = flippedCards;
     const isMatch = (card1.dataset.logo === card2.dataset.logo);
     if (isMatch) {
          setTimeout(() => {
               card1.classList.add('inative'); card2.classList.add('inative');
               card1.querySelector('.card-front').classList.add('grayscale');
               card2.querySelector('.card-front').classList.add('grayscale');
               totalFlippedCards += 2;
               updatePoints('+');
               if (gameOver()) stopGame();
          }, 500);
     }
     else {
          setTimeout(() => {
               card1.classList.remove('flipped'); card2.classList.remove('flipped');
               card1.addEventListener('click', funClickCard, { once: true });
               card2.addEventListener('click', funClickCard, { once: true });
               updatePoints('-');
          }, 500);
     }
     flippedCards = [];
}
function createPanelGame() {
     const backupCards = [...cards];
     panelGame.innerHTML = '';
     backupCards.forEach(c => panelGame.appendChild(c.cloneNode(true)));
     cards = panelGame.childNodes;
}
function reset() {
     [btLevel.disabled, btLevel.value, btPlay.disabled, panelGame.style.display, message.textContent] = [true, 1, false, 'grid', ''];
     message.classList.remove('hide');
     panelControl.querySelectorAll('.list-item').forEach(elemento => elemento.classList.remove('gameStarted'));
     createPanelGame();
     [labelGameTime.textContent, labelPoints.textContent] = [`${TIMEOUTGAME}s`, 0]
}
const createAndShuffleCards = array => {
     shuffleArray(array);
     array.splice(cards.length / 2, Number.MAX_VALUE);
     array.push(...array);
     shuffleArray(array)
}

function funClickCard() { flipCard(this); }

function startGame() {
     btPlay.textContent = 'Terminar Jogo';
     panelControl.querySelectorAll('.list-item').forEach(elemento => elemento.classList.add('gameStarted'));
     message.classList.add('hide');

     let [indice, newCardLogos] = [0, [...cardsLogos]];
     createAndShuffleCards(newCardLogos);
     for (let card of cards) {
          card.querySelector('.card-front').src = `images/${newCardLogos[indice]}.png`;
          card.dataset.logo = newCardLogos[indice++];
          card.addEventListener('click', funClickCard, { once: true });
     }
     [flippedCards, totalFlippedCards, totalPoints] = [[], 0, 0];
     [timer, timerId] = [TIMEOUTGAME, setInterval(updateGameTime, 1000)];
     [labelGameTime.textContent, labelPoints.textContent] = [`${timer}s`, 0];
     labelGameTime.removeAttribute('style');
     getTopPoints();
}
function stopGame() {
     [btPlay.textContent, modalGameOver.style.display, document.querySelector('#messageGameOver').textContent] = ['Iniciar Jogo', 'block', `Pontuação:${totalPoints}`];
     clearInterval(timerId);
     checkTop10();
     reset();
}

function getTop10(){
     let infoTop = document.getElementById('infoTop');

     /* for(let i = 0; i < topGamers.length; i++){
          arrayTop10 += '${topGamers[i].nickname} _ ${topGamers[i].points}<br>';
          console.log(arrayTop10);
     }
     infoTop.innerHTML = arrayTop10; */

     let div = document.createElement('div');     
     let p1 = document.createElement('p');
     p1.textContent = 'Nick Name';
     let p2 = document.createElement('p');
     p2.textContent = 'Pontuação';
     div.appendChild(p1);
     div.appendChild(p2);

     for (let i = 0; i < topGamers.length; i++) {     
          infoTop.appendChild(div.cloneNode(true));  
          div.firstChild.textContent = `${topGamers[i].nickname}`;
          div.lastChild.textContent = `${topGamers[i].points}`;
     }

     infoTop.appendChild(div);
}

function getTopPoints(){
     let pointsTop = document.getElementById('pointsTop');
     pointsTop.innerHTML = `${topGamers[0].points}`;
}

function getLastPoints(){
     let pointsLast = 0;
     let indexUltimo = topGamers.length;

     pointsLast = topGamers[indexUltimo - 1].points;

     console.log(`${topGamers[indexUltimo-1].points}`);

     return pointsLast;
}

function checkTop10(){
     let pointsLast = getLastPoints();
     let nick = document.getElementById('nickname');

     if(topGamers.length < 10 || totalPoints > pointsLast){
          nick.style.display = 'block';
          messageGameOver.innerHTML += "<br>Parabéns! Entrou no Top 10";
     }
}

function saveTop10(){
     let inputNick = document.getElementById('inputNick').value;
    localStorage.setItem('Nickname', inputNick);

    const novosPontos = {nickname: inputNick, points: totalPoints};
    const dimTopGamers = topGamers.length;
    
    let userExists = false;
    topGamers.forEach((gamer,index) =>{
        if(gamer.nickname === inputNick){
            userExists = true;
            topGamers[index].points = totalPoints;
        }
    
    })

    if(userExists === false){
        topGamers.push(novosPontos);
    }

    topGamers.sort(function (a, b) { return b.points - a.points });

    if(dimTopGamers > 10){
        topGamers.pop();
    }

    localStorage.setItem(topGamers, JSON.stringify({nickname:nickname, points: totalPoints}));
}

btLevel.addEventListener('change', reset);
btPlay.addEventListener('click', () => btPlay.textContent === 'Terminar Jogo' ? stopGame() : startGame());
panelGame.addEventListener('click', () => message.textContent === '' ? message.textContent = 'Clique em Iniciar o Jogo!' : message.textContent = '');

btTop.addEventListener('click', function () {
     getTop10();
});

okTop.addEventListener('click', function(){
     saveTop10();
     modalGameOver.style.display = "none";
     reset();
});

reset();

