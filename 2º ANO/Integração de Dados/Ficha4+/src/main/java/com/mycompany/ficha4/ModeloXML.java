/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package com.mycompany.ficha4;

import java.util.List;
import org.jdom2.Attribute;
import org.jdom2.Document;
import org.jdom2.Element;

/**
 *
 * @author Utilizador
 */
public class ModeloXML {
    public static Document adicionaEscritor (Escritor escritor, Document doc){
        Element raiz;
        if(doc == null){
            raiz = new Element("lista");
            doc = new Document(raiz);
        } else{
            raiz = doc.getRootElement();
        }
        
        Element pai = new Element("escritor");
        
        Attribute nome = new Attribute("nome", escritor.getNome());
        pai.setAttribute(nome);
      
        Element nome_completo = new Element("nome_completo").addContent(escritor.getNome_completo());
        pai.addContent(nome_completo);
        Element nacionalidade = new Element("nacionalidade").addContent(escritor.getNacionalidade());
        pai.addContent(nacionalidade);
        Element nascimento = new Element("nascimento").addContent(escritor.getNascimento());
        pai.addContent(nascimento);
        Element fotografia = new Element("fotografia").addContent(escritor.getFotografia());
        pai.addContent(fotografia);
        Element ocupacoes = new Element("ocupacoes");
        pai.addContent(ocupacoes);
        
        for(int i = 0; i < escritor.getOcupacoes().size(); i++){
            Element ocupacao;
            ocupacao = new Element("ocupacao");
            ocupacao.addContent(escritor.getOcupacoes().get(i));
            ocupacoes.addContent(ocupacao);
        }
        
        raiz.addContent(pai);
        return doc;
    }
    
    public static Document removeEscritor (String procura, Document doc){
        Element raiz;
        if(doc == null){
            raiz = new Element("lista");
            doc = new Document(raiz);
        } else{
            raiz = doc.getRootElement();
        }
        
        List todos = raiz.getChildren("escritor");
        
        boolean found = false;
        for(int i=0; i<todos.size();i++){
            Element esc = (Element)todos.get(i); 
            if (esc.getAttributeValue("nome").contains(procura)) {
                esc.getParent().removeContent(esc);
                System.out.println("Escritor removido com sucesso!");
                found = true;
            }
        }
        
        if(!found){
            System.out.println("Escritor " + procura + " não foi encontrado");
            return null;
        }
        
        return doc;
    }
    
    public static Document removeOcupacao(String escritor, String ocupacao, Document doc){
        Element raiz;
        if(doc == null){
            raiz = new Element("lista");
            doc = new Document(raiz);
        } else{
            raiz = doc.getRootElement();
        }
        
        List todos = raiz.getChildren("escritor");
        
        boolean found = false;
        boolean found1 = false;
        for (int i = 0; i < todos.size(); i++) {
            Element esc = (Element) todos.get(i); 
            if (esc.getAttributeValue("nome").contains(escritor)) {
                Element ocup = esc.getChild("ocupacoes");
                List lista_oc = ocup.getChildren("ocupacao");
                found1 = true;
                for (int j = 0; j < lista_oc.size(); j++) {
                    Element o = (Element) lista_oc.get(j);
                    if(o.getText().equals(ocupacao)){
                        o.getParent().removeContent(o);
                        System.out.println("Ocupação removida com sucesso!");
                        found = true;
                    }
                }
            }
        }
        
        if(!found1){
            System.out.println("Escritor " + escritor + " não foi encontrado");
            return null;
        }
        
        if(!found){
            System.out.println("Ocupação " + ocupacao + " não foi encontrada");
            return null;
        }
        
        return doc;
    }
    
    public static Document alteraNacionalidade (String nome, String novaNac, Document doc){
        Element raiz;
        if(doc == null){
            raiz = new Element("lista");
            doc = new Document(raiz);
        } else{
            raiz = doc.getRootElement();
        }
        
            List todos = raiz.getChildren("escritor");

            boolean found = false;
            for(int i=0; i<todos.size();i++){
                Element esc = (Element)todos.get(i); 
                if (esc.getAttributeValue("nome").contains(nome)) {
                    System.out.println("Escritor " + nome + " encontrado");
                    found = true;
                    Element nac = esc.getChild("nacionalidade");
                    System.out.println("Nacionalidade " + nac.getName() + " encontrado");
                    nac.setText(novaNac);
                }
            }
        
            if(!found){
                System.out.println("Escritor " + nome + " não foi encontrado");
                return null;
            }
        
        return doc;
    }
}
