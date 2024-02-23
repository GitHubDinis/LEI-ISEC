/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 */

package com.mycompany.ficha1;
import java.io.BufferedWriter;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Scanner;

/**
 *
 * @author Utilizador
 */
public class Ficha1 {

    public static void minhafunc1() {
        
        Scanner idade = new Scanner(System.in);
        int n;
        n = idade.nextInt();
        
        Scanner nome = new Scanner(System.in);
        String no;
        no = nome.nextLine(); 
        
        System.out.println("Hello World!"); // print e muda de linha
        System.out.println("O meu nome é " + no + " e tenho " + n + " anos.");
    }
    
    static void minhafunc2(int num){
        ArrayList<Aluno> turma = new ArrayList();
        Aluno a;
        
        int somaH = 0, contaH = 0;
        int somaM = 0, contaM = 0;
        
        for(int i = 0; i < num; i++){
            System.out.println("Aluno " + i);
            Scanner nome = new Scanner(System.in);
            String no;
            no = nome.nextLine();

            Scanner local = new Scanner(System.in);
            String l;
            l = local.nextLine();

            Scanner genero = new Scanner(System.in);
            String g;
            g = genero.next();

            Scanner idade = new Scanner(System.in);
            int n;
            n = idade.nextInt();

            a = new Aluno(no, l, g, n);
            turma.add(a);
            
            if("M".equals(g)){
                contaH++;
                somaH = somaH + n;
            } else{
                contaM++;
                somaM = somaM + n;
            }
        }
        
        int mediaH = somaH / contaH;
        int mediaM = somaM / contaM;
        
        for(int i = 0; i < num; i++){
            System.out.println("Aluno " + i + ": Nome - " + turma.get(i).nome + ", Local: " + turma.get(i).local + ", Genero: " + turma.get(i).genero + ", Idade: " + turma.get(i).idade);
        }
        
        System.out.println("Media Rapazes: " + mediaH);
        System.out.println("Media Raparigas: " + mediaM);
    }
    
    static void minhafunc3(String nomefich) throws FileNotFoundException, IOException{
        Scanner ler = new Scanner(new FileInputStream(nomefich));
        
        BufferedWriter escreverH = new BufferedWriter(new FileWriter("homens.txt"));
        BufferedWriter escreverM = new BufferedWriter(new FileWriter("mulheres.txt"));
        
        String linha;
        String []campos;
        
        while ((ler.hasNextLine())) {
            linha = ler.nextLine(); //lê linha a linha
            campos = linha.split(";");
            if("F".equals(campos[2])){
                escreverM.write(campos[0] + "\n");
            } else if("M".equals(campos[2])){
                escreverH.write(campos[0] + "\n");
            }
        }
        
        escreverH.close();
        escreverM.close();
        ler.close();
    }
    
    public static void main(String[] args) throws FileNotFoundException, IOException {
        //minhafunc1();
        
        //System.out.println("Numero de alunos:");
        
        //Scanner nalunos = new Scanner(System.in);
        //int n;
        //n = nalunos.nextInt();
        
        //minhafunc2(n);
        
        minhafunc3("alunos.txt");
    }
}
