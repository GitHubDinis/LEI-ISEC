/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 */

package com.mycompany.workid;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Scanner;
import net.sf.saxon.s9api.SaxonApiException;
import org.jdom2.Document;

/**
 *
 * @author Utilizador
 */
public class WorkID {

    public static void main(String[] args) throws IOException, SaxonApiException {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Digite o nome do autor: ");
        String nomeAutor = scanner.nextLine();

        //System.out.println("O autor digitado foi: " + nomeAutor);
        
        //Wrappers.obtemISBN(nomeAutor);
        
        String devolveLinkWiki = Wrappers.obtemLinkWikipedia(nomeAutor);
        System.out.println("Link wikipedia: " + devolveLinkWiki);
        //String devolveLinkWook = Wrappers.obtemLinkWook(nomeAutor);
        //System.out.println("Link wook: " + devolveLinkWook);
        String nacionalidade = Wrappers.obtemNacionalidade(nomeAutor);
        System.out.println("Nacionalidade: " + nacionalidade);
        String fotografia = Wrappers.obtemFotografia(nomeAutor);
        System.out.println("Fotografia: " + fotografia);
        String genero = Wrappers.obtemGeneroLiterario(nomeAutor);
        System.out.println("Género Literário: " + genero);
        String nascimento = Wrappers.obtemNascimento(nomeAutor);
        System.out.println("Nascimento: " + nascimento);
        String morte = Wrappers.obtemMorte(nomeAutor);
        System.out.println("Morte: " + morte);     
        ArrayList<String> premios = new ArrayList();
        premios = Wrappers.obtemPremios(nomeAutor);
        for (String l : premios) 
            System.out.print(l + " ; "); 
        System.out.println("");
        ArrayList<String> ocupacoes = new ArrayList();
        ocupacoes = Wrappers.obtemOcupacoes(nomeAutor);
        for (String l : ocupacoes) 
            System.out.print(l + " ; "); 
        System.out.println("");
        
        Escritores x = Escritores.criaEscritor(nomeAutor);
        System.out.println("Nome: " + x.getNome());
        System.out.println("Nacionalidade: " + x.getNacionalidade());
        System.out.println("Fotografia: " + x.getFotografia());
        System.out.println("Género Literário: " + x.getGeneroLiterario()); 
        System.out.println("Nascimento: " + x.getNascimento());
        System.out.println("Morte: " + x.getMorte());
        System.out.println("Premios: " + x.getPremios());
        System.out.println("Ocupações: " + x.getOcupacoes()); 
        System.out.println("ID: " + x.getID());
         
        //Inicializa Doc XML
        Document doc = XMLJDomFunctions.lerDocumentoXML("escritores.xml");
        //Chama a função para adicionar o cidade ao XML
        doc = ModeloXML.adicionaEscritor(x, doc);
        doc = ModeloXML.removeEscritor("Oscar Wilde", doc);
        doc = ModeloXML.alteraNacionalidade(" ", "portuguesa", doc);
        
        //grava o ficheiro XML em disco

        if(doc!=null){
            XMLJDomFunctions.escreverDocumentoParaFicheiro(doc, "escritores.xml");
        }
        
        Frame app = new Frame();
        app.setVisible(true);
    }
}
