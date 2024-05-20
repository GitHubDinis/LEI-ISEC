<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	<xsl:output method="xml"/>
	
	<xsl:template match="paises">
		<listagem>
			<xsl:apply-templates select="pais">
				<xsl:sort select="translate(populacao, ',', '')" order="descending"/>
			</xsl:apply-templates>
		</listagem>
	</xsl:template>

	<xsl:template match="pais">
		<xsl:if test="position() &lt;= 5">
			<pais>
				<nome><xsl:value-of select="@nome"/></nome>
				<populacao><xsl:value-of select="populacao"/></populacao>
			</pais>
		</xsl:if>
	</xsl:template>
	
</xsl:stylesheet>


