<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	<xsl:output method="html"/>
	<xsl:template match="factos">
		<html><body>
		<h2>Listagem das Cidades</h2>
	   		<ul>
				<xsl:apply-templates select="pais"/>
	   		</ul> 
		</body></html>
	</xsl:template>

	<xsl:template match="pais">
		<xsl:for-each select="cidades_mais_populosas/cidade">
			<xsl:sort select = "."/>
			<li><xsl:value-of select="."/></li>
		</xsl:for-each>
	</xsl:template>
	
</xsl:stylesheet>


