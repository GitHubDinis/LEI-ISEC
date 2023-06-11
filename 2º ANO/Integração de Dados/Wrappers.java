/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package com.mycompany.workid;

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
    public static String obtemLinkWook(String escritor) throws FileNotFoundException, IOException{
        HttpRequestFunctions.httpRequest1("https://www.wook.pt/", escritor, "escritor.txt");
        try (Scanner ler = new Scanner(new FileInputStream("escritor.txt"))) {
            String er = "href = \"//[A-Za-z-ç]+--[A-Za-z-Ø]+[^\"]+)\" title=\"" + escritor + "\">" + escritor + "</a>";
            Pattern p = Pattern.compile(er);
            while(ler.hasNextLine()){
                String linha = ler.nextLine();
                Matcher m = p.matcher(linha);
                if(m.find()){
                    String link = " https://pt.wikipedia.org/wiki/" + m.group(1);
                    ler.close();
                    return link;
                }
            }
        }
        return null;
    }
    
    public static String obtemLinkWikipedia(String escritor) throws FileNotFoundException, IOException{
        HttpRequestFunctions.httpRequest1("https://pt.wikipedia.org/wiki/", escritor, "escritor.txt");
        try (Scanner ler = new Scanner(new FileInputStream("escritor.txt"))) {
            String er ="\\\"wgPageName\\\":\\\"([A-Za-z-_]+)\\\"";
            Pattern p = Pattern.compile(er);
            while (ler.hasNextLine()) {
                String linha = ler.nextLine();
                Matcher m = p.matcher(linha);
                if (m.find()) {
                    String link = "https://pt.wikipedia.org/wiki/" + m.group(1);
                    ler.close();
                    return link;
                }
            }
        } 
        return null;
    }
    
    public static String obtemNacionalidade(String escritor) throws IOException{
        String link = obtemLinkWikipedia(escritor);
        HttpRequestFunctions.httpRequest1(link, "", "escritor1.txt");
        try (Scanner ler = new Scanner(new FileInputStream("escritor1.txt"))) {
            String er = "<td style=\"vertical-align: top; text-align: left;\"><a[^>]+>([^<]+)</a>";
            Pattern p = Pattern.compile(er);
            while(ler.hasNextLine()){
                String linha = ler.nextLine();
                Matcher m = p.matcher(linha);
                if(m.find()){
                    ler.close();
                    return m.group(1);
                }
            }
        }
        return null;
    }
    
    public static String obtemFotografia(String escritor) throws IOException{
        String link = obtemLinkWikipedia(escritor);
        HttpRequestFunctions.httpRequest1(link, "", "escritor1.txt");
        try (Scanner ler = new Scanner(new FileInputStream("escritor1.txt"))) {
            String er = "<a href=\"/wiki/Ficheiro:([^\\/]+)\" class=\"image\" title=\"[^\"]+\"><img alt=\"\" src=\"\\/\\/upload\\.wikimedia\\.org\\/wikipedia\\/commons\\/thumb\\/([^\\/]+\\/[^\"]+)\"";
            Pattern p = Pattern.compile(er);
            while(ler.hasNextLine()){
                String linha = ler.nextLine();
                Matcher m = p.matcher(linha);
                if(m.find()){
                    String linkFotografia = "https:" + m.group(1);
                    ler.close();
                    return linkFotografia;
                }
            }
        }
        return null;
    }
    
    public static String obtemGeneroLiterario(String escritor) throws IOException{
        HttpRequestFunctions.httpRequest1("https://pt.wikipedia.org/wiki/", "", "escritor1.txt");
        try (Scanner ler = new Scanner(new FileInputStream("escritor1.txt"))) {
            String er = "<td scope=\"row\" style=\"vertical-align: top; text-align: left; font-weight:bold;\">Género literário</td>\\s*<td style=\"vertical-align: top; text-align: left;\"><a[^>]+>([^<]+)</a>";
            Pattern p = Pattern.compile(er);
            while(ler.hasNextLine()){
                String linha = ler.nextLine();
                Matcher m = p.matcher(linha);
                if(m.find()){
                    ler.close();
                    return m.group(1);
                }
            }
        }
        return null;
    }
    
    public static String obtemNascimento(String escritor) throws IOException{
        HttpRequestFunctions.httpRequest1("https://pt.wikipedia.org/wiki/", "", "escritor1.txt");
        try (Scanner ler = new Scanner(new FileInputStream("escritor1.txt"))) {
            String er = "<td scope=\"row\" style=\"vertical-align: top; text-align: left; font-weight:bold;\">Nascimento[\\s\\S]*?<a href=\"[^>]*>(\\d+ de [^<]+) de \\d+";
            Pattern p = Pattern.compile(er);
            while(ler.hasNextLine()){
                String linha = ler.nextLine();
                Matcher m = p.matcher(linha);
                if(m.find()){
                    ler.close();
                    return m.group(1);
                }
            }
        }
        return null;
    }
    
    public static String obtemMorte(String escritor) throws IOException{
        String link = obtemLinkWikipedia(escritor);
        HttpRequestFunctions.httpRequest1(link, "", "escritor1.txt");
        try (Scanner ler = new Scanner(new FileInputStream("escritor1.txt"))) {
            String er = "<td scope=\"row\" style=\"vertical-align: top; text-align: left; font-weight:bold;\">Morte[\\s\\S]*?<a href=\"[^>]*>(\\d+ de [^<]+) de \\d+";
            Pattern p = Pattern.compile(er);
            while(ler.hasNextLine()){
                String linha = ler.nextLine();
                Matcher m = p.matcher(linha);
                if(m.find()){
                    ler.close();
                    return m.group(1);
                }
            }
        }
        return null;
    }
    
    public static ArrayList<String> obtemPremios(String escritor) throws IOException {
        ArrayList<String> premios = new ArrayList<>();
        String link = obtemLinkWikipedia(escritor);
        HttpRequestFunctions.httpRequest1(link, "", "escritor1.txt");
        try (Scanner ler = new Scanner(new FileInputStream("escritor1.txt"))) {
            String er = "<td scope=\"row\" style=\"vertical-align: top; text-align: left; font-weight:bold;\">Prêmios\\s*</td>\\s*<td style=\"vertical-align: top; text-align: left;\"><div class=\"plainlist\"><ul><li>([^<]+)";
            Pattern p = Pattern.compile(er);
            while (ler.hasNextLine()) {
                String linha = ler.nextLine();
                Matcher m = p.matcher(linha);
                if (m.find()) {
                    String premio = m.group(1);
                    premios.add(premio.trim());
                }
            }
        }
        return premios;
    }
    
    public static ArrayList<String> obtemOcupacoes(String escritor) throws IOException {
        ArrayList<String> ocupacoes = new ArrayList<>();
        String link = obtemLinkWikipedia(escritor);
        HttpRequestFunctions.httpRequest1(link, "", "escritor1.txt");
        try (Scanner ler = new Scanner(new FileInputStream("escritor1.txt"))) {
            String er = "<td scope=\"row\" style=\"vertical-align: top; text-align: left; font-weight:bold;\">Ocupação\\s*</td>\\s*<td style=\"vertical-align: top; text-align: left;\">([^<]+)";
            Pattern p = Pattern.compile(er);
            while (ler.hasNextLine()) {
                String linha = ler.nextLine();
                Matcher m = p.matcher(linha);
                if (m.find()) {
                    String ocupacao = m.group(1);
                    ocupacoes.add(ocupacao.trim());
                }
            }
        }
        return ocupacoes;
    }
 
    public static String obtem_titulo(String isbn) throws IOException  {
        HttpRequestFunctions.httpRequest1("https://www.wook.pt/", isbn, "obra.txt");
        String er = "<label class=\"option checked\" for=\"gallery-toggle-cover\" title=\"([^<]+)\">";
        Pattern p = Pattern.compile(er);
        Matcher m;
        try (Scanner ler = new Scanner(new FileInputStream("obra.txt"))) {
            while (ler.hasNextLine()) {
                String linha = ler.nextLine();
                m = p.matcher(linha);
                if (m.find()) {
                    ler.close();
                    return m.group(1);
                }  
            }
        }
        return null;
    }
    
    public static double obtem_preco(String isbn) throws FileNotFoundException, IOException {
        HttpRequestFunctions.httpRequest1("https://www.wook.pt/", isbn, "obra.txt");
        String er = "<span class=\"price text-black text-align-right\">\\s*([^<]+)\\s*</span>";
        try (Scanner ler = new Scanner(new FileInputStream("obra.txt"))) {
            Pattern p = Pattern.compile(er);
            String linha;
            while (ler.hasNextLine()) {
                linha = ler.nextLine();
                Matcher m = p.matcher(linha);
                if (m.find()) {
                    ler.close();
                    return Double.parseDouble(m.group(1).replace(",", "."));
                }              
            }
        }
        return -1;
    }
    
    public static String obtem_capa(String isbn) throws IOException {
        HttpRequestFunctions.httpRequest1("https://www.wook.pt/", "", "obra.txt");
        String er = "<label\\s+class=\"option checked\"\\s+for=\"gallery-toggle-cover\"\\s+title=\"([^\"]+)\">\\s+<img\\s+src=\"([^\"]+)\"\\s+alt=\"[^\"]+\"\\s+/>";
        Scanner ler = new Scanner(new FileInputStream("obra.txt"));
        Pattern p = Pattern.compile(er);
        String linha;
        while (ler.hasNextLine()) {
            linha = ler.nextLine();
            Matcher m = p.matcher(linha);
            if (m.find()) {
                ler.close();
                return m.group(1);
            }
        }
        ler.close();
        return null;
    }
    
    public static String obtem_editora(String isbn) throws IOException {
        HttpRequestFunctions.httpRequest1("https://www.wook.pt/", "", "obra.txt");
        String er1 = "editor:";
        String er2 = "<span class=\"name\\s*font-medium\">\\s*([^<]+)\\s*</span>";
        Scanner ler = new Scanner(new FileInputStream("obra.txt"));
        Pattern p1 = Pattern.compile(er1);
        Pattern p2 = Pattern.compile(er2);
        String linha;
        while (ler.hasNextLine()) {
            linha = ler.nextLine();
            Matcher m = p1.matcher(linha);
            if (m.find()) {
                linha = ler.nextLine();
                Matcher m2 = p2.matcher(linha);
                if (m2.find()) {
                    ler.close();
                    return m2.group(1);
                }
            }
        }
        ler.close();
        return null;
    } 
    
    public static String obtemISBN(String isbn) throws IOException{
        String link = obtemLinkWook(isbn);
        HttpRequestFunctions.httpRequest1(link, "", "obra.txt");
        try (Scanner ler = new Scanner(new FileInputStream("obra.txt"))) {
            String er = "<td>ISBN:</td>\\s*<td class=\"font-medium\">\\s*([0-9\\-]+)\\s*</td>";
            Pattern p = Pattern.compile(er);
            while(ler.hasNextLine()){
                String linha = ler.nextLine();
                Matcher m = p.matcher(linha);
                if(m.find()){
                    ler.close();
                    return m.group(1);
                }
            }
        }
        return null;
    }
}