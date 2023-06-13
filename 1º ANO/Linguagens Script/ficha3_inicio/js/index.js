'use strict';
const panelControl = document.querySelector('#panel-control');
const panelGame = document.querySelector('#game');
const btLevel = document.querySelector('#btLevel');
const btPlay = document.querySelector('#btPlay');

const cards = document.querySelectorAll('.card');
const cardsLogos = ['angular','bootstrap','html','javascript','vue','svelte','react','css','backbone','ember'];


// ------------------------
// Funções Genéricas
// ------------------------
function reset() {

     message.classList.remove('hide');
     if (btLevel.value === '0')
          btPlay.disabled = true
     else {
          btPlay.disabled = false;
          panelGame.style.display = 'grid';
     }
     const elementos = panelControl.querySelectorAll('.list-item');
     elementos.forEach(elemento => {
          elemento.classList.remove('gameStarted');
     });
}

function startGame() {
     message.classList.add('hide');
     btLevel.disabled = true;
     btPlay.textContent = 'Terminar Jogo';
     const elementos = panelControl.querySelectorAll('.list-item');
     elementos.forEach(elemento => {
          elemento.classList.add('gameStarted')
     });
     shuffleArray(cardsLogos);
     showCards();

     let indice = 0;
     for(card of cards){
          card.dataset.logo = cardsLogos[indice];
          card.querySelector('.card-font').src = 'images/${cardsLogos[indice]}.png';
          indice++;
     }


}

function stopGame() {
     btPlay.textContent = 'Iniciar Jogo'
     btLevel.disabled = false;
     hideCards();
     reset();
}

const shuffleArray = array => {
     for(let i = array.length - 1; i > 0; i--){
          const j = Math.floor(Math.random() * (i + 1));
          const temp = array[i];
          array[i] = array[j];
          array[j] = temp;
     }
};

function showCards(){
     for (let card of cards){
         card.classList.add('flipped');
     }
}

function hideCards(){
     for(let card of cards){
          card.classList.remove('flipped');
     }
}


// ------------------------
// Event Listeners
// ------------------------
btLevel.addEventListener('change', reset);
btPlay.addEventListener('click', () => (btPlay.textContent == 'Terminar Jogo') ? stopGame() : startGame());


reset();