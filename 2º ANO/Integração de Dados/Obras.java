/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package com.mycompany.workid;

import java.io.IOException;

/**
 *
 * @author Utilizador
 */
public class Obras {
    int codigoAutor;
    String nomeAutor, titulo, editora, fotoCapa, isbn;
    double preco;
    
    public Obras(String isbn, int codigoAutor, String nomeAutor, String titulo, String editora, String fotoCapa, double preco) {
        this.isbn = isbn;
        this.codigoAutor = codigoAutor;
        this.nomeAutor = nomeAutor;
        this.titulo = titulo;
        this.editora = editora;
        this.fotoCapa = fotoCapa;
        this.preco = preco;         
    }
    
    public String getISBN(){
        return isbn;
    }
    
    public void setISBN(String isbn){
        this.isbn = isbn;
    }
    
    public int getCodigoAutor(){
        return codigoAutor;
    }
    
    public void setCodigoAutor(int codigoAutor){
        this.codigoAutor = codigoAutor;
    }
    
    public String getNomeAutor(){
        return nomeAutor;
    }
    
    public void setNomeAutor(String nomeAutor){
        this.nomeAutor = nomeAutor;
    }
    
    public String getTitulo(){
        return titulo;
    }
    
    public void setTitutlo(String titulo){
        this.titulo = titulo;
    }
    
    public String getEditora(){
        return editora;
    }
    
    public void setEditora(String editora){
        this.editora = editora;
    }
    
    public String getFotoCapa(){
        return fotoCapa;
    }
    
    public void setFotoCapa(String fotoCapa){
        this.fotoCapa = fotoCapa;
    }
    
    public double getPreco(){
        return preco;
    }
    
    public void setPreco(double preco){
        this.preco = preco;
    }
    
    public static Obras criaObra(String isbn) throws IOException{
        Obras x;
        Escritores y = null;
        
        String titulo = Wrappers.obtem_titulo(isbn);
        String editora = Wrappers.obtem_capa(isbn);
        String fotoCapa = Wrappers.obtem_capa(isbn);
        double preco = Wrappers.obtem_preco(isbn);
        
        x = new Obras(isbn, y.getID(), y.getNome(), titulo, editora, fotoCapa, preco);
        
        return x;
    }
}   
