/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package com.mycompany.workid;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Date;

/**
 *
 * @author Utilizador
 */
public class Escritores {
    int id;
    String nome, nacionalidade, fotografia, generoLiterario;
    String nascimento, morte;
    ArrayList<String> premios = new ArrayList();
    ArrayList<String> ocupacoes = new ArrayList();
    
    public Escritores(int id, String nome, String nacionalidade, String fotografia, String generoLiterario, String nascimento, String morte, ArrayList premios, ArrayList ocupacoes){
        this.id = id;
        this.nome = nome;
        this.nacionalidade = nacionalidade;
        this.fotografia = fotografia;
        this.generoLiterario = generoLiterario;
        this.nascimento = nascimento;
        this.morte = morte;
        this.premios = premios;
        this.ocupacoes = ocupacoes;
    }
    
    public int getID(){
        return id;
    }
    
    public void setID(int id){
        this.id = id;
    }
    
    public String getNome(){
        return nome;
    }
    
    public void setNome(String nome){
        this.nome = nome;
    }
    
    public String getNacionalidade(){
        return nacionalidade;
    }
    
    public void setNacionalidade(String nacionalidade){
        this.nacionalidade = nacionalidade;
    }
    
    public String getFotografia(){
        return fotografia;
    }
    
    public void setFotografia(String fotografia){
        this.fotografia = fotografia;
    }
    
    public String getGeneroLiterario(){
        return generoLiterario;
    }
    
    public void setGeneroLiterario(String generoLiterario){
        this.generoLiterario = generoLiterario;
    }
    
    public String getNascimento(){
        return nascimento;
    }
    
    public void setNascimento(String nascimento){
        this.nascimento = nascimento;
    }
    
    public String getMorte(){
        return morte;
    }
    
    public void setMorte(String morte){
        this.morte = morte;
    }
    
    public ArrayList<String> getPremios(){
        return premios;
    }
    
    public void setPremios(ArrayList<String> premios){
        this.premios = premios;
    }
    
    public ArrayList<String> getOcupacoes(){
        return ocupacoes;
    }
    
    public void setOcupacoes(ArrayList<String> ocupacoes){
        this.ocupacoes = ocupacoes;
    }
    
    public static Escritores criaEscritor(String escritor_) throws IOException{
        Escritores x;
        
        int id = 0;
        String nome = escritor_;
        String nacionalidade = Wrappers.obtemNacionalidade(escritor_);
        String fotografia = Wrappers.obtemFotografia(escritor_);
        String generoLiterario = Wrappers.obtemGeneroLiterario(escritor_);
        String nascimento = Wrappers.obtemNascimento(escritor_);
        String morte = Wrappers.obtemMorte(escritor_);
        ArrayList<String> premios = Wrappers.obtemPremios(escritor_);
        ArrayList<String> ocupacoes = Wrappers.obtemOcupacoes(escritor_);
        
        x = new Escritores(id++, nome, nacionalidade, fotografia, generoLiterario, nascimento, morte, premios, ocupacoes);
        
        return x;
    }
}
