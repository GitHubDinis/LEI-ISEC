/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package com.mycompany.trabalhopraticoid;

import java.io.File;
import java.io.IOException;
import org.jdom2.Attribute;
import org.jdom2.DocType;
import org.jdom2.Document;
import org.jdom2.Element;
import org.jdom2.Namespace;

/**
 *
 * @author Utilizador
 */
public class ValidarXML {
    public static int validarDocumentoDTD(String xmlFile, String DTDFile) throws IOException {
        Document doc = XMLJDomFunctions.lerDocumentoXML(xmlFile);
        File f = new File(DTDFile);
        if (doc != null && f.exists()) { //DTD e XML existem
            Element raiz = doc.getRootElement();
            //Atribuir DTD ao ficheiro XML
            DocType dtd = new DocType(raiz.getName(), DTDFile);
            doc.setDocType(dtd);
            //Gravar o XML com as alterações em disco
            XMLJDomFunctions.escreverDocumentoParaFicheiro(doc, xmlFile);
            //CHAMAR A FUNÇÃO DE VALIDAÇÃO por DTD
            Document docDTD = JDOMFunctions_Validar.validarDTD(xmlFile);
            if (docDTD == null) {
                System.out.println("INVALIDO por DTD");
                return -1;
            } else {
                System.out.println("VALIDO por DTD");
                return 1;
            }
        }
        return 0;
    }
    
    public static int validarDocumentoXSD(String xmlFile, String XSDFile) {
        Document doc = XMLJDomFunctions.lerDocumentoXML(xmlFile);
        File f = new File(XSDFile);
        if (doc != null && f.exists()) {//XSD e XML existem
            Element raiz = doc.getRootElement();
            //Atribuir XSD ao ficheiro XML
            Namespace XSI = Namespace.getNamespace("xsi", "http://www.w3.org/2001/XMLSchema-instance");
            raiz.addNamespaceDeclaration(XSI);
            raiz.setAttribute(new Attribute("noNamespaceSchemaLocation", XSDFile,
                    Namespace.getNamespace("xsi", "http://www.w3.org/2001/XMLSchema-instance")));

            //Gravar o XML com as alterações em disco
            XMLJDomFunctions.escreverDocumentoParaFicheiro(doc, xmlFile);

            //CHAMAR A FUNÇÃO DE VALIDAÇÃO por XSD
            Document docXSD = JDOMFunctions_Validar.validarXSD(xmlFile);
            if (docXSD == null) {
                System.out.println("INVALIDO por XSD");
                return -1;
            } else {
                System.out.println("VALIDO por XSD");
                return 1;
            }
        }
        return 0;
    }
}
