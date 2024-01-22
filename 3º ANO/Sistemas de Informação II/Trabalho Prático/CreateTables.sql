-- SQLINES LICENSE FOR EVALUATION USE ONLY
CREATE TABLE vendas (
    id_venda             INTEGER,
    quantidade_produtos     INTEGER,
    preco_unidade         FLOAT,
    receita_total         FLOAT,
    funcionario_id_funcionario INTEGER NOT NULL,
    promocao_id_promocao     INTEGER NOT NULL,
    cliente_id_cliente     INTEGER NOT NULL,
    produto_id_produto     INTEGER NOT NULL,
    loja_id_loja         INTEGER NOT NULL,
    tempo_id_tempo         INTEGER NOT NULL,
    PRIMARY KEY(id_venda)
);

-- SQLINES LICENSE FOR EVALUATION USE ONLY
CREATE TABLE tempo (
    id_tempo     INTEGER,
    dia     INTEGER,
    mes     INTEGER,
    ano     INTEGER,
    trimestre INTEGER,
    semestre     INTEGER,
    horas     INTEGER,
    minutos     INTEGER,
    PRIMARY KEY(id_tempo)
);

-- SQLINES LICENSE FOR EVALUATION USE ONLY
CREATE TABLE loja (
    id_loja     INTEGER,
    rua         VARCHAR(256),
    distrito     VARCHAR(100),
    cod_postal     VARCHAR(120),
    departamento VARCHAR(120),
    ano_abertura INTEGER,
    gerente     VARCHAR(300),
    cidade     VARCHAR(120),
    PRIMARY KEY(id_loja)
);

-- SQLINES LICENSE FOR EVALUATION USE ONLY
CREATE TABLE produto (
    id_produto     INTEGER,
    categoria     VARCHAR(75),
    nome         VARCHAR(120),
    preco_unitario FLOAT,
    marca         VARCHAR(120),
    fornecedor     VARCHAR(120),
    PRIMARY KEY(id_produto)
);

-- SQLINES LICENSE FOR EVALUATION USE ONLY
CREATE TABLE cliente (
    id_cliente INTEGER,
    nome     VARCHAR(256),
    nif     INTEGER,
    data_nasc     DATE,
    cidade     VARCHAR(100),
    PRIMARY KEY(id_cliente)
);

-- SQLINES LICENSE FOR EVALUATION USE ONLY
CREATE TABLE promocao (
    id_promocao INTEGER,
    tipo     VARCHAR(75),
    descricao     VARCHAR(512),
    PRIMARY KEY(id_promocao)
);

-- SQLINES LICENSE FOR EVALUATION USE ONLY
CREATE TABLE funcionario (
    id_funcionario     INTEGER,
    nome         VARCHAR(320),
    tipo_funcionario VARCHAR(120),
    PRIMARY KEY(id_funcionario)
);
ALTER TABLE vendas ADD CONSTRAINT vendas_fk1 FOREIGN KEY (funcionario_id_funcionario) REFERENCES funcionario(id_funcionario);
ALTER TABLE vendas ADD CONSTRAINT vendas_fk2 FOREIGN KEY (promocao_id_promocao) REFERENCES promocao(id_promocao);
ALTER TABLE vendas ADD CONSTRAINT vendas_fk3 FOREIGN KEY (cliente_id_cliente) REFERENCES cliente(id_cliente);
ALTER TABLE vendas ADD CONSTRAINT vendas_fk4 FOREIGN KEY (produto_id_produto) REFERENCES produto(id_produto);
ALTER TABLE vendas ADD CONSTRAINT vendas_fk5 FOREIGN KEY (loja_id_loja) REFERENCES loja(id_loja);
ALTER TABLE vendas ADD CONSTRAINT vendas_fk6 FOREIGN KEY (tempo_id_tempo) REFERENCES tempo(id_tempo);