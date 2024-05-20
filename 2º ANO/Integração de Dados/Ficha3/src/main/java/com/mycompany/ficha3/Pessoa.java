/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package com.mycompany.ficha3;

import java.io.FileNotFoundException;
import java.io.IOException;
import static java.lang.Integer.parseInt;

/**
 *
 * @author Utilizador
 */
public class Pessoa {
    int id;
    String nome;
    String morada;
    String profissao;

    public Pessoa(int id, String nome, String morada, String profissao) {
        this.id = id;
        this.nome = nome;
        this.morada = morada;
        this.profissao = profissao;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getNome() {
        return nome;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public String getMorada() {
        return morada;
    }

    public void setMorada(String morada) {
        this.morada = morada;
    }

    public String getProfissao() {
        return profissao;
    }

    public void setProfissao(String profissao) {
        this.profissao = profissao;
    }
    
    public void imprime(){
        System.out.println("Dados do aluno: ");
        System.out.println("\tID: " + this.id);
        System.out.println("\tNome: " + this.nome);
        System.out.println("\tMorada: " + this.morada);
        System.out.println("\tProfissão: " + this.profissao);
    }
    
    static Pessoa procura_dados_pessoa(String id) throws FileNotFoundException, IOException{
        String nome = Wrappers.procura_por_id(id);
        String morada = Wrappers.procura_cidade_por_id(id);
        String profissao = Wrappers.procura_profissao_por_id(id);
        
        Pessoa p = new Pessoa(parseInt(id), nome, morada, profissao);
        return p;
    }
}
