<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	<xsl:output method="xml"/>
	
  	<xsl:variable name="inputDoc" select="doc('C:/Users/Utilizador/Documents/NetBeansProjects/TrabalhoPraticoID/input.xml')"/>

   	<xsl:variable name="countryName" select="$inputDoc/input"/>

	<xsl:template match="/">
        	<pais>
      			<xsl:apply-templates select="document('C:/Users/Utilizador/Documents/NetBeansProjects/TrabalhoPraticoID/paises.xml')/paises/pais[@nome=$countryName]"/>
    		</pais>
  	</xsl:template>

  	<xsl:template match="pais">
    		<xsl:copy>
      			<xsl:copy-of select="@*"/>
      			<xsl:copy-of select="*"/>
      			<xsl:copy-of select="document('C:/Users/Utilizador/Documents/NetBeansProjects/TrabalhoPraticoID/factos.xml')/factos/pais[@nome=$countryName]/(*[not(self::nome_oficial) and not(self::codigoISO)])"/>
    		</xsl:copy>
  	</xsl:template>
	
</xsl:stylesheet>


