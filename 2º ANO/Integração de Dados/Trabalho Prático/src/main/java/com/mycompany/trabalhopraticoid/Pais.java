/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package com.mycompany.trabalhopraticoid;

import java.io.IOException;
import java.util.ArrayList;
import net.sf.saxon.s9api.SaxonApiException;
import net.sf.saxon.s9api.XdmValue;

/**
 *  Dinis Meireles de Sousa Falcão | 2020130403
 *  Telmo Eduardo Fonseca Silva | 2019127444
 */

public class Pais {
    String codigoISO;
    String nome;
    String nome_oficial;
    String continente;
    String presidente;
    String bandeira;
    
    String capital;
    String moeda;
    String populacao;
    String area;
    String crescimentoPopulacao;
    ArrayList<String> cidades;
    String dominioInternet;
    ArrayList<String> idioma;
    ArrayList<String> paisesVizinhos;

    public Pais(String codigoISO, String nome, String nome_oficial, String continente, String presidente, String bandeira, String capital, String moeda, String populacao, String area, String crescimentoPopulacao, ArrayList<String> cidades, String dominioInternet, ArrayList<String> idioma, ArrayList<String> paisesVizinhos) {
        this.codigoISO = codigoISO;
        this.nome = nome;
        this.nome_oficial = nome_oficial;
        this.continente = continente;
        this.presidente = presidente;
        this.bandeira = bandeira;
        this.capital = capital;
        this.moeda = moeda;
        this.populacao = populacao;
        this.area = area;
        this.crescimentoPopulacao = crescimentoPopulacao;
        this.cidades = cidades;
        this.dominioInternet = dominioInternet;
        this.idioma = idioma;
        this.paisesVizinhos = paisesVizinhos;
    }
    
    

    public String getCodigoISO() {
        return codigoISO;
    }

    public void setCodigoISO(String codigoISO) {
        this.codigoISO = codigoISO;
    }

    public String getNome() {
        return nome;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }
   
    public String getNomeOficial() {
        return nome_oficial;
    }

    public void setNomeOficial(String nome_oficial) {
        this.nome_oficial = nome_oficial;
    }

    public String getContinente() {
        return continente;
    }

    public void setContinente(String continente) {
        this.continente = continente;
    }

    public String getPresidente() {
        return presidente;
    }

    public void setPresidente(String presidente) {
        this.presidente = presidente;
    }

    public String getBandeira() {
        return bandeira;
    }

    public void setBandeira(String bandeira) {
        this.bandeira = bandeira;
    }

    public String getCapital() {
        return capital;
    }

    public void setCapital(String capital) {
        this.capital = capital;
    }

    public String getMoeda() {
        return moeda;
    }

    public void setMoeda(String moeda) {
        this.moeda = moeda;
    }

    public String getPopulacao() {
        return populacao;
    }

    public void setPopulacao(String populacao) {
        this.populacao = populacao;
    }

    public String getArea() {
        return area;
    }

    public void setArea(String area) {
        this.area = area;
    }

    public String getCrescimentoPopulacao() {
        return crescimentoPopulacao;
    }

    public void setCrescimentoPopulacao(String crescimentoPopulacao) {
        this.crescimentoPopulacao = crescimentoPopulacao;
    }

    public ArrayList<String> getCidades() {
        return cidades;
    }

    public void setCidades(ArrayList<String> cidades) {
        this.cidades = cidades;
    }

    public String getDominioInternet() {
        return dominioInternet;
    }

    public void setDominioInternet(String dominioInternet) {
        this.dominioInternet = dominioInternet;
    }

    public ArrayList<String> getIdioma() {
        return idioma;
    }

    public void setIdioma(ArrayList<String> idioma) {
        this.idioma = idioma;
    }

    public ArrayList<String> getPaisesVizinhos() {
        return paisesVizinhos;
    }

    public void setPaisesVizinhos(ArrayList<String> paisesVizinhos) {
        this.paisesVizinhos = paisesVizinhos;
    }
    
    
    
    public void imprime(){
        System.out.println("Codigo ISO: " + this.codigoISO);
        System.out.println("Nome: " + this.nome);
        System.out.println("Nome Oficial: " + this.nome_oficial);
        System.out.println("Continente: " + this.continente);
        System.out.println("Presidente: " + this.presidente);
        System.out.println("Bandeira: " + this.bandeira);
    }
    
    public static Pais criaPais (String nome_pais) throws IOException, SaxonApiException{
        String xp = "//pais[@nome='" + nome_pais + "']";
        XdmValue res = null;
        res = XPathFunctions.executaXpath(xp, "paises.xml");
        if (res == null || res.size() == 0) {
            String codigoISO = Wrappers.obtemCodigoISO(nome_pais);
            String nome = Wrappers.obtemNome(nome_pais);
            String nome_oficial = Wrappers.obtemNomeOficialPais(nome_pais);
            String continente = Wrappers.obtemContinente(nome_pais);
            String presidente = Wrappers.obtemPresidente(nome_pais);
            String bandeira = Wrappers.obtemBandeira(nome_pais);
            
            String capital = Wrappers.obtemCapital(nome_pais);
            String moeda = Wrappers.obtemMoeda(nome_pais);
            String populacao = Wrappers.obtemPopulacao(nome_pais);
            String area = Wrappers.obtemArea(nome_pais);
            String crescimentoPopulacao = Wrappers.obtemCrescimentoPopulacao(nome_pais);
            ArrayList<String> cidades = Wrappers.obtemCidadesMaisPopulosas(nome_pais);
            String dominioInternet = Wrappers.obtemDominioInternet(nome_pais);
            ArrayList<String> idioma = Wrappers.obtemIdiomaOficial(nome_pais);
            ArrayList<String> paisesVizinhos = Wrappers.obtemPaisesVizinhos(nome_pais);
            
            Pais novo = new Pais(codigoISO, nome, nome_oficial, continente, presidente, bandeira, capital, moeda, populacao, area, crescimentoPopulacao, cidades, dominioInternet, idioma, paisesVizinhos);
        
            return novo;  
        }
        
        return null;
    }
}
