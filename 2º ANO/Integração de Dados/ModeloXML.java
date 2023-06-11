/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package com.mycompany.workid;

import static java.lang.String.valueOf;
import java.util.ArrayList;
import java.util.List;
import net.sf.saxon.s9api.SaxonApiException;
import net.sf.saxon.s9api.XdmValue;
import org.jdom2.Document;
import org.jdom2.Element;

/**
 *
 * @author Utilizador
 */
public class ModeloXML {
    public static Document adicionaEscritor(Escritores esc, Document doc) throws SaxonApiException{
        Element raiz;
        
        if (doc == null) {
            raiz = new Element("catalogo"); //cria <catalogo>...</catalogo>
            doc = new Document(raiz);
        } else {
            raiz = doc.getRootElement();
            String xp = "//escritor[contains(nome,'" + esc.getNome() + "')]";
            //System.out.println(xp);
            XdmValue res = XPathFunctions.executaXpath(xp, "escritores.xml");
            if (res != null && res.size() > 0) {
                System.out.println("Escritor já existe");
                return null;
            } else {
                Element escritor = new Element("escritor");
                String nome = esc.getNome();
                if (nome != null) {
                    Element folha = new Element("nome").addContent(nome);
                    escritor.addContent(folha);
                }
                String nascimento = esc.getNascimento();
                if (nascimento != null) {
                    Element folha = new Element("bandeirapais").addContent(nascimento);
                    escritor.addContent(folha);
                }
                String morte = esc.getMorte();
                if (morte != null) {
                    Element folha = new Element("bandeiracidade").addContent(morte);
                    escritor.addContent(folha);
                }                   
                String nacionalidade = esc.getNacionalidade();
                if (nacionalidade != null) {
                    Element folha = new Element("presidente").addContent(nacionalidade);
                    escritor.addContent(folha);
                }
                String generoLiterario = esc.getGeneroLiterario();
                if (generoLiterario != null) {
                    Element folha = new Element("clima").addContent(generoLiterario);
                    escritor.addContent(folha);
                }
                String foto = esc.getFotografia();
                if (foto != null) {
                    Element folha = new Element("fuso").addContent(foto);
                    escritor.addContent(folha);
                }
                Element premio = new Element("premios");
                ArrayList<String> premios = esc.getPremios();
                if (premios.size() != 0) {
                    for (int i = 0; i < premios.size(); i++) {
                        Element folha = new Element("premio").addContent(premios.get(i));
                        premio.addContent(folha);
                    }
                }
                escritor.addContent(premio);         
                Element ocupacao = new Element("ocupacao");
                ArrayList<String> ocupacoes = esc.getOcupacoes();
                if (ocupacoes.size() != 0) {
                        for (int i = 0; i < ocupacoes.size(); i++) {
                            Element folha = new Element("monumento").addContent(ocupacoes.get(i));
                            ocupacao.addContent(folha);
                        }
                }
                escritor.addContent(ocupacao);
                return doc;
                    
                }
        }
        return doc;
    }
    
    public static Document removeEscritor(String nome, Document doc) {
        Element raiz;
        if (doc == null) {
            System.out.println("Não existe nenhum ficheiro");
            return null;
        } else {
            raiz = doc.getRootElement();
            boolean found = false;
            List todosEscritores = raiz.getChildren("escritor");
            for (int i = 0; i < todosEscritores.size(); i++) {
                Element escritor = (Element) todosEscritores.get(i);
                if (escritor.getChild("nome").getText().contains(nome)) {
                    escritor.getParent().removeContent(escritor);
                    found = true;
                }
            }
            if (!found) {               
                return null;
            }
        }
        return doc;
    }
    
    public static Document alteraNascimento(String nome, String nascimento, Document doc) {
        Element raiz;
        if (doc == null) {
            System.out.println("Ficheiro nao existe - nao dá para alterar informação");
            return null;
        } else {
            raiz = doc.getRootElement();
        }
        List todosEscritores = raiz.getChildren("escritor");
        boolean found = false;
        for (int i = 0; i < todosEscritores.size(); i++) {
            Element escritor = (Element) todosEscritores.get(i); 
            if (escritor.getChild("nome").getText().contains(nome)) {                
                escritor.getChild("nascimento").setText(String.valueOf(nascimento));
                found = true;
            }
        }
        if (!found) {
            System.out.println("Escritor " + nome + " não encontrado");
            return null;
        }
        return doc;
    }
    
    public static Document alteraNacionalidade(String nome, String nacionalidade, Document doc) {
        Element raiz;
        if (doc == null) {
            System.out.println("Ficheiro nao existe - nao dá para alterar informação");
            return null;
        } else {
            raiz = doc.getRootElement();
        }
        List todosEscritores = raiz.getChildren("escritor");
        boolean found = false;
        for (int i = 0; i < todosEscritores.size(); i++) {
            Element escritor = (Element) todosEscritores.get(i); 
            if (escritor.getChild("nome").getText().contains(nome)) {                
                escritor.getChild("nacionalidade").setText(String.valueOf(nacionalidade));
                found = true;
            }
        }
        if (!found) {
            System.out.println("Escritor " + nome + " não encontrado");
            return null;
        }
        return doc;
    }
}
