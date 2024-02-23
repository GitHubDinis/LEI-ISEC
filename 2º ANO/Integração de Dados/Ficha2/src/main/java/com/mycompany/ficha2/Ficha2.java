/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 */

package com.mycompany.ficha2;

import java.io.BufferedWriter;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import static java.lang.Integer.parseInt;
import java.util.Scanner;

/**
 *
 * @author Utilizador
 */
public class Ficha2 {
    
    static String ler_ficheiro(String nomeF) throws FileNotFoundException{
        String linha;
        StringBuilder texto = new StringBuilder(); //permite concatenar várias String
        Scanner input = new Scanner(new FileInputStream(nomeF));

        while ((input.hasNextLine())) {
            linha = input.nextLine();
            texto.append(linha).append("\n");
        }
        input.close();
        return texto.toString(); //converter StringBuilder para String
    }
    
    static void separa_ficheiro(String nomeF) throws FileNotFoundException, IOException{
        String linha;
        String []campos;
        Scanner input = new Scanner(new FileInputStream(nomeF));
        BufferedWriter mulheres = new BufferedWriter(new FileWriter("mulheres.txt"));
        BufferedWriter homens = new BufferedWriter(new FileWriter("homens.txt"));
        while ((input.hasNextLine())) {
            linha = input.nextLine(); //lê linha a linha
            campos = linha.split(";");
            if("F".equals(campos[2])){
                mulheres.write(campos[0] + "\n");
            } else if("M".equals(campos[2])){
                homens.write(campos[0] + "\n");
            }
        }
        mulheres.close();
        homens.close();
        input.close();
    }
    
    static double calcula_MediaIdade(String genero) throws FileNotFoundException{
        int somaH = 0, contaH = 0;
        int somaM = 0, contaM = 0;
        
        String linha;
        String []campos;
        
        Scanner input = new Scanner(new FileInputStream("alunos.txt"));
        
        while ((input.hasNextLine())) {
            linha = input.nextLine(); //lê linha a linha
            campos = linha.split(";");
            if("F".equals(campos[2])){
                somaH = somaH + parseInt(campos[3]);
                contaH = contaH + 1;
            } else if("M".equals(campos[2])){
                contaM = contaM + 1;
                somaM = somaM + parseInt(campos[3]);
            }
        }
        
        int mediaH = somaH / contaH;
        int mediaM = somaM / contaM;
        
        if(genero.equals("M")){
            return mediaM;
        } else {
            return mediaH;
        }
    }

    public static void main(String[] args) {
        Frame app = new Frame();
        app.setVisible(true);
    }
}
