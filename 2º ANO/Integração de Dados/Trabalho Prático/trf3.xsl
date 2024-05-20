<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	<xsl:output method="xml"/>
	
	<xsl:template match="paises">
		<listagem>
			<xsl:apply-templates select="pais">
				<xsl:sort select="@nome"/>
			</xsl:apply-templates>
		</listagem>
	</xsl:template>

	<xsl:template match="pais">
		<pais nome="{@nome}"><xsl:value-of select="nome"/></pais>
	</xsl:template>
	
</xsl:stylesheet>


