/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package com.mycompany.ficha3;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Scanner;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 *
 * @author Utilizador
 */
public class Wrappers {
    static String procura_por_id(String procura) throws FileNotFoundException, IOException{
        String link = "https://eden.dei.uc.pt/~abs/ID/pessoas.html";
        String pesquisa = "";
        HttpRequestFunctions.httpRequest1(link, pesquisa, "pessoas.html");
        
        String nome = null;
        String er = "<tr>\\s*<td\\s*>" + procura + "</td><td\\s*>([a-zA-Z\\s]+)</td>";
        String linha;
        Scanner input = new Scanner(new FileInputStream("pessoas.html"));
        
        while ((input.hasNextLine())) {
           linha = input.nextLine(); //lê linha a linha
           Pattern p = Pattern.compile(er);
           Matcher m = p.matcher(linha);
           if(m.find()){
               nome = m.group(1);
           }
       }
       input.close();
        
       return nome;
    }
    
    static String procura_cidade_por_id(String procura) throws FileNotFoundException, IOException{
        String link = "https://eden.dei.uc.pt/~abs/ID/pessoas.html";
        String pesquisa = "";
        HttpRequestFunctions.httpRequest1(link, pesquisa, "pessoas.html");
        
        
        String cidade = null;
        String er = "<tr>\\s*<td\\s*>" + procura + "</td><td\\s*>([a-zA-Z\\s]+)*</td><td>([0-9]+)*</td><td>([a-zA-Z\\s]+)(, [a-zA-Z\\s]+)*</td>";
        // String er = "<tr>\\s*<td\\s*>" + procura + "</td><td\\s*>[a-zA-Z\\s]+</td><td>[0-9]+</td><td>([a-zA-Z\\s,]+)</td>";
        String linha;
        Scanner input = new Scanner(new FileInputStream("pessoas.html"));
        
        while ((input.hasNextLine())) {
           linha = input.nextLine(); //lê linha a linha
           Pattern p = Pattern.compile(er);
           Matcher m = p.matcher(linha);
           if(m.find()){
               cidade = m.group(3);
               if(m.group(4) != null){
                   cidade = cidade + m.group(4);
               }
               //cidade = m.group();
           }
       }
       input.close();
        
       return cidade;
    }
    
    static String procura_profissao_por_id(String procura) throws FileNotFoundException, IOException{
        String link = "https://eden.dei.uc.pt/~abs/ID/pessoas.html";
        String pesquisa = "";
        HttpRequestFunctions.httpRequest1(link, pesquisa, "pessoas.html");
        
        
        String profissao = null;
        String er = "<tr>\\s*<td\\s*>" + procura + "</td><td\\s*>[a-zA-Z\\s]+</td><td>[0-9]+</td><td>[a-zA-Z\\s,]+</td><td>([a-zA-Z\\s]+)</td></tr>";
        String linha;
        Scanner input = new Scanner(new FileInputStream("pessoas.html"));
        
        while ((input.hasNextLine())) {
           linha = input.nextLine(); //lê linha a linha
           Pattern p = Pattern.compile(er);
           Matcher m = p.matcher(linha);
           if(m.find()){
               profissao = m.group(1);
           }
       }
       input.close();
        
       return profissao;
    }
    
    static ArrayList procura_nomes(String procura) throws FileNotFoundException, IOException{
        String link = "https://eden.dei.uc.pt/~abs/ID/pessoas.html";
        String pesquisa = "";
        HttpRequestFunctions.httpRequest1(link, pesquisa, "pessoas.html");
        
        
        ArrayList nomes = new ArrayList();
        
        String er = "(?i)<tr>\\s*<td\\s*>[0-9]+</td><td\\s*>([a-zA-Z\\s]*"+ procura +"[a-zA-Z\\s]*)</td>";
        String linha;
        Scanner input = new Scanner(new FileInputStream("pessoas.html"));

        while ((input.hasNextLine())) {
           linha = input.nextLine(); //lê linha a linha
           Pattern p = Pattern.compile(er);
           Matcher m = p.matcher(linha);
           if(m.find()){
               nomes.add(m.group(1));
           }
       }
       input.close();
        
       return nomes;
    }
}
