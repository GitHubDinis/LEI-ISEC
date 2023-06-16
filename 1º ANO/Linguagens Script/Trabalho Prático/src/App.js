import React, { useState, useEffect } from 'react';
import './App.css';
import Header from './components/Header.component';
import './styles/Header.css';
import Footer  from './components/Footer.component';
import './styles/Footer.css'
import ControlPanel from './components/control-panel.component';
import './styles/control-panel.css'

function Square({ value, onSquareClick, isPlayable, winner }) {
  return (
    <button
      className={`square ${isPlayable ? '' : 'disabled'} ${winner ? 'winner' : ''}`}
      onClick={onSquareClick}
      disabled={!isPlayable}
    >
      { value }
    </button>
  );
}

function App() {
  const [gameStarted, setGameStarted] = useState(false);
  const [xIsNext, setXIsNext] = useState(true);
  const [squares, setSquares] = useState(Array(9).fill(null).map(() => Array(9).fill(null)));
  const [activeBoard, setActiveBoard] = useState(null);
  const winner = calculateWinner(squares, activeBoard);
  const overallWinner = calculateOverallWinner(squares);
  const [timerX, setTimerX] = useState(0);
  const [timerO, setTimerO] = useState(0);
  const [isAgainstComputer, setIsAgainstComputer] = useState(false);
  const [overalWinner, setOverallWinner] = useState(null);

  let status;
  if (overallWinner) {
    status = 'General Winner: ' + overallWinner;
  } else if (winner) {
    status = 'Winner: ' + winner;
    setActiveBoard(null);
  } else {
    status = 'Player Turn: ' + (xIsNext ? 'X' : 'O');
  }

  useEffect(() => {
    let timerInterval = null;
  
    const endGame = () => {
      let generalWinner = null;
      let playerXWins = 0;
      let playerOWins = 0;

      for (let i = 0; i < squares.length; i++) {
        const board = squares[i];
        const boardWinner = calculateWinner(board, null);

        if (boardWinner === 'X') {
          playerXWins++;
        } else if (boardWinner === 'O') {
          playerOWins++;
        }
      }

      if (playerXWins > playerOWins) {
        generalWinner = 'X';
      } else if (playerOWins > playerXWins) {
        generalWinner = 'O';
      }

      // Atualizar o estado do vencedor geral
      setOverallWinner(generalWinner);

      // Exibir uma mensagem de encerramento do jogo
      if (generalWinner) {
        alert(`Game Over! General Winner: Player ${generalWinner}`);
      } else {
        alert("Game Over! It's a draw!");
      }

      // Parar o tempo
      clearInterval(timerInterval);
    };
  
    if (gameStarted && !overalWinner && !winner) {
      timerInterval = setInterval(() => {
        if (xIsNext) {
          setTimerX((prevTimerX) => {
            const newTimerX = prevTimerX + 1;
            if (newTimerX >= 100) {
              endGame();
            }
            return newTimerX;
          });
        } else {
          setTimerO((prevTimerO) => {
            const newTimerO = prevTimerO + 1;
            if (newTimerO >= 100) {
              endGame();
            }
            return newTimerO;
          });
        }
      }, 1000);
    }
  
    return () => {
      clearInterval(timerInterval);
    };
  }, [overalWinner, timerO, timerX, gameStarted, xIsNext, squares, winner, overallWinner]);  
  
  function handleClick(boardIndex, squareIndex) {
    if (overallWinner || winner || ((activeBoard !== null && activeBoard !== boardIndex) || squares[boardIndex][squareIndex] !== null)) {
      return;
    }

    const nextSquares = squares.map((board, i) => {
      if (i === boardIndex) {
        return board.map((square, j) => {
          if (j === squareIndex) {
            return xIsNext ? 'X' : 'O';
          }
          return square;
        });
      }
      return board;
    });

    setSquares(nextSquares);

    const boardWinner = calculateWinner(nextSquares, boardIndex);
    if (boardWinner) {
      const updatedSquares = nextSquares.map((board, i) => {
        if (i === boardIndex) {
          return board.map((square) => boardWinner);
        }
        return board;
      });
      setSquares(updatedSquares);
    }

    setActiveBoard(squareIndex);

    if (isAgainstComputer && !overallWinner && !winner) {
      setXIsNext(!xIsNext);
      setTimeout(makeComputerMove, 500); // Adiciona um atraso de 500ms antes do movimento do computador
    } else {
      setXIsNext(!xIsNext);
    }
  }

  function resetGame() {
    setXIsNext(true);
    setSquares(Array(9).fill(null).map(() => Array(9).fill(null)));
    setActiveBoard(null);
    setTimerX(0);
    setTimerO(0);
  }

  function makeComputerMove() {
    // OPÇÃO DE JOGAR CONTRA O COMPUTADOR.  
  }
  
  return (
    <div id='main'>
      <Header/>
      <ControlPanel></ControlPanel>
      <div className="game-container">
      <div id='iniciar' className="iniciar-container">
      <button className="iniciarjogo-button" onClick={() => setGameStarted(true)}>
          Iniciar Jogo
      </button>
      </div>
        <div className="status">{status}</div>
        <div className="timers">
          <div className="timer">
            <span>Player X: {timerX} seconds</span>
          </div>
          <div className="timer">
            <span>Player O: {timerO} seconds</span>
          </div>
        </div>
        <div className="ultimate-board">
          {squares.map((board, i) => (
            <div key={i} className={`board ${activeBoard === i ? 'active' : ''}`}>
              {board.map((square, j) => (
                <Square
                  key={j}
                  value={square}
                  onSquareClick={() => handleClick(i, j)}
                  isPlayable={activeBoard === i || activeBoard === null}
                  winner={winner && winner === square}
                />
              ))}
            </div>
          ))}
        </div>
        <div className="againstComputer-container">
          <button className="computer-button" onClick={() => setIsAgainstComputer(true)}>
            Jogar contra o computador
          </button>
        </div>
        <div className="reset-button-container">
          <button className="reset-button" onClick={resetGame}>
            Reiniciar Jogo
          </button>
        </div>
      </div>
      <Footer/>
    </div>
  );
}

function calculateWinner(squares, activeBoard) {
  const winningCombos = [
    // Linhas
    [0, 1, 2],
    [3, 4, 5],
    [6, 7, 8],
    // Colunas
    [0, 3, 6],
    [1, 4, 7],
    [2, 5, 8],
    // Diagonais
    [0, 4, 8],
    [2, 4, 6],
  ];

  const checkBoardWinner = (board) => {
    for (let combo of winningCombos) {
      const [a, b, c] = combo;
      if (board[a] && board[a] === board[b] && board[a] === board[c]) {
        return board[a];
      }
    }
    return null;
  };

  for (let combo of winningCombos) {
    const [a, b, c] = combo;
    const boardA = squares[a];
    const boardB = squares[b];
    const boardC = squares[c];

    if (
      boardA &&
      boardA === boardB &&
      boardA === boardC &&
      (activeBoard === null || activeBoard === a)
    ) {
      return boardA;
    }
  }

  if (activeBoard !== null) {
    const board = squares[activeBoard];
    return checkBoardWinner(board);
  }

  return null;
}

function calculateOverallWinner(squares) {
  const winningCombos = [
    // Linhas
    [0, 1, 2],
    [3, 4, 5],
    [6, 7, 8],
    // Colunas
    [0, 3, 6],
    [1, 4, 7],
    [2, 5, 8],
    // Diagonais
    [0, 4, 8],
    [2, 4, 6],
  ];

  for (let combo of winningCombos) {
    const [a, b, c] = combo;
    const boardA = squares[a][0];
    const boardB = squares[b][0];
    const boardC = squares[c][0];

    if (boardA && boardA === boardB && boardA === boardC) {
      return boardA;
    }
  }

  return null;
}

export default App;