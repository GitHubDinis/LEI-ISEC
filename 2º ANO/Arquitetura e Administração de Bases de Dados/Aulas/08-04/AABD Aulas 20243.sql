CREATE TABLE encomenda(
    codigo_enc NUMBER,
    codigo_livro NUMBER, 
    data DATE,
    quant_encomenda NUMBER
);

CREATE SEQUENCE seq_enc START WITH 1;

CREATE OR REPLACE TRIGGER F06_EX25
AFTER UPDATE OF quant_em_stock 
ON livros
FOR EACH ROW
DECLARE
    quant NUMBER;    
    n NUMBER;
BEGIN
    SELECT quant_minima INTO quant
    FROM stock_minimo
    WHERE codigo_livro = :NEW.codigo_livro
    AND quant_minima > :NEW.quant_em_stock;
    
    BEGIN
        SELECT quant_encomenda INTO n 
        FROM encomenda
        WHERE codigo_livro = :NEW.codigo_livro
        AND data > SYSDATE - 10/(24 * 60); 
        UPDATE encomenda SET quant_encomenda = quant_encomenda + :NEW.quant_em_stock
        WHERE codigo_livro = :NEW.codigo_livro;
    EXCEPTION
        WHEN NO_DATA_FOUND THEN
            INSERT INTO encomenda VALUES (seq_enc.NEXTVAL, :NEW.codigo_livro, SYSDATE, quant * 2);
    END;
EXCEPTION
    WHEN NO_DATA_FOUND THEN 
        NULL;
END;

CREATE OR REPLACE PACKAGE LIVRARIA AS
    TAXA_DE_IVA CONSTANT NUMBER := 0.06;
    LIVRO_INVALIDO EXCEPTION;
    SEM_STOCK EXCEPTION;
 
    PROCEDURE AUMENTA_PRECO (PERCENT NUMBER) IS
    BEGIN
        UPDATE livros SET preco_tabela := preco_tabela + (preco_tabela * percent);
    END AUMENTA_PRECO; -- todos os livros
    
    PROCEDURE AUMENTA_PRECO (PERCENT NUMBER, GENERO VARCHAR) IS
    BEGIN
        UPDATE livros l WHERE l.genero = GENERO SET preco_tabela := preco_tabela + (preco_tabela * percent); 
    END AUMENTA_PRECO;-- apenas deste genero

    FUNCTION  GETPRECO(codLivro NUMBER) RETURN number IS
        preco NUMBER;
    BEGIN
        SELECT preco_tabela INTO preco
        FROM LIVROS
        WHERE codigo_livro = codLivro;
        
        RETURN preco;
    END GETPRECO; -- obtem preco do livro
    
    FUNCTION  QUANT_EM_STOCK(codLivro NUMBER) RETURN number;
    FUNCTION  EXISTE_EM_STOCK(codLivro NUMBER, QUANTIDADE number) RETURN number;

    PROCEDURE REGISTA_VENDA(codLivro NUMBER, codCliente NUMBER);
    PROCEDURE REGISTA_VENDA(codLivro NUMBER, NIFCliente NUMBER);
    PROCEDURE REGISTA_VENDA(TITULO VARCHAR, codCliente NUMBER);

    PROCEDURE REGISTA_ENCOMENDA(codLivro NUMBER, quantidade NUMBER);

    PROCEDURE REGISTA_LIVRO(ISBN number, titulo VARCHAR, Genero VARCHAR, Preco NUMBER, NomeAutor VARCHAR);
END LIVRARIA;


