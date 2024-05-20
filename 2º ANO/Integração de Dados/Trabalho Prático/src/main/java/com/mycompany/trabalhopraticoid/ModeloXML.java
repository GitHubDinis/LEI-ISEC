/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package com.mycompany.trabalhopraticoid;

import java.util.List;
import org.jdom2.Attribute;
import org.jdom2.Document;
import org.jdom2.Element;

/**
 *  Dinis Meireles de Sousa Falcão | 2020130403
 *  Telmo Eduardo Fonseca Silva | 2019127444
 */
public class ModeloXML {
    public static Document adicionaPais (Pais pais, Document doc){
        Element raiz;
        if(doc == null){
            raiz = new Element("paises");
            doc = new Document(raiz);
        } else{
            raiz = doc.getRootElement();
        }
        
        Element pai = new Element("pais");
        
        Attribute codigoISO = new Attribute("codigoISO", pais.getCodigoISO()); 
        pai.setAttribute(codigoISO);
        Attribute nome_pais = new Attribute("nome", pais.getNome()); 
        pai.setAttribute(nome_pais);
        
        Element nome = new Element("nome_oficial").addContent(pais.getNomeOficial());
        pai.addContent(nome);
        Element continente = new Element("continente").addContent(pais.getContinente());
        pai.addContent(continente);
        Element presidente = new Element("presidente").addContent(pais.getPresidente());
        pai.addContent(presidente);
        Element bandeira = new Element("bandeira").addContent(pais.getBandeira());
        pai.addContent(bandeira);
        
        raiz.addContent(pai);
        
        return doc;
    }
    
    public static Document adicionaFactos (Pais pais, Document doc){
        Element raiz;
        if(doc == null){
            raiz = new Element("factos");
            doc = new Document(raiz);
        } else{
            raiz = doc.getRootElement();
        }
        
        Element pai = new Element("pais");
        
        Attribute codigoISO = new Attribute("codigoISO", pais.getCodigoISO()); 
        pai.setAttribute(codigoISO);
        Attribute nome_pais = new Attribute("nome", pais.getNome()); 
        pai.setAttribute(nome_pais);
        
        Element nome_oficial = new Element("nome_oficial").addContent(pais.getNomeOficial());
        pai.addContent(nome_oficial);
        Element capital = new Element("capital").addContent(pais.getCapital());
        pai.addContent(capital);
        Element moeda = new Element("moeda").addContent(pais.getMoeda());
        pai.addContent(moeda);
        Element populacao = new Element("populacao").addContent(pais.getPopulacao());
        pai.addContent(populacao);
        Element area = new Element("area").addContent(pais.getArea());
        pai.addContent(area);
        Element crescimento = new Element("crescimento").addContent(pais.getCrescimentoPopulacao());
        pai.addContent(crescimento);
        Element cidades = new Element("cidades_mais_populosas");
        pai.addContent(cidades);
        for(int i = 0; i < pais.getCidades().size(); i++){
            Element cidade;
            cidade = new Element("cidade");
            cidade.addContent(pais.getCidades().get(i));
            cidades.addContent(cidade);
        }
        Element dominioInternet = new Element("dominioInternet").addContent(pais.getDominioInternet());
        pai.addContent(dominioInternet);
        Element idiomas_oficiais = new Element("idiomas_oficiais");
        pai.addContent(idiomas_oficiais);
        for(int i = 0; i < pais.getIdioma().size(); i++){
            Element idioma;
            idioma = new Element("idioma");
            idioma.addContent(pais.getIdioma().get(i));
            idiomas_oficiais.addContent(idioma);
        }
        Element paises_vizinhos = new Element("paises_vizinhos");
        pai.addContent(paises_vizinhos);
        for(int i = 0; i < pais.getPaisesVizinhos().size(); i++){
            Element paisV;
            paisV = new Element("pais_vizinho");
            paisV.addContent(pais.getPaisesVizinhos().get(i));
            paises_vizinhos.addContent(paisV);
        }
        
        raiz.addContent(pai);
        
        return doc;
    }
    
    public static Document removePais (String nome_pais, Document doc){
        Element raiz;
        if(doc == null){
            raiz = new Element("paises");
            doc = new Document(raiz);
        } else{
            raiz = doc.getRootElement();
        }
        
        List todos = raiz.getChildren("pais");
        
        boolean found = false;
        for(int i = 0; i < todos.size(); i++){
            Element p = (Element)todos.get(i); 
            if (p.getAttributeValue("nome").contains(nome_pais)) {
                p.getParent().removeContent(p);
                System.out.println("País removido com sucesso!");
                found = true;
            }
            
        }
        
        if(!found){
            System.out.println("País " + nome_pais + " não foi encontrado");
            return null;
        }
        
        return doc;
    }
    
    public static Document removeFactos (String nome_pais, Document doc){
        Element raiz;
        if(doc == null){
            raiz = new Element("factos");
            doc = new Document(raiz);
        } else{
            raiz = doc.getRootElement();
        }
        
        List todos = raiz.getChildren("pais");
        
        boolean found = false;
        for(int i = 0; i < todos.size(); i++){
            Element p = (Element)todos.get(i); 
            if (p.getAttributeValue("nome").contains(nome_pais)) {
                p.getParent().removeContent(p);
                System.out.println("Factos removido com sucesso!");
                found = true;
            }
            
        }
        
        if(!found){
            System.out.println("País " + nome_pais + " não foi encontrado");
            return null;
        }
        
        return doc;
    }
    
    public static Document alteraFacto (String nome_pais, String atributo, String novoAtributo, Document doc){
        Element raiz;
        if(doc == null){
            raiz = new Element("factos");
            doc = new Document(raiz);
        } else{
            raiz = doc.getRootElement();
        }
        
        List todos = raiz.getChildren("pais");
        
        boolean found = false;
        boolean found1 = false;
        for(int i = 0; i < todos.size(); i++){
            Element p = (Element)todos.get(i); 
            if (p.getAttributeValue("nome").contains(nome_pais)) {
                Element f = p.getChild(atributo);
                if(f != null){
                    f.setText(novoAtributo);
                    found1 = true;
                }
                found = true;
            }
        }
        
        if(!found){
            System.out.println("País " + nome_pais + " não foi encontrado");
            return null;
        } else if(!found1){
            System.out.println("Atributo " + atributo + " não foi encontrado");
            return null;
        }
        
        return doc;
    }
    
    
    public static Document adicionarFactoLista (String nome_pais, String lista, String novo_atributo, Document doc){
        Element raiz;
        if(doc == null){
            raiz = new Element("factos");
            doc = new Document(raiz);
        } else{
            raiz = doc.getRootElement();
        }
        
        List todos = raiz.getChildren("pais");
        
        String nome = null;
        
        if(null != lista)
            switch (lista) {
            case "cidades_mais_populosas":
                nome = "cidade";
                break;
            case "idiomas_oficiais":
                nome = "idioma";
                break;
            case "paises_vizinhos":
                nome = "pais_vizinho";
                break;
            default:
                break;
        }
        
        boolean found = false;
        boolean found1 = false;
        
        for(int i = 0; i < todos.size(); i++){
            Element p = (Element)todos.get(i); 
            if (p.getAttributeValue("nome").contains(nome_pais)) {
                Element f = p.getChild(lista);
                if(f != null){
                    Element g = new Element(nome);
                    g.addContent(novo_atributo);
                    f.addContent(g);
                    found1 = true;
                }
                found = true;
            }
            
        }
        
        if(!found){
            System.out.println("País " + nome_pais + " não foi encontrado");
            return null;
        }
        
        if(!found1){
            System.out.println("Lista " + lista + " não foi encontrada");
            return null;
        }
        
        return doc;
    }
            
    public static Document alterarFactoLista(String nome_pais, String lista, String atributo, String novo_atributo, Document doc){
        Element raiz;
        if(doc == null){
            raiz = new Element("factos");
            doc = new Document(raiz);
        } else{
            raiz = doc.getRootElement();
        }
        
        List todos = raiz.getChildren("pais");
        
        String nome = null;
        
        if(null != lista)
            switch (lista) {
            case "cidades_mais_populosas":
                nome = "cidade";
                break;
            case "idiomas_oficiais":
                nome = "idioma";
                break;
            case "paises_vizinhos":
                nome = "pais_vizinho";
                break;
            default:
                break;
        }
        
        boolean found = false;
        boolean found1 = false;
        
        for(int i = 0; i < todos.size(); i++){
            Element p = (Element)todos.get(i); 
            if (p.getAttributeValue("nome").contains(nome_pais)) {
                Element f = p.getChild(lista);
                if(f != null){
                    List<Element> listaDe = f.getChildren(nome);
                    for(Element s : listaDe){
                        if(s.getText().equals(atributo)){
                            s.setText(novo_atributo);
                            found1 = true;
                        }
                    }
                }
                found = true;
            }
            
        }
        
        if(!found){
            System.out.println("País " + nome_pais + " não foi encontrado");
            return null;
        }
        
        if(!found1){
            System.out.println("Lista " + lista + " não foi encontrada");
            return null;
        }
        
        return doc;
    }
    
}
