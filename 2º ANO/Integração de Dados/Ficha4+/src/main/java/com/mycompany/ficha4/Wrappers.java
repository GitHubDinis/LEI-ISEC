/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package com.mycompany.ficha4;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Scanner;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 *  Dinis Meireles de Sousa Falcão | 2020130403
 * 
 */
public class Wrappers {
    public static String obtem_nome_completo(String escritor) throws IOException{
        String nome_completo = null;
        
        String link = "https://pt.wikipedia.org/wiki/";
        HttpRequestFunctions.httpRequest1(link, escritor, "escritor.html");
        
        String er1 = "Nome completo";
        String er2 = "left;\">([a-zA-Z\\sóéçõãáí]+)";
        String linha;
        Scanner input = new Scanner(new FileInputStream("escritor.html"));
        
        Pattern p1 = Pattern.compile(er1);
        Pattern p2 = Pattern.compile(er2);
        Matcher m1, m2;
        
        while ((input.hasNextLine())) {
            linha = input.nextLine();
            m1 = p1.matcher(linha);
            if(m1.find()){
                input.nextLine(); // avançar <td> lixo
                linha = input.nextLine();
                m2 = p2.matcher(linha);
                if(m2.find()){
                    input.close();
                    nome_completo = m2.group(1);
                    return nome_completo;
                }
            }
        }
        input.close();
        
        return nome_completo;
    }
    
    public static String obtem_nacionalidade(String escritor) throws IOException{
        String nacionalidade = null;
        
        String link = "https://pt.wikipedia.org/wiki/";
        HttpRequestFunctions.httpRequest1(link, escritor, "escritor.html");
        
        String er1 = "Nacionalidade";
        String er2 = "<a href=\"/wiki/[a-zA-Z]+\" title=\"[a-zA-Z]+\">([^<]+)</a>";
        String linha;
        Scanner input = new Scanner(new FileInputStream("escritor.html"));
        
        Pattern p1 = Pattern.compile(er1);
        Pattern p2 = Pattern.compile(er2);
        Matcher m1, m2;
        
        while ((input.hasNextLine())) {
            linha = input.nextLine();
            m1 = p1.matcher(linha);
            if(m1.find()){
                input.nextLine(); // avançar </td> lixo
                linha = input.nextLine();
                m2 = p2.matcher(linha);
                if(m2.find()){
                    input.close();
                    nacionalidade = m2.group(1);
                    return nacionalidade;
                }
            }
        }
        input.close();
        
        return nacionalidade;
    }
    
    public static String obtem_dnascimento(String escritor) throws IOException{
        String nascimento = null;
        String link = "https://pt.wikipedia.org/wiki/";
        HttpRequestFunctions.httpRequest1(link, escritor, "escritor.html");
        
        String er1 = "Nascimento";
        String er2 = "\">([^<]+)<br />";
        String er3 = ">([^<]+)</a>( de )<a href=\"/wiki/[0-9]+\" title=\"[0-9]+\">([0-9]+)</a>";
        String linha;
        Scanner input = new Scanner(new FileInputStream("escritor.html"));
        
        Pattern p1 = Pattern.compile(er1);
        Pattern p2 = Pattern.compile(er2);
        Pattern p3 = Pattern.compile(er3);
        Matcher m1, m2, m3;
        
        while ((input.hasNextLine())) {
            linha = input.nextLine();
            m1 = p1.matcher(linha);
            if(m1.find()){
                input.nextLine(); // avançar </td> lixo
                linha = input.nextLine();
                m2 = p2.matcher(linha);
                if(m2.find()){
                    input.close();
                    nascimento = m2.group(1);
                    return nascimento;
                } else{
                    m3 = p3.matcher(linha);
                    if(m3.find()){
                        input.close();
                        nascimento = m3.group(1) + m3.group(2) + m3.group(3);
                        return nascimento;
                    }
                }
            }
        }     
        input.close();
        
        return nascimento;
    }
    
    public static String obtem_fotografia(String escritor) throws FileNotFoundException, IOException{
        String fotografia = null;
        
        String link = "https://pt.wikipedia.org/wiki/";
        HttpRequestFunctions.httpRequest1(link, escritor, "escritor.html");
        
        String er = "<meta property=\"og:image\" content=\"(https://upload.wikimedia.org/wikipedia/commons/[^/]+/[^/]+/[^.]+.jpg)\">";
        String linha;
        Scanner input = new Scanner(new FileInputStream("escritor.html"));
        
        while ((input.hasNextLine())) {
           linha = input.nextLine(); //lê linha a linha
           Pattern p = Pattern.compile(er);
           Matcher m = p.matcher(linha);
           if(m.find()){
               fotografia = m.group(1);
           }
       }
       input.close();
        
       return fotografia;
    }
    
    public static ArrayList<String> obtem_ocupacoes(String escritor) throws FileNotFoundException, IOException{
        ArrayList ocupacoes = new ArrayList();
        
        String link = "https://pt.wikipedia.org/wiki/";
        HttpRequestFunctions.httpRequest1(link, escritor, "escritor.html");
        
        String er1 = "Ocupação";
        String er2 = "title=\"[a-zA-Z]+\">([^<]+)</a>";
        String linha;
        Scanner input = new Scanner(new FileInputStream("escritor.html"));
        
        Pattern p1 = Pattern.compile(er1);
        Pattern p2 = Pattern.compile(er2);
        Matcher m1, m2;

        while ((input.hasNextLine())) {
            linha = input.nextLine();
            m1 = p1.matcher(linha);
            if(m1.find()){
                input.nextLine(); // avançar </td> lixo
                linha = input.nextLine();
                m2 = p2.matcher(linha);
                while(m2.find()){
                    ocupacoes.add(m2.group(1));                  
                }
                linha = input.nextLine();
                m2 = p2.matcher(linha);
                while(m2.find()){
                    ocupacoes.add(m2.group(1));                  
                }
                linha = input.nextLine();
                m2 = p2.matcher(linha);
                while(m2.find()){
                    ocupacoes.add(m2.group(1));                  
                }
                linha = input.nextLine();
                m2 = p2.matcher(linha);
                while(m2.find()){
                    ocupacoes.add(m2.group(1));                  
                }
                linha = input.nextLine();
                m2 = p2.matcher(linha);
                while(m2.find()){
                    ocupacoes.add(m2.group(1));                  
                }
            }
        }
        
        input.close();
        
        return ocupacoes;
    }
    
    public static ArrayList<String> obtem_ocupacoes2(String escritor) throws IOException{
        ArrayList ocupacoes = new ArrayList();
        
        String link = "https://pt.wikipedia.org/wiki/";
        HttpRequestFunctions.httpRequest1(link, escritor, "escritor.html");
        
        String er1 = "Ocupação";
        String er2 = "title=\"[a-zA-Z]+\">([^<]+)</a>";
        String er3 = "<ul><li>";
        String linha;
        Scanner input = new Scanner(new FileInputStream("escritor.html"));
        
        Pattern p1 = Pattern.compile(er1);
        Pattern p2 = Pattern.compile(er2);
        Pattern p3 = Pattern.compile(er3);
        Matcher m1, m2, m3;
        
        while (input.hasNextLine()) {
            linha = input.nextLine();
            m1 = p1.matcher(linha);
            if (m1.find()) {
                do{
                   linha = input.nextLine();
                   m3 = p3.matcher(linha);
                }while(!m3.find());
                //linha = ler.nextLine();
                m2 = p2.matcher(linha);
                while (m2.find()) {
                    ocupacoes.add(m2.group(1));
                    linha = input.nextLine();
                    m2 = p2.matcher(linha);
                }
            }
        }
        
        input.close();
        
        return ocupacoes;
    }
}
