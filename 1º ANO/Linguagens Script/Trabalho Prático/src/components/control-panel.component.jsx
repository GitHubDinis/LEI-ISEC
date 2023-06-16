import React, { useState } from 'react';

function ControlPanel() {
  const [jogador1, setJogador1] = useState('');
  const [jogador2, setJogador2] = useState('');
  const [simbolo1, setSimbolo1] = useState('');
  const [simbolo2, setSimbolo2] = useState('');

  const handleSubmit = (event) => {
    event.preventDefault();

    const valoresPossiveis = ['X', 'O'];
    const indiceAleatorio = Math.floor(Math.random() * valoresPossiveis.length);
    const valorAleatorio = valoresPossiveis[indiceAleatorio];

    if (valorAleatorio === 'X') {
      setSimbolo1(valorAleatorio);
      setSimbolo2('O');
    } else {
      setSimbolo1(valorAleatorio);
      setSimbolo2('X');
    }

    console.log(`JOGADOR 1: ${jogador1}`);
    console.log(`JOGADOR 2: ${jogador2}`);
  };

  return (
    <section id="panel-control">
      <h1 className="title">JOGO ULTIMATE TIC-TAC-TOE</h1>
      <form onSubmit={handleSubmit}>
        <div className="label1">
          <label>
            JOGADOR 1:
            <input
              type="text"
              value={jogador1}
              onChange={(event) => setJogador1(event.target.value)}
            />
          </label>
          <span> Símbolo Aleatório: {simbolo1}</span>
        </div>
        <br />
        <div className="label2">
          <label>
            JOGADOR 2:
            <input
              type="text"
              value={jogador2}
              onChange={(event) => setJogador2(event.target.value)}
            />
          </label>
          <span> Símbolo Aleatório: {simbolo2}</span>
        </div>
        <br />
        <button type="submit" id="btPlay">Atribuir Símbolos</button>
      </form>
    </section>
  );
}

export default ControlPanel;