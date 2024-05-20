xquery version "1.0";

declare variable $v := doc("C:/Users/Utilizador/Documents/NetBeansProjects/TrabalhoPraticoID/input.xml")/input/text();

<html><body>
<h2>Bandeiras do Continente {$v}</h2>
<ul>
{
for $x in doc("C:/Users/Utilizador/Documents/NetBeansProjects/TrabalhoPraticoID/paises.xml")//pais
where $x/continente/text() = $v
return 
	<li><img src="{$x/bandeira/text()}" height="100px" width="100px"/></li>
}
</ul>
</body></html>