/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 */

package com.mycompany.ficha3;

import java.io.BufferedWriter;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Scanner;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 *
 * @author Utilizador
 */
public class Ficha3 {
    
    public static void ficha3a(){
        String telef = "919191919 929992221 91111111111 239494582 967779999";
        
        String er = "\\b9[1236][0-9]{7}\\b";
        
        Pattern p = Pattern.compile(er);
        
        Matcher m = p.matcher(telef);
        while(m.find()){
            System.out.println("Número de Telefone: " + m.group() + "\n");
        }
    }
    
    public static void ficha3b(String fileIn, String fileOut) throws FileNotFoundException, IOException{
        String er = "[0-9]{2}[/-][0-9]{2}[/-][0-9]{4}";
        
        String linha;
        Scanner input = new Scanner(new FileInputStream(fileIn));
        BufferedWriter output = new BufferedWriter(new FileWriter(fileOut));
        
        while ((input.hasNextLine())) {
            linha = input.nextLine(); //lê linha a linha
            Pattern p = Pattern.compile(er);
            Matcher m = p.matcher(linha);
            while(m.find()){
                output.write(m.group() + "\n");
            }
        }
        output.close();
        input.close();
        
    }
    
    public static void ficha3c(String fileIn, String fileOut) throws FileNotFoundException, IOException{
        String er = "\\b[a-zA-Záé]*(ch)[a-zA-Záé]*";
        
        int nsubstituicoes = 0;
        String linha;
        Scanner input = new Scanner(new FileInputStream(fileIn));
        BufferedWriter output = new BufferedWriter(new FileWriter(fileOut));
        
        String result = null;
        
        while ((input.hasNextLine())) {
            linha = input.nextLine(); //lê linha a linha
            Pattern p = Pattern.compile(er);
            Matcher m = p.matcher(linha);
            while(m.find()){
                nsubstituicoes++;
                result = linha.replace(m.group(1), "X");
            }
            output.write(result + "\n");
        }
        
        output.write("Foram efetuadas " + nsubstituicoes + " substituições");
        
        output.close();
        input.close();
    }

    public static void main(String[] args) throws IOException {
        
        //String texto = "A Maria tem 12 anos";
        
        //String er = "[0-9]+";
        //Pattern p = Pattern.compile(er);
        
        //Matcher m = p.matcher(texto);
        //while(m.find()){
        //    System.out.println("Idade da Maria: " + m.group() + "\n");
        //}
        
        //ficha3b("datas.txt", "outl.txt");
        
        //ficha3c("ficheiro3.txt", "out2.txt");
        
        String nome = Wrappers.procura_por_id("999");
        System.out.println("Nome Encontrado: " + nome + "\n");
        
        String cidade = Wrappers.procura_cidade_por_id("999");
        System.out.println("Cidade Encontrada: " + cidade + "\n");
        
        String profissao = Wrappers.procura_profissao_por_id("999");
        System.out.println("Profissão Encontrada: " + profissao + "\n");
        
        Scanner ler = new Scanner(System.in);
        String palavra;
        System.out.println("Palavra a procurar: ");
        palavra = ler.nextLine();
        ArrayList res = Wrappers.procura_nomes(palavra);
        System.out.println(res);
    }
}
