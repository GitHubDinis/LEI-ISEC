/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package com.mycompany.trabalhopraticoid;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Scanner;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 *  Dinis Meireles de Sousa Falcão | 2020130403
 *  Telmo Eduardo Fonseca Silva | 2019127444
 */
public class Wrappers {
    
    public static String obtemCodigoISO(String nome_pais) throws IOException{
        String codigoISO = null;
        
        String link = "https://en.wikipedia.org/wiki/";
        HttpRequestFunctions.httpRequest1(link, nome_pais, "nome_pais.html");
        
        String er = "<a href=\"/wiki/ISO_3166-2:[a-zA-Z]+\" title=\"ISO 3166-2:[a-zA-Z]+\">([^<]+)</a>";
        Scanner input = new Scanner(new FileInputStream("nome_pais.html"));
        
        String linha;
        
        while ((input.hasNextLine())) {
            linha = input.nextLine();
            Pattern p = Pattern.compile(er);
            Matcher m = p.matcher(linha);
            if(m.find()){
                codigoISO = m.group(1);
            }
        }
        input.close();
        
        if(codigoISO == null){
            codigoISO = "Não possui ISO 3166 code na página.";
        }
        
        return codigoISO;
    }
    
    public static String obtemNome(String nome_pais) throws IOException{
        String nome = null;
        
        String link = "https://en.wikipedia.org/wiki/";
        HttpRequestFunctions.httpRequest1(link, nome_pais, "nome_pais.html");
        
        String er = "<title>([a-zA-z\s]+) - Wikipedia</title>";
        Scanner input = new Scanner(new FileInputStream("nome_pais.html"));
        
        String linha;
        
        while ((input.hasNextLine())) {
            linha = input.nextLine();
            Pattern p = Pattern.compile(er);
            Matcher m = p.matcher(linha);
            if(m.find()){
                nome = m.group(1);
            }
        }
        input.close();
        
        return nome;
    }
    
    public static String obtemNomeOficialPais(String nome_pais) throws IOException{
        String nome_oficial = null;
        
        String link = "https://en.wikipedia.org/wiki/";
        HttpRequestFunctions.httpRequest1(link, nome_pais, "nome_pais.html");
        
        String er = "<div class=\"fn org country-name\">([^<]+)<";
        String er1 = "<div class=\"fn org\">([^<]+)</div>";
        Scanner input = new Scanner(new FileInputStream("nome_pais.html"));
        
        String linha;
        
        while ((input.hasNextLine())) {
            linha = input.nextLine();
            Pattern p = Pattern.compile(er);
            Matcher m = p.matcher(linha);
            if(m.find()){
                nome_oficial = m.group(1);
            } 
        }
        
        if(nome_oficial == null){
            Scanner input1 = new Scanner(new FileInputStream("nome_pais.html"));
            while ((input1.hasNextLine())) {
                linha = input1.nextLine();
                Pattern p1 = Pattern.compile(er1);
                Matcher m1 = p1.matcher(linha);
                if(m1.find()){
                    nome_oficial = m1.group(1);
                }
            }
            input1.close();
        }
        
        input.close();
        
        return nome_oficial;
    }
    
    public static String obtemContinente(String nome_pais) throws IOException{
        String capital = null;
        
        String link = "https://www.countryreports.org/country/";
        HttpRequestFunctions.httpRequest1(link, nome_pais + "/geography.htm", "nome_pais.html");
        
        String er1 = "Geographic Location					</td>";
        String er2 = "([a-zA-Z\s]+)					</td>";

        String linha;
        Scanner input = new Scanner(new FileInputStream("nome_pais.html"));
        
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
                    capital = m2.group(1);
                    return capital;
                }
            }
        }
        input.close();
        
        return capital;
    }
    
    public static String obtemPresidente(String nome_pais) throws IOException{
        String presidente = null;
        
        String link = "https://en.wikipedia.org/wiki/";
        HttpRequestFunctions.httpRequest1(link, nome_pais, "nome_pais.html");
        
        String er = ">(President|Monarch)</a> </div></th><td class=\"infobox-data\">(<[^<]+)?<a href=\"/wiki/[^\"]+\" title=\"[^\"]+\">([^<]+)</a>";
        String er2 = ">CCP General Secretary</a><sup id=\"cite_ref-4\" class=\"reference\"><a href=\"#cite_note-4\">&#91;a&#93;</a></sup> </div></th><td class=\"infobox-data\"><a href=\"/wiki/[^\"]+\" title=\"[^\"]+\">([^<]+)</a>";
        Scanner input = new Scanner(new FileInputStream("nome_pais.html"));
        
        String linha;
        
        while ((input.hasNextLine())) {
            linha = input.nextLine();
            Pattern p = Pattern.compile(er);
            Matcher m = p.matcher(linha);
            if(m.find()){
                presidente = m.group(3);
            }
        }
        
        if(presidente == null){
            Scanner input2 = new Scanner(new FileInputStream("nome_pais.html"));
            while ((input2.hasNextLine())) {
                linha = input2.nextLine();
                Pattern p2 = Pattern.compile(er2);
                Matcher m2 = p2.matcher(linha);
                if(m2.find()){
                    presidente = m2.group(1);
                }
            }
            input2.close();
        }
        
        input.close();
        
        return presidente;
    }
    
    public static String obtemBandeira(String nome_pais) throws IOException{
        String bandeira = null;
        
        String link = "https://en.wikipedia.org/wiki/";
        HttpRequestFunctions.httpRequest1(link, nome_pais, "nome_pais.html");
        
        String er = "title=\"Flag of " + nome_pais + "\"><img alt=\"[^\"]+\" src=\"([^\"]+)\"";
        Scanner input = new Scanner(new FileInputStream("nome_pais.html"));
        
        String linha;
        
        while ((input.hasNextLine())) {
            linha = input.nextLine();
            Pattern p = Pattern.compile(er);
            Matcher m = p.matcher(linha);
            if(m.find()){
                bandeira = m.group(1);
            }
        }
        input.close();
        
        return bandeira;
    }
    
    public static String obtemCapital(String nome_pais) throws IOException{
        String capital = null;
        
        String link = "https://www.countryreports.org/country/";
        HttpRequestFunctions.httpRequest1(link, nome_pais + ".htm", "nome_pais.html");
        
        String er1 = "Capital					</td>";
        String er2 = "([a-zA-Z\sí,]+)					</td>";
        //String er3 = "([a-zA-Zí,]+[\s]?[a-zA-Z]+)					</td>";
        String linha;
        Scanner input = new Scanner(new FileInputStream("nome_pais.html"));
        
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
                    capital = m2.group(1);
                    return capital;
                }
            }
        }
        input.close();
        
        return capital;
    }
    
    public static String obtemMoeda(String nome_pais) throws IOException{
        String moeda = null;
        
        String link = "https://www.countryreports.org/country/";
        HttpRequestFunctions.httpRequest1(link, nome_pais + ".htm", "nome_pais.html");
        
        String er1 = "Currency					</td>";
        String er2 = "([a-zA-Z\s()]+)					</td>";
        String linha;
        Scanner input = new Scanner(new FileInputStream("nome_pais.html"));
        
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
                    moeda = m2.group(1);
                    return moeda;
                }
            }
        }
        input.close();
        
        return moeda;
    }
    
    public static String obtemPopulacao(String nome_pais) throws IOException{
        String populacao = null;
        
        String link = "https://www.countryreports.org/country/";
        HttpRequestFunctions.httpRequest1(link, nome_pais + ".htm", "nome_pais.html");
        
        String er1 = "Population					</td>";
        String er2 = "([0-9,]+)					</td>";
        String linha;
        Scanner input = new Scanner(new FileInputStream("nome_pais.html"));
        
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
                    populacao = m2.group(1);
                    return populacao;
                }
            }
        }
        input.close();
        
        return populacao;
    }
    
    public static String obtemArea(String nome_pais) throws IOException{
        String area = null;
        
        String link = "https://www.countryreports.org/country/";
        HttpRequestFunctions.httpRequest1(link, nome_pais + ".htm", "nome_pais.html");
        
        String er1 = "Total Area					</td>";
        String er2 = "<br /> ([0-9,]+) Square Kilometers					</td>";
        String linha;
        Scanner input = new Scanner(new FileInputStream("nome_pais.html"));
        
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
                    area = m2.group(1);
                    return area;
                }
            }
        }
        input.close();
        
        return area;
    }
    
    public static String obtemCrescimentoPopulacao(String nome_pais) throws IOException{
        String crescimentoPopulacao = null;
        
        String link = "https://www.countryreports.org/country/";
        HttpRequestFunctions.httpRequest1(link, nome_pais + ".htm", "nome_pais.html");
        
        String er1 = "Population Growth Rate					</td>";
        String er2 = "([0-9.%]+)					</td>";
        String linha;
        Scanner input = new Scanner(new FileInputStream("nome_pais.html"));
        
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
                    crescimentoPopulacao = m2.group(1);
                    return crescimentoPopulacao;
                }
            }
        }
        input.close();
        
        return crescimentoPopulacao;
    }
    
    public static ArrayList<String> obtemCidadesMaisPopulosas(String nome_pais) throws FileNotFoundException, IOException{
        ArrayList cidades = new ArrayList();
        
        String link = "https://www.countryreports.org/country/";
        HttpRequestFunctions.httpRequest1(link, nome_pais + ".htm", "nome_pais.html");
        
        String er1 = "Population in Major Urban Areas					</td>";
        String er2 = "([a-zA-Z()0-9.,\s]+);?([a-zA-Z()0-9.,\s]+)?;?([a-zA-Z()0-9.,\s]+)?					</td>";
        String linha;
        Scanner input = new Scanner(new FileInputStream("nome_pais.html"));
        
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
                    cidades.add(m2.group(1));
                    if(m2.group(2) != null){
                        cidades.add(m2.group(2));
                    }
                    if(m2.group(3) != null){
                        cidades.add(m2.group(3));
                    }
                    return cidades;
                }
            }
        }
        input.close();
        
       return cidades;
    }
    
    public static String obtemDominioInternet(String nome_pais) throws IOException{
        String dominio = null;
        
        String link = "https://en.wikipedia.org/wiki/";
        HttpRequestFunctions.httpRequest1(link, nome_pais, "nome_pais.html");
        
        String er = ">Internet TLD</a></th><td class=\"infobox-data\">[^<]*<a href=\"/wiki/[^\"]+\" title=\"[^\"]+\">([^<]+)</a>";
        Scanner input = new Scanner(new FileInputStream("nome_pais.html"));
        
        String linha;
        
        while ((input.hasNextLine())) {
            linha = input.nextLine();
            Pattern p = Pattern.compile(er);
            Matcher m = p.matcher(linha);
            if(m.find()){
                dominio = m.group(1);
            }
        }
        input.close();
        
        return dominio;
    }  
    
    // FALTA LISTA DE IDIOMAS OFICIAIS 
    public static ArrayList<String> obtemIdiomaOficial(String nome_pais) throws IOException{
        ArrayList idiomas = new ArrayList();
        
        String link = "https://www.countryreports.org/country/";
        HttpRequestFunctions.httpRequest1(link, nome_pais + ".htm", "nome_pais.html");
        
        String er1 = "Predominant Language					</td>";
        String er2 = "([a-zA-Z()0-9%\s-]+),?([a-zA-Z()0-9%\s-]+)?,?([a-zA-Z()0-9%\s-]+)?,?([a-zA-Z()0-9%\s-]+)?					</td>|<br />";
        String linha;
        Scanner input = new Scanner(new FileInputStream("nome_pais.html"));
        
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
                    idiomas.add(m2.group(1));
                    if(m2.group(2) != null){
                        idiomas.add(m2.group(2));
                    }
                    if(m2.group(3) != null){
                        idiomas.add(m2.group(3));
                    }
                    if(m2.group(4) != null){
                        idiomas.add(m2.group(4));
                    }
                    return idiomas;
                }
            }
        }
        input.close();
        
       return idiomas;
    }  
    
    // FALTA LISTA DE PAÍSES VIZINHOS
    public static ArrayList<String> obtemPaisesVizinhos(String nome_pais) throws IOException{
        ArrayList paisesVizinhos = new ArrayList();
        
        String link = "https://www.countryreports.org/country/";
        HttpRequestFunctions.httpRequest1(link, nome_pais + "/geography.htm", "nome_pais.html");
        
        String er1 = "Border Countries					</td>";
        //String er2 = "([a-zA-Z\s]+),?([a-zA-Z()\s.,]+)?,?([a-zA-Z()0-9\s.,]+)?,?([a-zA-Z()0-9\s.,]+)?					(</td>|<br />)";
        String er3 = "([A-Za-z]+) [0-9]{1,3}(?:,[0-9]{3})* km,?([A-Za-z]*)\s*[0-9]*(?:,[0-9]{3})*\s*k?m?,?([A-Za-z]*)\s*[0-9]*(?:,[0-9]{3})*\s*k?m?,?([A-Za-z]*)\s*[0-9]*(?:,[0-9]{3})*\s*k?m?,?					(</td>|<br />)";
        
        String er4 = "([a-zA-Z]+) [0-9]+[.|,]?[0-9]* km,? ([a-zA-Z]*) [0-9]*.?,?[0-9]* k?m?,? ([a-zA-Z]*) [0-9]*.?,?[0-9]* k?m?,? ([a-zA-Z]*) [0-9]*.?,?[0-9]* k?m?,? ([a-zA-Z]*) [(]?([a-zA-Z]*)[)]? [0-9]*.?,?[0-9]* k?m?,? ([a-zA-Z]*) [(]?([a-zA-Z]*)[)]? [0-9]*.?,?[0-9]* k?m?					</td>";
        
        String er2 = "([A-Za-z]+).*[A-Za-z]*.*(\s([A-Za-z]*\s)*).*[A-Za-z]*.*[A-Za-z]*.*[A-Za-z]*.*[A-Za-z]*.*[A-Za-z]*.*[A-Za-z]*";
        
        String linha;
        Scanner input = new Scanner(new FileInputStream("nome_pais.html"));
        
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
                    //input.close();
                    paisesVizinhos.add(m2.group(1));
                } 
                
            }
        }
        input.close();
        
       return paisesVizinhos;
    }
}
